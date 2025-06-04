#include <dht11.h>
#include <Arduino.h>
#include <WiFi.h>
dht11 dht_sensor;
#include <Firebase_ESP_Client.h>

//Additional codes to connect firebase properly
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

////// an error checking value is defined for time interruption
#define TIMER_INTERRUPT_DEBUG      1

// set up WIFI settings to prove esp32 an internet connection.
#define WIFI_SSID "WIFI_NAME"
#define WIFI_PASSWORD "WIFI_PASSWORD"

// Enter firebase API key to provide ESP32 sending and reading values
#define API_KEY "ENTER_YOUR_APIKEY_HERE"

// Enter database url */
#define DATABASE_URL "ENTER_YOUR_DATABASE_HERE"

//Let's create a Firebase object
FirebaseData fbdo;
//authority and config values is being created
FirebaseAuth auth;
FirebaseConfig config;
//Essential values

unsigned long getDataPrevMillis   = 0;
bool signupOK                     = false;
unsigned long sendDataPrevMillis  = 0;
String                            ReceivedValue1;
String                            ReceivedValue2;
String                            ReceivedValue3;
String                            ReceivedValue4;
void setup() {
  Serial.begin(115200);
  WiFi.begin  (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting The Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connection is provided, IP Adress: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* assign the defined value above */
  config.api_key = API_KEY;

  /* assign the database's url above to the settings */
  config.database_url = DATABASE_URL;

  /* let's connect the firebase */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* It's necessary to check whether token is still usefull or not */
  config.token_status_callback = tokenStatusCallback;
  //let's start connection
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  //pin status
  //!attention! Arrange your pins accordingly!
  pinMode(19,OUTPUT);
  pinMode(21,OUTPUT);
  pinMode(17,OUTPUT);
}

void loop() {
  //Describing values 
  static int light_value=0;
  static float humidity_value=0;
  static float temperature_value=0;
  static float ambient_humidity;
  //Values read by ADC pin of the esp32 
    light_value=analogRead(34);
    temperature_value=dht_sensor.read(33);
    humidity_value=analogRead(35);
    //Enter into if blocks after waiting for a second.
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();
        //Sending values read by ADC pins. 
    if (Firebase.RTDB.setInt(&fbdo, "LED_BLINK/Light", map(light_value,0,4095,100,0))) {
      delay(50);
      if(Firebase.RTDB.setInt(&fbdo, "LED_BLINK/hum", map(humidity_value,0,4095,100,0))){
        delay(50);
         if(Firebase.RTDB.setInt(&fbdo, "LED_BLINK/ambient_hum", (float)dht_sensor.humidity)){
          delay(50);
          if(Firebase.RTDB.setInt(&fbdo, "LED_BLINK/temp",(float)dht_sensor.temperature)){
             delay(50);
             Serial.println("Writing is completed");
             Serial.println("Adress: " + fbdo.dataPath());
             Serial.println("Value Type: " + fbdo.dataType());
              }
               else {
                Serial.println("ERROR");
                Serial.println("REASON OF THE ERROR: " + fbdo.errorReason());
              }    
        
            }
          
         } 
      }
}
   
  //Enter into if blocks after waiting for a sec
   if (Firebase.ready() && signupOK && (millis() - getDataPrevMillis > 1500 || getDataPrevMillis == 0)) {
        Firebase.RTDB.getString(&fbdo, "/LED_BLINK/auto");
        ReceivedValue1=fbdo.stringData();
        Serial.println(gelenveri1);
        Firebase.RTDB.getString(&fbdo, "/LED_BLINK/fan");
        ReceivedValue2=fbdo.stringData();
        Firebase.RTDB.getString(&fbdo, "/LED_BLINK/light_");
        ReceivedValue3=fbdo.stringData();
        Firebase.RTDB.getString(&fbdo, "/LED_BLINK/water");
        ReceivedValue4=fbdo.stringData();
        getDataPrevMillis = millis();
        //Check whether automatic mod is active or not.
        if(ReceivedValue1=="1"){
          if(map(light_value,0,4095,100,0)<45){
            digitalWrite(21,1);           
          }
          else{
            digitalWrite(21,0);
           }
          if((float)dht_sensor.temperature>29){
            digitalWrite(19,1);
            }
           else{
            digitalWrite(19,0);
            }
           if(map(humidity_value,0,4095,100,0)<35){
            digitalWrite(17,1);
            }
           else{
            digitalWrite(17,0);
            }
        }
        //Enter into blocks if devices will be controlled by hand
        else{
           if(ReceivedValue2=="1"){
            digitalWrite(19,1);
            }
           else{
            digitalWrite(19,0);
            }
            if(ReceivedValue3=="1"){
            digitalWrite(21,1);
            }
            else{
            digitalWrite(21,0);
            }
             if(ReceivedValue4=="1"){
            digitalWrite(17,1);
            }
            else{
            digitalWrite(17,0);
            }
           
          }
 }

}
