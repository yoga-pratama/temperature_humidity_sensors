#include <ESP8266WiFi.h>
#include "DHT.h"
#include <WiFiClient.h>;
#include <ThingSpeak.h>;


DHT dht;

const char* ssid     = "Yoga P";
const char* password = "yoga1234";

const char* apiKey = "9L1B0RCTCBX7MA7E";
unsigned long myChannelNumber = 817601; //Your Channel Number (Without Brackets)

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  dht.setup(D1);

  Serial.print("connect to thinkspeak");
  ThingSpeak.begin(client);
}

void loop() {
  float  h = dht.getHumidity();
  float  t = dht.getTemperature();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      Serial.print(".");
      delay(20000);
    }
    Serial.println("\nConnected.");
  }


  Serial.print("temperature : ");
  Serial.println(t);
  Serial.print("humidity : ");
  Serial.println(h);

  ThingSpeak.setField(1 , t);
  ThingSpeak.setField(2 , h);

  Serial.println("Try Update Data to thinkSpeak");
  int x =  ThingSpeak.writeFields(myChannelNumber,apiKey);

  if (x == 200) {
    Serial.println("Channel update successful.");  // change the values number1++; if(number1 > 99){
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
   delay(20000); 
}
