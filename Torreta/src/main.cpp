#include <Arduino.h>
#include <AccelStepper.h>
#include <WiFi.h>
#include <WebServer.h>

// Definir los pines para los drivers A4988
// Motor 1 (eje X)
#define PIN_STEP1 26
#define PIN_DIR1  25

// Motor 2 (eje Y)
#define PIN_STEP2 12
#define PIN_DIR2  14

#define MOVE_STEPS 10

// Crear instancias de AccelStepper para cada motor
AccelStepper StepperY(AccelStepper::DRIVER, PIN_STEP1, PIN_DIR1);
AccelStepper StepperX(AccelStepper::DRIVER, PIN_STEP2, PIN_DIR2);

// Configuración de la red WiFi
const char* ssid = "Nico";
const char* password = "pruebaesp";

// Crear un servidor web en el puerto 80
WebServer server(80);

// Función para configurar los motores
void configurarMotores() {
  StepperY.setMaxSpeed(1000);    // Velocidad máxima en pasos por segundo
  StepperY.setAcceleration(200); // Aceleración en pasos por segundo^2

  StepperX.setMaxSpeed(1000);    // Velocidad máxima para el segundo motor
  StepperX.setAcceleration(200); // Aceleración para el segundo motor

  // Iniciar comunicación serial para imprimir mensajes
  Serial.begin(115200);
  Serial.println("Iniciando motores...");
}

// Función para convertir porcentaje a pasos
int porcentajeAPasos(int porcentaje) {
  return (porcentaje * MOVE_STEPS) / 100;
}

// Función para mover los motores
void moverMotores(int x, int y) {
  if (x != 0) {
    StepperX.move(x); // Mueve el motor 1 en X
  }
  
  if (y != 0) {
    StepperY.move(y); // Mueve el motor 2 en Y
  }

  // Ejecutar el movimiento de ambos motores
  while (StepperY.distanceToGo() != 0 || StepperX.distanceToGo() != 0) {
    StepperY.run();
    StepperX.run();
  }
}

// Función para manejar la página web de control
void handleRoot() {
  String html = "<html><head><title>Control de Motores</title>";
  html += "<script>";
  html += "document.addEventListener('keydown', function(event) {";
  html += "if (event.key === 'ArrowUp') { sendCommand('/up'); }";
  html += "else if (event.key === 'ArrowDown') { sendCommand('/down'); }";
  html += "else if (event.key === 'ArrowLeft') { sendCommand('/left'); }";
  html += "else if (event.key === 'ArrowRight') { sendCommand('/right'); }";
  html += "});";
  html += "function sendCommand(cmd) {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.open('GET', cmd, true);";
  html += "xhttp.send();";
  html += "}";
  html += "</script>";
  html += "</head><body>";
  html += "<h1>Controla los motores con las flechas del teclado</h1>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

// Funciones para manejar las peticiones del servidor y mover los motores
void handleUp() {
  Serial.println("Moviendo Arriba");
  moverMotores(0, MOVE_STEPS);  // Mueve el motor en el eje Y hacia arriba
  server.send(204, "text/plain", "");  // Respuesta sin contenido
}

void handleDown() {
  Serial.println("Moviendo Abajo");
  moverMotores(0, -MOVE_STEPS); // Mueve el motor en el eje Y hacia abajo
  server.send(204, "text/plain", "");  // Respuesta sin contenido
}

void handleLeft() {
  Serial.println("Moviendo Izquierda");
  moverMotores(MOVE_STEPS, 0); // Mueve el motor en el eje X hacia la izquierda
  server.send(204, "text/plain", "");  // Respuesta sin contenido
}

void handleRight() {
  Serial.println("Moviendo Derecha");
  moverMotores(-MOVE_STEPS, 0);  // Mueve el motor en el eje X hacia la derecha
  server.send(204, "text/plain", "");  // Respuesta sin contenido
}

void setup() {
  configurarMotores(); // Configurar velocidad y aceleración de los motores

  // Conectar a la red WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Imprimir la IP asignada
  Serial.println("");
  Serial.println("Conectado a WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Configurar las rutas del servidor web
  server.on("/", handleRoot);      // Página principal
  server.on("/up", handleUp);      // Mover hacia arriba
  server.on("/down", handleDown);  // Mover hacia abajo
  server.on("/left", handleLeft);  // Mover hacia izquierda
  server.on("/right", handleRight);// Mover hacia derecha

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  // Manejar las peticiones del servidor web
  server.handleClient();
}
