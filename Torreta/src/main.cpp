#include <Arduino.h>
#include <Arduino.h>
#include <AccelStepper.h>

// Definir los pines para el primer driver A4988 (Eje horizontal - Izquierda/Derecha)
#define PIN_STEP_1 26
#define PIN_DIR_1  25

// Definir los pines para el segundo driver A4988 (Eje vertical - Arriba/Abajo)
#define PIN_STEP_2 24
#define PIN_DIR_2  23

// Crear instancias de AccelStepper para cada motor
AccelStepper stepper1(AccelStepper::DRIVER, PIN_STEP_1, PIN_DIR_1); // Horizontal
AccelStepper stepper2(AccelStepper::DRIVER, PIN_STEP_2, PIN_DIR_2); // Vertical

void setup() {
  // Configuración de velocidad y aceleración para ambos motores
  stepper1.setMaxSpeed(800);    // Máxima velocidad en pasos por segundo (Motor 1 - Horizontal)
  stepper1.setAcceleration(400); // Aceleración en pasos por segundo^2 (Motor 1)
  
  stepper2.setMaxSpeed(600);    // Máxima velocidad en pasos por segundo (Motor 2 - Vertical)
  stepper2.setAcceleration(300); // Aceleración en pasos por segundo^2 (Motor 2)
}

void loop() {
  // Rutina del faro de vigilancia simulando diferentes posiciones
  // Paso 1: Mover a posición (derecha, arriba)
  stepper1.moveTo(200);  // Derecha en eje horizontal
  stepper2.moveTo(100);  // Arriba en eje vertical
  
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 2: Mover a posición (izquierda, abajo)
  stepper1.moveTo(0);  // Izquierda en eje horizontal
  stepper2.moveTo(0);  // Abajo en eje vertical
  
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 3: Mover a posición (centro, arriba)
  stepper1.moveTo(-200);    // Centro en eje horizontal
  stepper2.moveTo(-100); // Arriba en eje vertical
  
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 4: Mover a posición (derecha, abajo)
  stepper1.moveTo(-200);  // Derecha en eje horizontal
  stepper2.moveTo(100); // Abajo en eje vertical
  
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Paso 5: Mover a posición (izquierda, arriba)
  stepper1.moveTo(0); // Izquierda en eje horizontal
  stepper2.moveTo(0);  // Arriba en eje vertical
  
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }
  delay(500); // Pausa en esa posición para alumbrar

  // Repetir el ciclo de posiciones
}
