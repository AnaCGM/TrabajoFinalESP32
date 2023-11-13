#include <Arduino.h>

const int fotoResistencia1 = 34; // Pin para el sensor de luz (fotoresistencia)
const int LED1 = 2; // Pin para el primer LED de iluminación
const int fotoResistencia2 = 35; // Pin para el sensor de luz (fotoresistencia)
const int LED2 = 16; // Pin para el primer LED de iluminación

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  int analog_value1 = analogRead(fotoResistencia1);
  int brightness1 = map(analog_value1, 0, 4095, 0, 100);
  int analog_value2 = analogRead(fotoResistencia2);
  int brightness2 = map(analog_value2, 0, 4095, 0, 100);
  
  delay(100);

}
