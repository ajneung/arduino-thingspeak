#include <DHT.h>


// dht 22
#define DHTPIN 14
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE); 


//SOil sensor
int sensorPin = A0;



void setup() {
  Serial.begin(9600);
  dht.begin();
 
}

void loop () {

  //Get Humid and Temperature in the AIR from DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String temp = (String) t;
  String hum = (String) h; 

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  

  //Get Soil humid value
  int sensorValue;
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 100);
  Serial.print("Soil moisture: ");
  Serial.print(sensorValue);
  Serial.println(" %");

  delay(1000);
}
