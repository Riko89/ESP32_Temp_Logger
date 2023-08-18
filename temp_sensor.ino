//Include required libraries
#include "WiFi.h"
#include <HTTPClient.h>
#include <DHT.h>

#define DHT_SENSOR_PIN  21 // ESP32 pin GPIO21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// WiFi credentials
const char* ssid = "Your Wifi Network Here";  // Enter SSID here
const char* password = "Your Wifi password Here"; //password here
// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "-------  GOOGLE APPS SCRIPT ID HERE ----------";    // change Gscript ID
void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(1000);
  dht_sensor.begin(); // initialize the DHT sensor
  delay(1000);
  // connect to WiFi
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Init and get the time
}
void loop() {
   if (WiFi.status() == WL_CONNECTED) {
    static bool flag = false;
        // read humidity
    float humi = dht_sensor.readHumidity();
    // read temperature in Celsius
    float tempC = dht_sensor.readTemperature();
    // read temperature in Fahrenheit
    float tempF = dht_sensor.readTemperature(true);
   //start WIFI
    if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+"temperature=" + tempF + "&humidity=" + humi;
      Serial.print("POST data to spreadsheet:");
      Serial.println(urlFinal);
      HTTPClient http;
      http.begin(urlFinal.c_str());
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      int httpCode = http.GET(); 
      Serial.print("HTTP Status Code: ");
      Serial.println(httpCode);
      //---------------------------------------------------------------------
      //getting response from google sheet
      String payload;
      if (httpCode > 0) {
          payload = http.getString();
          Serial.println("Payload: "+payload);    
    }
    //---------------------------------------------------------------------
    http.end();
    }
  }
  delay(900000);
} 
