#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DHT.h>

const char* ssid     = "*********************************************";
const char* pass = "*************************************************";

// dht 22
#define DHTPIN 14
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE); 


//SOil sensor
int sensorPin = A0;


// ThingSpeak Settings //
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "********************************"; //API Key
WiFiClient client;

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, pass);
   
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("IP address.....");
  Serial.println(WiFi.localIP());

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

  
}

void loop () {

  //Get Humid and Temperature in the AIR from DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String tem = (String) t;
  String hum = (String) h; 

  //Get Soil humid value
  int sensorValue;
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 100);
  //Serial.print("Soil moisture: ");
  //Serial.print(sensorValue);
  //Serial.println(" %");
  
  
  String data = "field1=" + hum + "&field2=" + tem + "&field3="+sensorValue; 
  Serial.println("xxx " + data);
  Serial.println("begin send data.....");
  
  if (client.connect(thingSpeakAddress, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data); //data
  }
  Serial.println(data);
  delay(1000);
}
