#include <EEPROM.h>

int numMedida=1;

int posEscrLuzAmb = 52;
int posEscrTempAmb = 65;
int posEscrHumAmb = 117;
int posEscrHumSuelo = 169;
int posEscrTempSuelo = 0;

 
void setup() {
  
  for (int i=1; numMedida<=13; i++){
    
      byte luz = i;
      EEPROM.put(posEscrLuzAmb, luz);
      posEscrLuzAmb++;
      
      float humedad = i;
      EEPROM.put(posEscrHumAmb,humedad);
      posEscrHumAmb=posEscrHumAmb+4;

      float temperatura = i;
      EEPROM.put(posEscrTempAmb,temperatura);
      posEscrTempAmb=posEscrTempAmb+4;

      float temperature= i;
      EEPROM.put(posEscrTempSuelo,temperature);
      posEscrTempSuelo = posEscrTempSuelo + sizeof(float);

      int humedadSuelo = i;
      EEPROM.put(posEscrHumSuelo, humedadSuelo);
      posEscrHumSuelo =  posEscrHumSuelo + sizeof(int);

      numMedida++;      
  }

}

void loop() {
  

}
