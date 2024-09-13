#include <Arduino.h>
#include <AccelStepper.h>

// Definir los pines para el primer driver A4988 (Motor 1)
#define PIN_STEP_1 26
#define PIN_DIR_1  25

// Definir los pines para el segundo driver A4988 (Motor 2)
#define PIN_STEP_2 35
#define PIN_DIR_2  34

// Crear instancias de AccelStepper para cada motor
AccelStepper stepper1(AccelStepper::DRIVER, PIN_STEP_1, PIN_DIR_1);
AccelStepper stepper2(AccelStepper::DRIVER, PIN_STEP_2, PIN_DIR_2);

void setup() {
  // Configuración de velocidad y aceleración para ambos motores
  stepper1.setMaxSpeed(1000);    // Máxima velocidad en pasos por segundo (Motor 1)
  stepper1.setAcceleration(500); // Aceleración en pasos por segundo^2 (Motor 1)
  
  stepper2.setMaxSpeed(1000);    // Máxima velocidad en pasos por segundo (Motor 2)
  stepper2.setAcceleration(500); // Aceleración en pasos por segundo^2 (Motor 2)
}

void loop() {
  // Mover ambos motores hacia adelante
  stepper1.moveTo(200); // Mover 2000 pasos hacia adelante (Motor 1)
  stepper2.moveTo(200); // Mover 2000 pasos hacia adelante (Motor 2)
  
  // Mientras ambos motores no lleguen a su destino
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run(); // Ejecutar movimiento para Motor 1
    stepper2.run(); // Ejecutar movimiento para Motor 2
  }

  delay(1000); // Esperar un segundo

  // Mover ambos motores hacia atrás
  stepper1.moveTo(0); // Mover de regreso a la posición 0 (Motor 1)
  stepper2.moveTo(0); // Mover de regreso a la posición 0 (Motor 2)
  
  // Mientras ambos motores no lleguen a su destino
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run(); // Ejecutar movimiento para Motor 1
    stepper2.run(); // Ejecutar movimiento para Motor 2
  }

  delay(1000); // Esperar un segundo
}
