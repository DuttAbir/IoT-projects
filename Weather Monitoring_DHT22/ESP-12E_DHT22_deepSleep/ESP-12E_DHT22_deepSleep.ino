#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include"C:\Users\dutta\Documents\IoT_projects\Weather Monitoring_DHT22\info.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
const char *SSID = ssid();
const char *password = Pass();

WiFiClient client;
long MyChannelNumber = channelID();
const char* myWriteAPIKey = writeAPI();

void setup() {
  dht.begin();
  
  float tempSum = 0;
  float humSum = 0;
  long ldrSum = 0;
  int sampleCount = 40; // 40 samples * 15 seconds = 10 minutes

  // Data collection loop
  for (int i = 0; i < sampleCount; i++) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    int l = analogRead(A0);

    if (!isnan(t) && !isnan(h)) {
      tempSum += t;
      humSum += h;
      ldrSum += l;
    } else {
      i--; // Retry sample if sensor fails
    }
    delay(15000); 
  }

  // Calculate averages
  float avgTemp = tempSum / sampleCount;
  float avgHum = humSum / sampleCount;
  int avgLdrPercent = map(ldrSum / sampleCount, 0, 1023, 0, 100);

  // Connect and Upload
  WiFi.begin(SSID, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  ThingSpeak.begin(client);
  ThingSpeak.setField(1, (float)avgTemp);
  ThingSpeak.setField(2, (float)avgHum);
  ThingSpeak.setField(3, avgLdrPercent);

  ThingSpeak.writeFields(MyChannelNumber, myWriteAPIKey);

  // Deep Sleep for 20 minutes (20m * 60s * 1,000,000us)
  ESP.deepSleep(1200000000ULL); 
}

void loop() {
  // Not used in Deep Sleep setups
}