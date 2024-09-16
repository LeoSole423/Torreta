#include <Arduino.h>
#include <Arduino.h>
#include <AccelStepper.h>

// Definir los pines para los drivers A4988
// Motor 1 (eje X)
#define PIN_STEP1 26
#define PIN_DIR1  25

// Motor 2 (eje Y)
#define PIN_STEP2 12
#define PIN_DIR2  14

// Crear instancias de AccelStepper para cada motor
AccelStepper StepperY(AccelStepper::DRIVER, PIN_STEP1, PIN_DIR1); // Horizontal
AccelStepper StepperX(AccelStepper::DRIVER, PIN_STEP2, PIN_DIR2); // Vertical

void setup() {
  // Configuración de velocidad y aceleración para ambos motores
  StepperY.setMaxSpeed(800);    // Máxima velocidad en pasos por segundo (Motor 1 - Horizontal)
  StepperY.setAcceleration(400); // Aceleración en pasos por segundo^2 (Motor 1)
  
  StepperX.setMaxSpeed(600);    // Máxima velocidad en pasos por segundo (Motor 2 - Vertical)
  StepperX.setAcceleration(300); // Aceleración en pasos por segundo^2 (Motor 2)
}

void loop() {
  // Rutina del faro de vigilancia simulando diferentes posiciones
  // Paso 1: Mover a posición (derecha, arriba)
  StepperY.moveTo(200);  // Derecha en eje horizontal
  StepperX.moveTo(100);  // Arriba en eje vertical
  
  while (StepperY.distanceToGo() != 0 || StepperX.distanceToGo() != 0) {
    StepperY.run();
    StepperX.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 2: Mover a posición (izquierda, abajo)
  StepperY.moveTo(0);  // Izquierda en eje horizontal
  StepperX.moveTo(0);  // Abajo en eje vertical
  
  while (StepperY.distanceToGo() != 0 || StepperX.distanceToGo() != 0) {
    StepperY.run();
    StepperX.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 3: Mover a posición (centro, arriba)
  StepperY.moveTo(-200);    // Centro en eje horizontal
  StepperX.moveTo(-100); // Arriba en eje vertical
  
  while (StepperY.distanceToGo() != 0 || StepperX.distanceToGo() != 0) {
    StepperY.run();
    StepperX.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 4: Mover a posición (derecha, abajo)
  StepperY.moveTo(-200);  // Derecha en eje horizontal
  StepperX.moveTo(100); // Abajo en eje vertical
  
  while (StepperY.distanceToGo() != 0 || StepperX.distanceToGo() != 0) {
    StepperY.run();
    StepperX.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 5: Mover a posición (izquierda, arriba)
  StepperY.moveTo(0); // Izquierda en eje horizontal
  StepperX.moveTo(0);  // Arriba en eje vertical
  
  while (StepperY.distanceToGo() != 0 || StepperX.distanceToGo() != 0) {
    StepperY.run();
    StepperX.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Repetir el ciclo de posiciones
}
