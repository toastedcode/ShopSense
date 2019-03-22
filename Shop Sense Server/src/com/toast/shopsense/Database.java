package com.toast.shopsense;

import java.time.LocalDateTime;
import java.util.List;

import org.json.JSONObject;

public class Database
{
   public void connect(
         String databaseUrl,
         String username,
         String password)
   {
      
   }
   
   public void disconnect()
   {
      
   }
   
   boolean isConnected()
   {
      return (false);
   }
   
   void store(
      String machineId,
      String sensorId,
      String messageId,
      String message)
   {
      
   }
   
   JSONObject getLastMessage(
      String machineId,
      String sensorId,
      String messageId)
   {
      return (null);
   }
   
   List<JSONObject> getMessageRange(
      String machineId,
      String sensorId,
      String messageId,
      LocalDateTime startTime,
      LocalDateTime endTime)
   {
      return (null);
   }
}
