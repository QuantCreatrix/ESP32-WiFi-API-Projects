#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define Red 

const char* ssid = "Redmi 12 5G";
const char* password = "1234567890";

//Your Domain name with URL path or IP address with path
String url = "https://remotergb-y3sj.onrender.com/rgb";
String rgb;
HTTPClient http;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

  if(WiFi.status() == WL_CONNECTED) {
    delay(4000);
    http.begin(url);
  }
}

void loop() {
    int httpCode = http.GET();
    if(httpCode > 0){
      rgb = http.getString();
      Serial.println(rgb);

      // Accessing Json doc
      DynamicJsonDocument myVals(1024);
      deserializeJson(myVals, rgb);
      int r = myVals[0]["r"];
      int g = myVals[0]["g"];
      int b = myVals[0]["b"];
      
      Serial.print("Red: ");
      Serial.println(r);
      Serial.print("Green: ");
      Serial.println(g);
      Serial.print("Blue: ");
      Serial.println(b);
      // JsonObject myValues = doc.as<JsonObject>();
      // Serial.println(myValues);
      // Serial.println(myValues[3]);
      // Serial.println(myValues[4]);

      analogWrite(2, r);
      analogWrite(12, g);
      analogWrite(13, b);
    }
}