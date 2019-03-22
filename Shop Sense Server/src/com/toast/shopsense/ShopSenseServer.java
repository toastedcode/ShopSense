package com.toast.shopsense;

import java.awt.BorderLayout;
import java.time.LocalDateTime;

import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextPane;
import javax.swing.SwingUtilities;
import javax.swing.text.BadLocationException;
import javax.swing.text.StyledDocument;

import org.json.JSONException;
import org.json.JSONObject;

import com.toast.socket.SimpleSocket;
import com.toast.socket.SocketListener;

public class ShopSenseServer implements SocketListener
{
   public static void main(final String args[])
   {
      try
      {
         // Spawn the GUI thread.
         // Note: invokeLater() causes this to be executed on the event dispatch thread.
         SwingUtilities.invokeLater(
            new Runnable()
            {
               public void run()
               {
                  new ShopSenseServer();
               }
            });
      }
      catch(Exception e)
      {
         System.out.print("Failed to start application.\n");            
      }
   }
   
   public ShopSenseServer()
   {
      createGui();
      
      connectToDatabase();
      
      listen();
   }
   
   // **************************************************************************
   //                          SocketListener interface

   @Override
   public void onConnected(SimpleSocket socket)
   {
      println("Received connection from %s.",socket.getSocket().getRemoteSocketAddress().toString());
   }

   @Override
   public void onDisconnected(SimpleSocket socket)
   {
      println("Disconnected.");
   }

   @Override
   public void onConnectionFailed(SimpleSocket socket)
   {
      println("Connection failed.");
   }

   @Override
   public void handleData(SimpleSocket socket, String buffer)
   {
      try
      {
         JSONObject json = new JSONObject(buffer);
         
         String machineId = json.getString("machineId");
         String sensorId = json.getString("sensorId");
         String messageId = json.getString("messageId");
         
         println("Got %s message from %s.%s", messageId, machineId, sensorId);
         
         database.store(machineId, sensorId, messageId, buffer);
      }
      catch (JSONException e)
      {
         println("Parse error: \"%s\"", buffer);
      }
   }
   
   // **************************************************************************
   
   private void println(
      String format,
      Object... arguments)
   {
      String string = String.format(format, arguments);
      
      StyledDocument doc = textPane.getStyledDocument();
      
      try
      {
         doc.insertString(doc.getLength(),  string + "\n", null);
      } 
      catch (BadLocationException e)
      {
         e.printStackTrace();
      }      
   }
   
   private void createGui()
   {
      frame = new JFrame("Shop Sense Server");
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      
      JPanel centerPanel = new JPanel();
      centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.X_AXIS));
      
      frame.getContentPane().add(centerPanel, BorderLayout.CENTER);
      
      // TODO: GUI creation
      
      textPane = new JTextPane();
      textPane.setEditable(false);
      
      JScrollPane scrollPane = new JScrollPane(textPane);
      scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS); 
      
      centerPanel.add(scrollPane);
      
      frame.setSize(500, 150);
      frame.setVisible(true);
   }
   
   private void connectToDatabase()
   {
      database.connect(DATABASE_URL, DATABASE_USERNAME,  DATABASE_PASSWORD);
   }
   
   private void listen()
   {
      println("Listening on port " + PORT + ".");
      
      server.addListener(this);
      server.listen(PORT);
   }
   
   private static final int PORT = 5000;
   
   private static final String DATABASE_URL = "localhost";
   
   private static final String DATABASE_USERNAME = "pi";
   
   private static final String DATABASE_PASSWORD = "r4sp83rryt0st";
   
   private JFrame frame;
   
   private JTextPane textPane;
   
   private SimpleSocket server = new SimpleSocket();
   
   private Database database = new Database();
}
