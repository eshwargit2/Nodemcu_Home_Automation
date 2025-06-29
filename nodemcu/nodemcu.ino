#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Eshwar Creativity ";
const char* password = "666666555";
const char* serverURL = "http://192.168.250.172:3000/status";

#define RELAY1 D1
#define RELAY2 D2
#define RELAY3 D3
#define RELAY4 D4

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverURL);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Payload: " + payload);

      // Parse JSON
      DynamicJsonDocument doc(256);
      deserializeJson(doc, payload);

      digitalWrite(RELAY1, doc["1"] == "on" ? HIGH : LOW);
      digitalWrite(RELAY2, doc["2"] == "on" ? HIGH : LOW);
      digitalWrite(RELAY3, doc["3"] == "on" ? HIGH : LOW);
      digitalWrite(RELAY4, doc["4"] == "on" ? HIGH : LOW);

    } else {
      Serial.println("HTTP Error");
    }

    http.end();
  }


}