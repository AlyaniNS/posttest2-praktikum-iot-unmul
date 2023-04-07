#include <ESP8266WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>
#include "webserverPostTest2B5.h"; // file webserver
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
 
const int sampleWindow = 50;                              // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
#define SENSOR_PIN A0 // Pin Microphone
#define PIN_QUIET D3 // Pin LED merah
#define PIN_MODERATE D4 // Pin LED kuning
#define PIN_LOUD D5 // Pin LED hijau
 
const char *apiKey = "P6MZ3YVRLBOGTU0P"; // API key dari ThingSpeak
const char *ssid = "Universitas Mulawarman";     // SSID Kampus
const char *pass = "";

ESP8266WebServer server(80);

  void webpage()
  {
    server.send(200,"text/html", webserverPostTest2B5);
  }
 
void setup ()  
{   
  pinMode (SENSOR_PIN, INPUT);  
  pinMode(PIN_QUIET, OUTPUT);
  pinMode(PIN_MODERATE, OUTPUT);
  pinMode(PIN_LOUD, OUTPUT); 
 
  digitalWrite(PIN_QUIET, LOW);
  digitalWrite(PIN_MODERATE, LOW);
  digitalWrite(PIN_LOUD, LOW);
  
  Serial.begin(115200);
  lcd.init();
 
  // Menyalakan backlight LED
  lcd.backlight();
 
  Serial.println("Menyambungkan ke ");
  Serial.println(ssid);
  
  lcd.setCursor(0, 0); // LED baris atas
  lcd.print("Menyambungkan ke");
 
  lcd.setCursor(0, 1); // LED baris bawah
  lcd.print(ssid);
 
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
    Serial.println("WiFi terhubung");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", webpage);
    server.begin();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi terhubung");
    delay(4000);
    lcd.clear();
}  
 
   
void loop ()  
{ 
   unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            // value signal minimum 
   unsigned int signalMin = 1024;                         // value signal maksimum
 
                                                          // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(SENSOR_PIN);                    // Baca inputan dari sensor mic
      if (sample < 1024)                                  // Buang semua inputan signal diatas 1024
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // Simpan signal maksimum jika signal > 1024
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // Simpan signal minimum jika signal < 1024
         }
      }
   }
 
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   int db = map(peakToPeak,20,900,49.5,90);             // Kalibrasi desibel 
 
  lcd.setCursor(0, 0);
  lcd.print("Intensitas: ");
  lcd.print(db);
  lcd.print("dB");
  
  if (db <= 60)
  {
    lcd.setCursor(0, 1);
    lcd.print("Level: Sunyi");
    digitalWrite(PIN_QUIET, HIGH);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, LOW);
  }
  else if (db > 60 && db<85)
  {
    lcd.setCursor(0, 1);
    lcd.print("Level: Sedang");
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, HIGH);
    digitalWrite(PIN_LOUD, LOW);
  }
  else if (db>=85)
  {
    lcd.setCursor(0, 1);
    lcd.print("Level: Tinggi");
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, HIGH);
 
  }
  
  server.handleClient(); 

   delay(1000);      
   lcd.clear();
}
