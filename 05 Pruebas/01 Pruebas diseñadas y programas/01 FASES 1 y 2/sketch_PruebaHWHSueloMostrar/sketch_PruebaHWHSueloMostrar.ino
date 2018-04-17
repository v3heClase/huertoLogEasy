#include <EEPROM.h>

int posLectHumSuelo = 169; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  int cont = 1;
  while (cont <= 13) {
    mostrar1ValorMasHumSuelo();
    cont++;
    delay(10);
  }
  while(1);
}

void mostrar1ValorMasHumSuelo() {
  int humedadSuelo;
  EEPROM.get(posLectHumSuelo, humedadSuelo);
  Serial.print("Humedad suelo = ");
  Serial.print(humedadSuelo);
  Serial.println("%");
  posLectHumSuelo = posLectHumSuelo + sizeof(int);
}
