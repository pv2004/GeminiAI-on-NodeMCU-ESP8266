#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* ssid = "NAKSHATRA-1";  // Replace with your WiFi SSID
const char* password = "Srinivasan@123";  // Replace with your WiFi password
const char* Gemini_Token = "AIzaSyDVUL60jXACSa9K2g9hotKHgs6F5pNpNWc";  // Replace with your actual API Key
const int Gemini_Max_Tokens = 100;  // Max output tokens

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  int retry_count = 0;
  while (WiFi.status() != WL_CONNECTED && retry_count < 20) {
    delay(1000);
    Serial.print(".");
    retry_count++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi. Please check credentials.");
  }
}

void loop() {
  Serial.println("\nAsk your Question:");
  
  while (!Serial.available());  // Wait for user input
  String res = Serial.readStringUntil('\n');  // Read user input
  res.trim();  // Remove leading/trailing whitespace

  if (res.length() == 0) {
    Serial.println("Invalid input. Please enter a valid question.");
    return;
  }

  Serial.print("\nAsking Your Question: ");
  Serial.println(res);

  // Secure HTTP client
  WiFiClientSecure client;
  client.setInsecure();  // Allow insecure connections (for testing)

  HTTPClient http;
  String url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + String(Gemini_Token);

  if (http.begin(client, url)) {  
    http.addHeader("Content-Type", "application/json");

    // Properly formatted JSON payload
    String payload = "{\"contents\": [{\"parts\": [{\"text\": \"" + res + "\"}]}],\"generationConfig\": {\"maxOutputTokens\": " + String(Gemini_Max_Tokens) + "}}";

    int httpCode = http.POST(payload);
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      
      DynamicJsonDocument doc(4096);
      DeserializationError error = deserializeJson(doc, response);
      if (error) {
        Serial.print("JSON Parsing Error: ");
        Serial.println(error.c_str());
      } else {
        String answer = doc["candidates"][0]["content"]["parts"][0]["text"].as<String>();
        
        // Clean answer by removing special characters
        answer.trim();
        String filteredAnswer = "";
        for (size_t i = 0; i < answer.length(); i++) {
          char c = answer[i];
          if (isalnum(c) || isspace(c) || c == '.' || c == ',') {
            filteredAnswer += c;
          } else {
            filteredAnswer += ' ';
          }
        }

        Serial.println("\nHere is your Answer:");
        Serial.println(filteredAnswer);
      }
    } else {
      Serial.printf("[HTTP] Request failed. Error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect to API.");
  }
}
