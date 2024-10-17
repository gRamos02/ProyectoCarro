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

String command = "";

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
  while (Bluetooth.available()) {
    char incomingChar = Bluetooth.read();
    // Serial.println(incomingChar);
    if (incomingChar == '\n') {
      Serial.println(command);
      processCommand(command);
      command = "";  // Clear command buffer for the next command
    } else {
      command += incomingChar;  // Add character to the command
    }
  }
}

void processCommand(String command) {
    command.trim();  // Eliminar espacios en blanco
    Serial.println(command);

    if (command.startsWith("i:")) {  // Comando para motor izquierdo (motor B)
      int speed = command.substring(2).toInt();  // Obtener valor de velocidad
      setMotorA(speed);
      Serial.println("Motor A adelante con velocidad: " + String(speed));
    } 
    else if (command.startsWith("d:")) {  // Comando para motor derecho (motor A)
      int speed = command.substring(2).toInt();  // Obtener valor de velocidad
      setMotorB(speed);
      Serial.println("Motor B adelante con velocidad: " + String(speed));
    } 
    else if (command == "rl") {  // Reversa motor izquierdo (motor B)
      reverseMotorA();
      Serial.println("Motor B en reversa");
    } 
    else if (command == "rd") {  // Reversa motor derecho (motor A)
      reverseMotorB();
      Serial.println("Motor A en reversa");
    } 
    else if (command == "stopA") {  // Detener motor A
      stopMotorA();
      Serial.println("Motor A detenido");
    }
    else if (command == "stopB") {  // Detener motor B
      stopMotorB();
      Serial.println("Motor B detenido");
    }
}

// Función para ajustar el motor A con la velocidad indicada
void setMotorA(int speed) {
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, HIGH);
  analogWrite(motorAEnable, speed);  // Controla la velocidad con PWM
}

// Función para ajustar el motor B con la velocidad indicada
void setMotorB(int speed) {
  digitalWrite(motorBIn3, HIGH);
  digitalWrite(motorBIn4, LOW);
  analogWrite(motorBEnable, speed);  // Controla la velocidad con PWM
}

// Función para reversa del motor A
void reverseMotorA() {
  digitalWrite(motorAIn1, HIGH);
  digitalWrite(motorAIn2, LOW);
  analogWrite(motorAEnable, 255);  // Velocidad fija al máximo
}

// Función para reversa del motor B
void reverseMotorB() {
  digitalWrite(motorBIn3, LOW);
  digitalWrite(motorBIn4, HIGH);
  analogWrite(motorBEnable, 255);  // Velocidad fija al máximo
}

// Función para detener el motor A
void stopMotorA() {
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, LOW);
  analogWrite(motorAEnable, 0);  // Apaga el motor
}

// Función para detener el motor B
void stopMotorB() {
  digitalWrite(motorBIn3, LOW);
  digitalWrite(motorBIn4, LOW);
  analogWrite(motorBEnable, 0);  // Apaga el motor
}
