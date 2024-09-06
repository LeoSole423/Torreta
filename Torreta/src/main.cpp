#include <Arduino.h>

// Definir el pin del LED
const int ledPin = 2;

void setup() {
  // Configurar el pin del LED como salida
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Encender el LED
  digitalWrite(ledPin, HIGH);
  // Esperar 1000 milisegundos (1 segundo)
  delay(1000);
  
  // Apagar el LED
  digitalWrite(ledPin, LOW);
  // Esperar 1000 milisegundos (1 segundo)
  delay(1000);
}
