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

  WiFi.softAP("ESPWIFI");

  Serial.print("Starting access point ");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500); 
    Serial.print(". ");
  }
  Serial.print("success!\n");
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
         }
         else
         {
            connectedClient.stop();
         }
      }
   }

   delay(500);
}
