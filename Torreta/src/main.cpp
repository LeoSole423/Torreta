#include <Arduino.h>
#include <AccelStepper.h>

// Definir los pines para los drivers A4988
// Motor 1 (eje X)
#define PIN_STEP1 3
#define PIN_DIR1  4

// Motor 2 (eje Y)
#define PIN_STEP2 6
#define PIN_DIR2  7

// Crear instancias de AccelStepper para cada motor
AccelStepper motor1(AccelStepper::DRIVER, PIN_STEP1, PIN_DIR1);
AccelStepper motor2(AccelStepper::DRIVER, PIN_STEP2, PIN_DIR2);

// Variables para las posiciones X e Y
int posicionX = 0;  // Rango de -100 a 100
int posicionY = 0;  // Rango de -100 a 100

// Función para configurar los motores
void configurarMotores() {
  motor1.setMaxSpeed(1000);    // Velocidad máxima en pasos por segundo
  motor1.setAcceleration(500); // Aceleración en pasos por segundo^2

  motor2.setMaxSpeed(1000);    // Velocidad máxima para el segundo motor
  motor2.setAcceleration(500); // Aceleración para el segundo motor

  // Iniciar comunicación serial para imprimir mensajes
  Serial.begin(9600);
  while (!Serial) {
    ; // Esperar a que se conecte la consola serial
  }
  Serial.println("Iniciando motores...");
}

// Función para mover los motores según la posición actual
void moverMotores(int x, int y) {
  Serial.print("Moviendo motores... ");
  if (x != 0) {
    Serial.print("Posicion X: ");
    Serial.print(x);
    Serial.print(" pasos. ");
    motor1.move(-x); // Mueve el motor 1 para llevar posicionX a 0
  }
  
  if (y != 0) {
    Serial.print("Posicion Y: ");
    Serial.print(y);
    Serial.println(" pasos.");
    motor2.move(-y); // Mueve el motor 2 para llevar posicionY a 0
  }

  // Ejecutar el movimiento de ambos motores
  while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0) {
    motor1.run();
    motor2.run();
  }

  // Una vez movidos, las posiciones vuelven a 0
  posicionX = 0;
  posicionY = 0;
  Serial.println("Motores en posicion de origen (X=0, Y=0).");
}

void setup() {
  configurarMotores(); // Configurar la velocidad y aceleración de los motores
}

void loop() {
  // Simulación de cambios en las posiciones X e Y
  // Aquí puedes actualizar las variables posicionX y posicionY con valores entre -100 y 100
  posicionX = random(-100, 101);  // Valor aleatorio entre -100 y 100
  posicionY = random(-100, 101);  // Valor aleatorio entre -100 y 100

  // Imprimir las nuevas posiciones
  Serial.print("Nuevas posiciones: X = ");
  Serial.print(posicionX);
  Serial.print(", Y = ");
  Serial.println(posicionY);

  // Verificar si hay un cambio en la posición
  if (posicionX != 0 || posicionY != 0) {
    moverMotores(posicionX, posicionY);  // Mover los motores
  } else {
    Serial.println("Los motores no se moverán (ambas posiciones son 0).");
  }

  delay(5000);  // Pausa de 1 segundo antes de la próxima actualización
}
