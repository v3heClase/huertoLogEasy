// LIBRERÍAS
#include <EEPROM.h>

// Control del numero de datos guardados
#define NUM_MAX_MEDIDAS 13

//Posiciones de lectura
int posLectLuzAmb = 52;
int posLectTempAmb = 65;
int posLectHumAmb = 117;
int posLectHumSuelo = 169;
int posLectTempSuelo = 0;


void setup() {
  //Iniciar monitor serie
  Serial.begin(9600);
  // Ver valores
  mostrarTodosValoresLuzAmb();
  mostrarTodosValoresTempAmb();
  mostrarTodosValoresHumAmb();
  mostrarTodosValoresHumSuelo();
  mostrarTodosValoresTempSuelo();
}

void loop() {  
   
}

void mostrarTodosValoresLuzAmb(){
  for (int i=0; i<NUM_MAX_MEDIDAS; i++){
    mostrar1ValorMasLuzAmb();
  }
}

void mostrarTodosValoresTempAmb(){
  for (int i=0; i<NUM_MAX_MEDIDAS; i++){
    mostrar1ValorMasTempAmb();
  }
}

void mostrarTodosValoresHumAmb(){
  for (int i=0; i<NUM_MAX_MEDIDAS; i++){
    mostrar1ValorMasHumAmb();
  }
}

void mostrarTodosValoresHumSuelo(){
  for (int i=0; i<NUM_MAX_MEDIDAS; i++){
    mostrar1ValorMasHumSuelo();
  }
}

void mostrarTodosValoresTempSuelo(){
  for (int i=0; i<NUM_MAX_MEDIDAS; i++){
    mostrar1ValorMasTempSuelo();
  }
}

void mostrar1ValorMasLuzAmb(){
  byte luz;
  
  EEPROM.get(posLectLuzAmb, luz);
  Serial.print("Luz: ");
  Serial.print(luz);
  Serial.println(" %");
  posLectLuzAmb = posLectLuzAmb + 1;  
}

void mostrar1ValorMasTempAmb(){
  float temperatura;
  
  EEPROM.get(posLectTempAmb, temperatura);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  
  posLectTempAmb = posLectTempAmb + sizeof(float);
}

void mostrar1ValorMasHumAmb(){
  float humedad;
  
  EEPROM.get(posLectHumAmb, humedad);
  
  Serial.print("Humedad: "); 
  Serial.println(humedad);
  
  posLectHumAmb = posLectHumAmb + sizeof(float);
}

void mostrar1ValorMasHumSuelo(){
  int humedadSuelo;
  EEPROM.get(posLectHumSuelo, humedadSuelo);
  Serial.print("Humedad suelo = ");
  Serial.print(humedadSuelo);
  Serial.println("%");
  posLectHumSuelo = posLectHumSuelo + sizeof(int);
}

void mostrar1ValorMasTempSuelo(){
  float temperatura;
  EEPROM.get(posLectTempSuelo, temperatura);
  Serial.print("La temperatura del suelo es = ");
  Serial.println(temperatura); 
  posLectTempSuelo = posLectTempSuelo + 4;
}

