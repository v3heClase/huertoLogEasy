// LIBRERÍAS
#include <EEPROM.h>
#include "DHT.h"
#include <OneWire.h>

// NÚCLEO GRABACIÓN
// Control del numero de datos guardados
int numMedida=1;
#define NUM_MAX_MEDIDAS 13

// Tiempos entre medidas e inicial
const unsigned long TIEMPO_ESPERA_INICIAL = 1000;//12*long(3600)*long(1000);        //ms
const unsigned long TIEMPO_ESPERA_ENTRE_MEDIDAS = 1000; //2*long(3600)*long(1000);    //ms

// OTROS MÓDULOS
// Luz ambiente
#define PIN_LUZ_AMB A1
int posEscrLuzAmb = 52;

// Común a temperatura ambiente y humedad ambiente
#define PIN_TEMP_HUM_AMB 6
#define DHTTYPE DHT22
DHT sensorTHAmb(PIN_TEMP_HUM_AMB, DHTTYPE);     // Objeto temperatura humedad ambiente

// Temperatura ambiente
int posEscrTempAmb = 65;

// Humedad ambiente
int posEscrHumAmb = 117;

// Humedad suelo
#define PIN_HUM_SUELO A2
int posEscrHumSuelo = 169;

// Temperatura suelo
#define PIN_TEMP_SUELO 3
int posEscrTempSuelo = 0;
OneWire sensorTempSuelo (PIN_TEMP_SUELO);     // Objeto temperatura suelo

// NÚCLEO GRABACIÓN
void setup() {
  // Pruebas ??
  Serial.begin(9600);

  // Iniciar objetos  
  sensorTHAmb.begin();
  //sensorTempSuelo.begin(); ??
  
  // Espera inicial
  delay(TIEMPO_ESPERA_INICIAL);
}

void loop() {
  // Llamar a las funciones de lectura de los sensores
  grabar1ValorMasLuzAmb();
  grabar1ValorMasTempAmb();
  grabar1ValorMasHumAmb();
  grabar1ValorMasHumSuelo();
  grabar1ValorMasTempSuelo();

  // Incremento contador medidas si son correctas
  numMedida++;

  // Posible bloqueo (en cuanto lee la última medida se bloquea)
  if(numMedida>NUM_MAX_MEDIDAS){
      Serial.println("Fin medidas");
      while(1);                                   // Deja parado el sistema cuando alcanza el numero de medidas. SUSTITUIR POR DORMIR SISTEMA      
  }
  
  //Tiempo espera entre medidas
  delay (TIEMPO_ESPERA_ENTRE_MEDIDAS);  
}


// FUNCIONES DISTINTOS SENSORES
// Humedad suelo
void grabar1ValorMasHumSuelo() {
  int humedadSuelo;
  humedadSuelo = analogRead(PIN_HUM_SUELO);
  humedadSuelo = map(humedadSuelo, 0, 1023, 100, 0);
  Serial.print(numMedida);
    Serial.print(" HumSuelo: ");
    Serial.println(humedadSuelo);
  EEPROM.put(posEscrHumSuelo, humedadSuelo);
  posEscrHumSuelo =  posEscrHumSuelo + sizeof(int);
}


// Luz
void grabar1ValorMasLuzAmb() {  
  byte luz = map(analogRead(PIN_LUZ_AMB), 0, 1023, 100, 0);
  Serial.print(numMedida);
    Serial.print(" LuzAmb: ");
    Serial.println(luz);
  EEPROM.put(posEscrLuzAmb, luz);
  posEscrLuzAmb++;
}

// Humedad ambiente
void grabar1ValorMasHumAmb(){
    float humedad = sensorTHAmb.readHumidity();
    Serial.print(numMedida);
    Serial.print(" humedadAmb: ");
    Serial.println(humedad);
    EEPROM.put(posEscrHumAmb,humedad);
    posEscrHumAmb=posEscrHumAmb+4;
}

// Temperatura ambiente
void grabar1ValorMasTempAmb(){
    float temperatura = sensorTHAmb.readTemperature();
    EEPROM.put(posEscrTempAmb,temperatura);
    Serial.print(numMedida);
    Serial.print(" TempAmb: ");
    Serial.println(temperatura);
    posEscrTempAmb=posEscrTempAmb+4;
}

// Temperatura del suelo
void grabar1ValorMasTempSuelo() {
  float temperature= getTemp();
  Serial.print(numMedida);
    Serial.print(" TempSuelo: ");
    Serial.println(temperature);
  EEPROM.put(posEscrTempSuelo,temperature);
  posEscrTempSuelo = posEscrTempSuelo + sizeof(float);
}

float getTemp(){
  // returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !sensorTempSuelo.search(addr)) {
      // no more sensors on chain, reset search
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

  float tempRead = ((MSB << 8) | LSB); // using two's compliment
  float temperatureSum = tempRead / 16;
  
  return temperatureSum;  
}
