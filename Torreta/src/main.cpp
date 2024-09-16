#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Configura el nombre de tu red WiFi y la contraseña
const char* ssid = "Nico";
const char* password = "pruebaesp";

// Crea un servidor web en el puerto 80
WebServer server(80);

// Función para mostrar la página web
void handleRoot() {
  // HTML para los botones de control
  String html = "<html><head><title>Control de Movimiento</title></head><body>";
  html += "<h1>Control de Movimiento</h1>";
  html += "<button onclick=\"location.href='/up'\">Arriba</button><br>";
  html += "<button onclick=\"location.href='/left'\">Izquierda</button>";
  html += "<button onclick=\"location.href='/right'\">Derecha</button><br>";
  html += "<button onclick=\"location.href='/down'\">Abajo</button>";
  html += "</body></html>";
  
  // Enviar la página web al cliente
  server.send(200, "text/html", html);
}

// Funciones para manejar las acciones de movimiento
void handleUp() {
  Serial.println("Arriba");
  // Aquí puedes agregar el código para mover el motor hacia arriba
  server.send(200, "text/html", "Moviendo hacia arriba");
}

void handleDown() {
  Serial.println("Abajo");
  // Aquí puedes agregar el código para mover el motor hacia abajo
  server.send(200, "text/html", "Moviendo hacia abajo");
}

void handleLeft() {
  Serial.println("Izquierda");
  // Aquí puedes agregar el código para mover el motor hacia la izquierda
  server.send(200, "text/html", "Moviendo hacia la izquierda");
}

void handleRight() {
  Serial.println("Derecha");
  // Aquí puedes agregar el código para mover el motor hacia la derecha
  server.send(200, "text/html", "Moviendo hacia la derecha");
}

void setup() {
  // Iniciar la comunicación serie para ver la depuración
  Serial.begin(115200);

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
  server.on("/up", handleUp);      // Acción para mover arriba
  server.on("/down", handleDown);  // Acción para mover abajo
  server.on("/left", handleLeft);  // Acción para mover izquierda
  server.on("/right", handleRight);// Acción para mover derecha

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  // Manejar las peticiones del servidor web
  server.handleClient();
}
