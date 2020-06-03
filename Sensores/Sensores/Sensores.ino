#include <ArduinoJson.h>

#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

int pin=2;
DHT11 dht11(pin);

const char* ssid = "NOMBRE DE LA RED";
const char* password = "CONTRASEÑA DE LA RED";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.0.6:8085/history";

unsigned long lastTime = 0;
// Timer set to 10 minutes (3600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 3600000;

void setup()
   {
       Serial.begin(9600);
      
        // Connect to WiFi
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) 
        {
           delay(500);
           Serial.print("*");
        }
        
        Serial.println("");
        Serial.println("WiFi connection Successful");
        Serial.print("The IP Address of ESP8266 Module is: ");
        Serial.print(WiFi.localIP());// Print the IP address
   }


void loop()
   {
       int err;
       float temp, hum;
       if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
          {
             Serial.print("Temperatura: ");
             Serial.print(temp);
             Serial.print(" Humedad: ");
             Serial.print(hum);
             Serial.println();

             
             
              Serial.println();
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
          }
        
    if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status

     if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
       // Your Domain name with URL path or IP address with path
        http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
      // Data to send with HTTP POST
      String requestP1 = "\"value\":\"";
      String requestP2 = ",\"sensorId\":\"";
      // Prepare JSON document
        DynamicJsonDocument docHum(2048);
        docHum["value"] = hum;
        docHum["sensorId"] = 1;
        
        // Serialize JSON document
        String jsonHum;
        serializeJson(docHum, jsonHum);
       
      String httpRequestData = "{" + requestP1 + hum + "\"" + requestP2 + 1 + "\"" + "}";
               
      // Send HTTP POST request
      int httpResponseCode = http.POST(jsonHum);

     
      Serial.print("HTTP Response code: ");
      Serial.print(http.getString());
      Serial.println(httpResponseCode);

      // Free resources
      http.end();

      // Specify content-type header
      http.addHeader("Content-Type", "application/json");

      
        DynamicJsonDocument docTemp(2048);
        docTemp["value"] = temp;
        docTemp["sensorId"] = 2;
        String jsonTemp;
        serializeJson(docTemp, jsonTemp);

        httpResponseCode = http.POST(jsonTemp);

      Serial.print("HTTP Response code: ");
      Serial.print(http.getString());
      Serial.println(httpResponseCode);

        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    
    lastTime = millis();
  }
        
       delay(2000);            //Recordad que solo lee una vez por segundo
   }
