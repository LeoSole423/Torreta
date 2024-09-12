#include <Arduino.h>
#include <AccelStepper.h>

// Definir los pines para el driver A4988
#define PIN_STEP 26
#define PIN_DIR  25


// Crear una instancia de AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIR);

void setup() {
  // Configuración de velocidad y aceleración
  stepper.setMaxSpeed(1000);    // Máxima velocidad en pasos por segundo
  stepper.setAcceleration(500); // Aceleración en pasos por segundo^2
}

void loop() {
  // Mover el motor hacia adelante
  stepper.moveTo(2000); // Mover 2000 pasos hacia adelante
  while (stepper.distanceToGo() != 0) {
    stepper.run(); // Esta función debe llamarse repetidamente
  }

  delay(1000); // Esperar un segundo

  // Mover el motor hacia atrás
  stepper.moveTo(0); // Mover de regreso a la posición 0
  while (stepper.distanceToGo() != 0) {
    stepper.run(); // Esta función debe llamarse repetidamente
  }

  delay(1000); // Esperar un segundo
}
