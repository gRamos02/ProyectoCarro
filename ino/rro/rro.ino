#include <SoftwareSerial.h>

// Declaración de pines para SoftwareSerial (Bluetooth)
SoftwareSerial Bluetooth(2, 3);  // RX = 2, TX = 3

// Pines del motor A (derecha)
const int motorAIn1 = 8;
const int motorAIn2 = 7;
const int motorAEnable = 9;

// Pines del motor B (izquierda)
const int motorBIn3 = 13;
const int motorBIn4 = 12;
const int motorBEnable = 11;

void setup() {
  Serial.begin(9600);        // Comunicación serial para el monitor serial
  Bluetooth.begin(9600);     // Configuración del Bluetooth
  pinMode(motorAIn1, OUTPUT);
  pinMode(motorAIn2, OUTPUT);
  pinMode(motorAEnable, OUTPUT);
  pinMode(motorBIn3, OUTPUT);
  pinMode(motorBIn4, OUTPUT);
  pinMode(motorBEnable, OUTPUT);

  Serial.println("Bluetooth listo. Esperando comandos...");
}
 
void loop() {
  // Comprobamos si hay datos recibidos desde el Bluetooth
  if (Bluetooth.available()) {
    char command = Bluetooth.read();  // Leer el carácter enviado por Bluetooth
    command = tolower(command);       // Convertir a minúscula para evitar problemas con mayúsculas

    if (command == 'e') {
      MotorHorario();
      Serial.println("Motores girando hacia adelante");
      Bluetooth.println("Motores girando hacia adelante");
    } 
    else if (command == 'r') {
      MotorAntihorario();
      Serial.println("Motores girando en reversa");
      Bluetooth.println("Motores girando en reversa");
    } 
    else if (command == 's') {
      MotorStop();
      Serial.println("Motores detenidos");
      Bluetooth.println("Motores detenidos");
    }
    else if (command == 'i') {  // Girar a la izquierda
      MotorIzquierda();
      Serial.println("Girando a la izquierda");
      Bluetooth.println("Girando a la izquierda");
    }
    else if (command == 'd') {  // Girar a la derecha
      MotorDerecha();
      Serial.println("Girando a la derecha");
      Bluetooth.println("Girando a la derecha");
    }
  }
}

// Función para girar los motores hacia adelante (horario)
void MotorHorario() {
  // Motor A adelante
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, HIGH);
  digitalWrite(motorAEnable, HIGH);

  // Motor B adelante
  digitalWrite(motorBIn3, HIGH);
  digitalWrite(motorBIn4, LOW);
  digitalWrite(motorBEnable, HIGH);
}

// Función para girar los motores en reversa (antihorario)
void MotorAntihorario() {
  // Motor A reversa
  digitalWrite(motorAIn1, HIGH);
  digitalWrite(motorAIn2, LOW);
  digitalWrite(motorAEnable, HIGH);

  // Motor B reversa
  digitalWrite(motorBIn3, LOW);
  digitalWrite(motorBIn4, HIGH);
  digitalWrite(motorBEnable, HIGH);
}

// Función para girar a la izquierda
void MotorIzquierda() {
  // Motor A adelante
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, HIGH);
  digitalWrite(motorAEnable, HIGH);

  // Detener Motor B
  digitalWrite(motorBIn3, LOW);
  digitalWrite(motorBIn4, LOW);
  digitalWrite(motorBEnable, LOW);
}

// Función para girar a la derecha
void MotorDerecha() {
  // Detener Motor A
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, LOW);
  digitalWrite(motorAEnable, LOW);

  // Motor B adelante
  digitalWrite(motorBIn3, HIGH);
  digitalWrite(motorBIn4, LOW);
  digitalWrite(motorBEnable, HIGH);
}

// Función para detener los motores
void MotorStop() {
  // Apagar Motor A
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, LOW);
  digitalWrite(motorAEnable, LOW);

  // Apagar Motor B
  digitalWrite(motorBIn3, LOW);
  digitalWrite(motorBIn4, LOW);
  digitalWrite(motorBEnable, LOW);
}