#include <ESP8266WiFi.h>
#include <Utility.h>

WiFiServer server(80);

void setup() 
{
  Serial.begin(9600);

  Serial.print("*********************************\n");
  Serial.print("********** Server Test **********\n");
  Serial.print("*********************************\n");
  Serial.print("\n");

  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESPWIFI");

  server.begin();

  Serial.print("Starting access point ");
}

void loop() 
{
   WiFiClient connectedClient = server.available();

   if (connectedClient)
   {
      Serial.print("Client connected from " + Utility::toString(connectedClient.remoteIP()) + "\n");

      if (connectedClient.connected())
      {
         Serial.print("Client is connected\n");

         const int WAIT_TIME = 5000;
         int startTime = millis();
         while ((connectedClient.available() == false) &&
                ((millis() - startTime) > WAIT_TIME))
         {
           // Wait. 
         }
         
         if (connectedClient.available())
         {
            Serial.print("Data from client is available\n");

            String string = connectedClient.readStringUntil('\r');
            connectedClient.flush();

            Serial.print("Read data from client: " + string + "\n");

            String response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: text/html\r\n\r\n";
            response += "<!DOCTYPE HTML>\r\n";
            response += "<html><body>boner town, open for business</body></html>\r\n";

            connectedClient.print(response);

            delay(1);

            connectedClient.stop();
            
         }
         else
         {
            connectedClient.stop();
         }
      }
   }
}
