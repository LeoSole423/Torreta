#include <Arduino.h>
#include <AccelStepper.h>

#define PIN_STEP1 26
#define PIN_DIR1 25
#define PIN_STEP2 12
#define PIN_DIR2 14

AccelStepper Motorabajo(AccelStepper::DRIVER, PIN_STEP1, PIN_DIR1);
int movimiento = 0; // Comenzar con el primer movimiento
AccelStepper Motorabajo2(AccelStepper::DRIVER, PIN_STEP2, PIN_DIR2);
int movimiento2 = 0; // Comenzar con el primer movimiento

void setup() {
    Serial.begin(115200);
    Motorabajo.setSpeed(50);
    Motorabajo.setAcceleration(100);
    Motorabajo.setMaxSpeed(100); //VELOCIDADES ESTAN CORRECTAS
    Motorabajo.moveTo(75); // Posición inicial CORRECTA
    Motorabajo2.setSpeed(50);
    Motorabajo2.setAcceleration(100);
    Motorabajo2.setMaxSpeed(100); //VELOCIDADES ESTAN CORRECTAS
    Motorabajo2.moveTo(400); // Posición inicial CORRECTA
    delay(1000);
    Serial.print("esta en setup");
}

void perimergiroarriba() {
    Motorabajo.moveTo(75); // Mueve 200 pasos desde la posición actual
}
void primergiroabajo(){
    Motorabajo2.moveTo(400); // Mueve 200 pasos desde la posición actual
    Serial.print("esta en primergiro");
}

void vuelta() {
    Motorabajo.moveTo(-50); // Mueve -200 pasos desde la posición actual
}
void vueltaabajo(){
     Motorabajo2.moveTo(-400); // Mueve -200 pasos desde la posición actual
    Serial.print("esta en vuelta");
}

void decidemovimientoarriba() {
    if (movimiento > 2) {
        movimiento = 1; // Resetea el movimiento si supera el límite
    }
    switch (movimiento) {
        case 1:
            vuelta();
            break;
        case 2:
            perimergiroarriba();
            break;
        default:
            break;
    }
    Serial.print("esta en decide movimiento");
}
void decidemovimientoabajo() {
    if (movimiento2 > 2) {
        movimiento2 = 1; // Resetea el movimiento si supera el límite
    }
    switch (movimiento2) {
        case 1:
            vueltaabajo();
            break;
        case 2:
            primergiroabajo();
            break;
        default:
            break;
    }
    Serial.print("esta en decide movimiento");
}

void loop() {
    if (Motorabajo.distanceToGo() == 0) {
        movimiento++;
        decidemovimientoarriba();
        Serial.print("esta en if");
    }
    if (Motorabajo2.distanceToGo() == 0) {
        movimiento2++;
        decidemovimientoabajo();
        Serial.print("esta en if");
    }
    
    Motorabajo.run(); // Actualiza el estado del motor
    Motorabajo2.run();
   
}
