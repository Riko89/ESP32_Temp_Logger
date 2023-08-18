# ESP32_Temp_Logger
Temperature Logger with the ESP32 using Google Sheets and Google App Script


![Temperature_Sensor](https://github.com/Riko89/ESP32_Temp_Logger/assets/39813738/500f0102-f4de-4e3b-b66f-41a8d54992e6)

  **Google Sheets**
-Share Google sheet for Anyone
-Name your sheet tabs at the bottom of the screen
-Copy the middle section of the link for use in the google Apps Script

  **Google Apps Script**
  **- COPY THE CODE FROM temp_sensor_Apps_Script.txt HERE -**
-Make new Project or Find your old one
-Place your copied Sheet ID in the var sheet_id field
-Place the Sheet you want to write to in the 
var sheet_name field
-Deploy your Project as Web App, execute as me, 
who has access: Anyone
-Copy the ID after deploying for use in Arduino Script

  **Arduino**
  **- USE temp_sensor.ino file -**
-Launch Arduino IDE selecting the proper COM PORT and select board Node32s
-Replace the const char* ssid = with your Wifi Name
-Replace the const char* password = with your Wifi password
-Replace the GOOGLE_SCRIPT_ID with your Google Apps script ID that you copied from Deploying your Apps Script
-Compile and Upload your code to the Board
