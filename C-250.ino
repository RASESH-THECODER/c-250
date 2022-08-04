#include<WiFi.h>
#include<Adafruit_MQTT.h>
#include<Adafruit_MQTT_Client.h>
#include<DHT.h>

#define WLAN_SSID     "KhageshGandhi_2.4G"
#define WLAN_PASS     "9820334411"
#define AIO_USERNAME  "RaeshK"
#define AIO_KEY       "aio_gcdM16QJOEcmc5DFVIcQuIuZP3O2"
#define AIO_SERVER    "io.adafruit.com"
#define AIO_SERVERPORT       1883

const int relay=23;

WiFiClient wificlient;
Adafruit_MQTT_Client mqtt(&client , AIO_SERVER , AIO_SERVERPORT , AIO_USERNAME , AIO_KEY);
Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt , AIO_USERNAME"/feeds/light");

void setup() {
  // put your setup code here, to run once:
   digitalWrite(relay,LOW);
   Serial.begin(9600);
   delay(10);
   pinMode(relay,OUTUT);
   Serial.println();
   Serial.print("connected to");
   Serial.print(WLAN_SSID);
   WiFi.begin(WLAN_SSID,WLAN_PASS);
   while(WiFI.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
   }
   Serial.println();
   Serial.println("WiFi connected");
   Serial.println("IP address:");
   mqtt.subscribe(&Light);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription=mqtt.readSubscription(5000))){
    if (subscription==&Light){
      Serial.print(F("got :"));
      Serial.println((char*)Light.lastread);
      if(!strcmp((char*)Light.lastread,"OFF")){
        digitalWrite(relay,HIGH);
        
      }
      else{
        digitalWrite(relay,LOW)
      }
      
    }
  }
}
