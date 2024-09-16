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
AccelStepper motor1(AccelStepper::DRIVER, PIN_STEP1, PIN_DIR1);
AccelStepper motor2(AccelStepper::DRIVER, PIN_STEP2, PIN_DIR2);

// Configuración de la red WiFi
const char* ssid = "Nico";
const char* password = "pruebaesp";

// Crear un servidor web en el puerto 80
WebServer server(80);

// Variables para las posiciones X e Y (en porcentaje de -100% a 100%)
int posicionX = 0;  // Porcentaje en el eje X (rango de -100 a 100)
int posicionY = 0;  // Porcentaje en el eje Y (rango de -100 a 100)

// Definir el número máximo de pasos que corresponde al 100% de movimiento
const int maxPasos = 200; // Ajustar este valor según el desplazamiento máximo de tus motores

// Función para configurar los motores
void configurarMotores() {
  motor1.setMaxSpeed(1000);    // Velocidad máxima en pasos por segundo
  motor1.setAcceleration(200); // Aceleración en pasos por segundo^2

  motor2.setMaxSpeed(1000);    // Velocidad máxima para el segundo motor
  motor2.setAcceleration(200); // Aceleración para el segundo motor

  // Iniciar comunicación serial para imprimir mensajes
  Serial.begin(115200);
  Serial.println("Iniciando motores...");
}

// Función para convertir porcentaje a pasos
int porcentajeAPasos(int porcentaje) {
  return (porcentaje * maxPasos) / 100;
}

// Función para mover los motores según la posición actual (en porcentaje)
void moverMotores(int x, int y) {
  // Convertir porcentaje a pasos
  int pasosX = porcentajeAPasos(x);
  int pasosY = porcentajeAPasos(y);

  if (x != 0) {
    motor1.move(pasosX); // Mueve el motor 1 en X
  }
  
  if (y != 0) {
    motor2.move(pasosY); // Mueve el motor 2 en Y
  }

  // Ejecutar el movimiento de ambos motores
  while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0) {
    motor1.run();
    motor2.run();
  }

  // Resetear posiciones
  posicionX = 0;
  posicionY = 0;
}

// Función para manejar la página web de control
void handleRoot() {
  String html = "<html><head><title>Control de Motores</title>";
  html += "<script>";
  html += "function sendCommand(cmd) {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.open('GET', cmd, true);";
  html += "xhttp.send();";
  html += "}";
  html += "</script>";
  html += "</head><body>";
  html += "<h1>Control de Movimiento</h1>";
  html += "<button onclick=\"sendCommand('/up')\">Arriba</button><br>";
  html += "<button onclick=\"sendCommand('/left')\">Izquierda</button>";
  html += "<button onclick=\"sendCommand('/right')\">Derecha</button><br>";
  html += "<button onclick=\"sendCommand('/down')\">Abajo</button>";
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
  moverMotores(-MOVE_STEPS, 0); // Mueve el motor en el eje X hacia la izquierda
  server.send(204, "text/plain", "");  // Respuesta sin contenido
}

void handleRight() {
  Serial.println("Moviendo Derecha");
  moverMotores(MOVE_STEPS, 0);  // Mueve el motor en el eje X hacia la derecha
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
