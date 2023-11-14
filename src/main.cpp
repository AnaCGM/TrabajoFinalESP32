#include <Arduino.h>

const int fotoResistencia1 = 34; // Pin para el primer sensor de luz (fotoresistencia)
const int LED1 = 2; // Pin para el primer LED de iluminación
const int fotoResistencia2 = 35;
const int LED2 = 16; 

unsigned long tiempoInicio = 0; // Variable para almacenar el tiempo de inicio
unsigned long tiempoTranscurrido = 0; // Variable para guardar el tiempo total transcurrido
const float altura = 0.14; // Metros
long aceleracion = 0;

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  digitalWrite(LED1, HIGH); // Enciende LED
  digitalWrite(LED2, HIGH);

  int analog_value1 = analogRead(fotoResistencia1); // Lee el valor de la fotoresistencia
  int iluminacion1 = map(analog_value1, 0, 4095, 0, 100);
  int analog_value2 = analogRead(fotoResistencia2);
  int iluminacion2 = map(analog_value2, 0, 4095, 0, 100);

  delay(1);

  if (iluminacion1 > 85 && tiempoInicio == 0 && millis() > 5000) {
    tiempoInicio = millis(); // Inicia el contador de tiempo
  }

  if (iluminacion2 > 85 && tiempoInicio != 0) {
    tiempoTranscurrido = (millis() - tiempoInicio); // Finaliza contador de tiempo y convierte a segundos
    tiempoInicio = 0; // Reinicia el contador de tiempo
  }

  if(tiempoTranscurrido != 0){
    tiempoTranscurrido /= 1000;
    aceleracion = (2 * altura) / (tiempoTranscurrido * tiempoTranscurrido);
    Serial.print("El recorrido tomó ");
    Serial.print(tiempoTranscurrido*1000); // muestra con 2 decimales
    Serial.println(" segundos.");
    Serial.print("La aceleración es ");
    Serial.print(aceleracion);
    Serial.println(" metros/segundos^2.");
    tiempoTranscurrido = 0;
  }

  

}
