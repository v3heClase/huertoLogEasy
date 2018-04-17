#include <EEPROM.h>

#define PIN_HUM_SUELO A2

int posEscrHumSuelo = 169;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int cont = 1;
  while (cont <= 13) {
    grabar1ValorMasHumSuelo();
    cont++;
    delay(1000); 
  }
  while(1);
}

void grabar1ValorMasHumSuelo() {
  int humedadSuelo;
  humedadSuelo = analogRead(PIN_HUM_SUELO);
  humedadSuelo = map(humedadSuelo, 0, 1023, 100, 0);
  EEPROM.put(posEscrHumSuelo, humedadSuelo);
  posEscrHumSuelo =  posEscrHumSuelo + sizeof(int);
}


