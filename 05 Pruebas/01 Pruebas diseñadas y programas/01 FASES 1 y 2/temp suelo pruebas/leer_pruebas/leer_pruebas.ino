#include <EEPROM.h>

  int posLectTempSuelo = 0;
void setup() {
  Serial.begin(9600);
  
 
}

void loop(){
  mostrar1ValorMasTempSuelo();
  


}


void mostrar1ValorMasTempSuelo(){
  float temperatura;
  if(posLectTempSuelo <= 39){
    EEPROM.get(posLectTempSuelo, temperatura);
    Serial.print("La temperatura del suelo es = ");
    Serial.println(temperatura); 
    posLectTempSuelo = posLectTempSuelo +4;
  }
     
  
  
}
