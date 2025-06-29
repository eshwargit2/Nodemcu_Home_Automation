#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>  // Required only for HTTPS
#include <ArduinoJson.h>


const char* ssid = "Eshwar Creativity ";
const char* password = "666666555";

//  SERVER URL
const char* serverURL = "https://serverURL.com/status"; 


// Relay Pins
#define RELAY1 D1
#define RELAY2 D2
#define RELAY3 D3
#define RELAY4 D4

void setup() {
  Serial.begin(115200);

  // Pin setup
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n  WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

   
    bool isSecure = String(serverURL).startsWith("https");
    
    int httpCode;
    String payload;

    if (isSecure) {
      WiFiClientSecure client;
      client.setInsecure(); // skip certificate check
      HTTPClient https;

      https.begin(client, serverURL);
      httpCode = https.GET();
      if (httpCode > 0) {
        payload = https.getString();
      }
      https.end();
    } else {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverURL);
      httpCode = http.GET();
      if (httpCode > 0) {
        payload = http.getString();
      }
      http.end();
    }

   
    if (httpCode > 0) {
      Serial.println("✅ Payload: " + payload);

     
      DynamicJsonDocument doc(256);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        digitalWrite(RELAY1, doc["1"] == "on" ? HIGH : LOW);
        digitalWrite(RELAY2, doc["2"] == "on" ? HIGH : LOW);
        digitalWrite(RELAY3, doc["3"] == "on" ? HIGH : LOW);
        digitalWrite(RELAY4, doc["4"] == "on" ? HIGH : LOW);
      } else {
        Serial.println("❌ JSON Parse Failed");
      }

    } else {
      Serial.printf("❌ HTTP Error: %d\n", httpCode);
    }

  } else {
    Serial.println("❌ WiFi Disconnected");
  }

 
}