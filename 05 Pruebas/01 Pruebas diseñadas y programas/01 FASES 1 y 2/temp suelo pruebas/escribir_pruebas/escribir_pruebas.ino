#include <EEPROM.h>
#include <OneWire.h>
//#define ESPERA_INICIAL 2000
//#define ESPERA_INICIAL 36000000
#define ESPERA_MEDIDAS 10000
//#define ESPERA_MEDIDAS 7200000

const int PIN_TEMP_SUELO = 3; //DS18S20 Signal pin on digital 3

//Temperature chip i/o
OneWire sensorTempSuelo(PIN_TEMP_SUELO);  // on digital pin 3

void setup(void) {
  Serial.begin(9600);
  
}
float temperature = 0;
void loop(void) {
   grabar1ValorMasTempSuelo();
   delay(2000);
  }


  int posEscrTempSuelo= 0;


 
  
  void grabar1ValorMasTempSuelo() {
     if(posEscrTempSuelo <= 39){
       temperature= getTemp();
       EEPROM.put(posEscrTempSuelo,temperature);
       posEscrTempSuelo = posEscrTempSuelo + sizeof(float);
     }else{
      exit(0);
     }
 
}
float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !sensorTempSuelo.search(addr)) {
      //no more sensors on chain, reset search
      sensorTempSuelo.reset_search();
      Serial.println("NO hay sensores en la cadena!");
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.println("Device is not recognized");
      return -1000;
  }

  sensorTempSuelo.reset();
  sensorTempSuelo.select(addr);
  sensorTempSuelo.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = sensorTempSuelo.reset();
  sensorTempSuelo.select(addr);   
  sensorTempSuelo.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = sensorTempSuelo.read();
  }
  
  sensorTempSuelo.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float temperatureSum = tempRead / 16;
  
  return temperatureSum;
  
  
}
