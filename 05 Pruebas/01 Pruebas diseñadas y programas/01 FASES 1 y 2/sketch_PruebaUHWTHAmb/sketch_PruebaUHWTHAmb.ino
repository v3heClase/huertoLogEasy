#include "DHT.h"
#define DHTPIN 6
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.print("ARDUINO: Prueba");
  delay(3000);

}

void loop() {
  int dato;
  delay(4000);

  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  Serial.print("Humedad: ");
  Serial.println(humedad);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);
}
