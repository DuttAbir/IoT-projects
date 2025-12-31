#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
// #include <NTPClient.h>
// #include <WiFiUdp.h>
#include <ThingSpeak.h>

#define DHTPIN 2
#define DHTTYPE DHT22
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64

// Adafruit_SSD1306 display (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "LOVE U 3000";
const char *password = "AVATARRR";

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org");

// String Weekdays[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
// String Months[12]= {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

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
  // timeClient.begin();
  // timeClient.setTimeOffset(19800);



  dht.begin();
  // if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
  //   Serial.println("Allocation Failed");
  //   for(;;);
  //   }
   delay(2000);

  //  display.clearDisplay();
  //  display.setTextColor(WHITE);

   ThingSpeak.begin(client);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(5000);

  // timeClient.update();

  // int currentHour= timeClient.getHours();
  // int currentMinute= timeClient.getMinutes();


  t = dht.readTemperature();
  h = dht.readHumidity();

  if(isnan(t)|| isnan(h)){
    Serial.println("Failed to read from DHT sensor");
    }

  // display.clearDisplay();

  // Serial.print("Temperature : ");
  // Serial.print(t);
  // Serial.println("°C");

  // Serial.print("Humidity : ");
  // Serial.print(h);
  // Serial.println(" %");

  // display.setTextSize(1);
  // display.setCursor(62,0);
  // display.print(":");
  // display.setTextSize(1);
  // display.setCursor(68,0);
  // display.print(currentMinute);

  // if(currentHour >= 00 && currentHour <12){
  //   display.setTextSize(1);
  //   display.setCursor(50,0);
  //   display.print(currentHour);
  //   display.setTextSize(1);
  //   display.setCursor(85,0);
  //   display.print("AM");
  //   }
  // else if(currentHour >= 12){
  //   display.setTextSize(1);
  //   display.setCursor(50,0);
  //   display.print(currentHour-12);
  //   display.setTextSize(1);
  //   display.setCursor(85,0);
  //   display.print("PM");
  //   }


  // time_t epochTime = timeClient.getEpochTime();

  // String Weekday = Weekdays[timeClient.getDay()];

  // struct tm *ptm = gmtime((time_t *)&epochTime);

  // int MonthDay = ptm->tm_mday;

  // int Month = ptm->tm_mon+1;
  // String currentMonth = Months[Month-1];

  // int currentYear = ptm->tm_year+1900;

  // String currentDate = String(MonthDay) + "-" + String(currentMonth) + "-" + String(currentYear);


  // display.setTextSize(1);
  // display.setCursor(10,9);
  // display.print(Weekday);
  // display.setTextSize(1);
  // display.setCursor(40,9);
  // display.print(currentDate);



  // display.setTextSize(1);
  // display.setCursor(0,20);
  // display.print("Temp: ");

  // display.setTextSize(2);
  // display.setCursor(45,20);
  // display.print(t);

  // display.setTextSize(1);
  // display.cp437(true);

  // display.setTextSize(1);
  // display.print("C");


  // display.setTextSize(1);
  // display.setCursor(0,45);
  // display.print("HMDTY: ");

  // display.setTextSize(2);
  // display.setCursor(45,45);
  // display.print(h);

  // display.setTextSize(1);
  // display.print("%");
  

  // display.display();

  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);

  ThingSpeak.writeFields(MyChannelNumber, myWriteAPIKey);

  delay(5000);
}
