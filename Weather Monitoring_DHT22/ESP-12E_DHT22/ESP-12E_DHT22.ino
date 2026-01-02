#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>

#include <ESP8266WiFi.h>

#include <ThingSpeak.h>

#define DHTPIN 2
#define DHTTYPE DHT22

int ldrPin = A0;   // Analog pin
int ldrValue = 0;


DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "LOVE U 3000";
const char *password = "AVATARRR";


WiFiClient client;


long MyChannelNumber = 3216174;
const char myWriteAPIKey[] = "TVKN337NV4M284CZ";

float t = 0.0;
float h = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.print("connecting to.....");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }


  dht.begin();

  delay(2000);

  ThingSpeak.begin(client);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(5000);

  t = dht.readTemperature();
  h = dht.readHumidity();
  ldrValue = analogRead(ldrPin);  // Read light level
  int lightPercent = map(ldrValue, 0, 1023, 0, 100);

  if(isnan(t)|| isnan(h)){
    Serial.println("Failed to read from DHT sensor");
    }

  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, lightPercent);

  ThingSpeak.writeFields(MyChannelNumber, myWriteAPIKey);

  delay(5000);
}
