#include <EEPROM.h>
int posEscrLuzAmb = 52;
int luz;
int PIN_LUZ_AMB = A1;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 10; i++) {
    delay(500);
  }
}

void loop() {
  grabar1ValorMasLuzAmb();
  delay(2000);

  if(posEscrLuzAmb >= 65) while(1);
  
}

void grabar1ValorMasLuzAmb() {

  
  byte luz = map(analogRead(PIN_LUZ_AMB), 0, 1023, 100, 0);
  EEPROM.put(posEscrLuzAmb,luz);
  posEscrLuzAmb++;
  Serial.println(luz);
  
}
