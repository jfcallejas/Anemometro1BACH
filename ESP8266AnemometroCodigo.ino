#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

const char* ssid = "OnePlus";
const char* pass = "nhdhcjv364%";
WiFiClient client;

#define DATABASE_URL "bach-anemometro-default-rtdb.firebaseio.com"
#define API_KEY "AIzaSyCrzwSn33iP_w9_x2rSjt454RC6ueOE2Eg"

#define USER_EMAIL "4084726@alu.murciaeduca.es"
#define USER_PASSWORD "prueba123"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int pin_sensor = D5;

float radiodisco = 0.105;

float time_millis = millis();

float time_rpm_inicial = 0;

float timec;

float ms;

long velocidad0time = 0;


void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("+ ]============= CONNECTED");

  delay(4000);

  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

  config.token_status_callback = tokenStatusCallback;

  Firebase.reconnectNetwork(true);

  fbdo.setBSSLBufferSize(4096, 1024);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

}


float velocidad_calc(float time) {
  float timelap = time/1000;

  ms = ((2 * 3.1415 * radiodisco)/4) / timelap;

  Serial.println(timelap);
  Serial.println(ms);

  return ms;
}

void upload_db(float data){
  Firebase.setFloat(fbdo, "velocidad", data);
}


void loop() {
  int read_rpm = digitalRead(pin_sensor);

  long timewhiout0 = millis() - velocidad0time;
  
  if (timewhiout0/1000 > 3) {
    upload_db(0);
  }


  if(read_rpm == 0){    
    timec = millis() - time_rpm_inicial;
    
    Serial.print("ini1: ");
    Serial.println(time_rpm_inicial);

    time_rpm_inicial = millis();

    velocidad0time = millis();

    float mss = velocidad_calc(timec);

    upload_db(mss);
    
  delay(50);
}

}




