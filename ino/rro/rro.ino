const int motorAIn1 = 8;
const int motorAIn2 = 7;
const int motorAEnable = 9;

const int motorBIn3 = 13;
const int motorBIn4 = 12;
const int motorBEnable = 11;

void setup() {
  Serial.begin(9600);
  pinMode(motorAIn1, OUTPUT);
  pinMode(motorAIn2, OUTPUT);
  pinMode(motorAEnable, OUTPUT);
  pinMode(motorBIn3, OUTPUT);
  pinMode(motorBIn4, OUTPUT);
  pinMode(motorBEnable, OUTPUT);
}
 
void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();  // Leer el carácter enviado por el monitor serial
    command = tolower(command);    // Convertir a minúscula para evitar problemas con mayúsculas

    if (command == 'e') {
      MotorHorario();
      Serial.println("Motores girando hacia adelante");
    } 
    else if (command == 'r') {
      MotorAntihorario();
      Serial.println("Motores girando en reversa");
    } 
    else if (command == 's') {
      MotorStop();
      Serial.println("Motores detenidos");
    }
  }
}

// Función para girar los motores hacia adelante (horario)
void MotorHorario() {
  // Invertir la lógica del motor A para corregir la dirección
  digitalWrite(motorAIn1, LOW);  // Cambiar LOW
  digitalWrite(motorAIn2, HIGH); // Cambiar HIGH
  digitalWrite(motorAEnable, HIGH);

  // Motor B adelante
  digitalWrite(motorBIn3, HIGH);
  digitalWrite(motorBIn4, LOW);
  digitalWrite(motorBEnable, HIGH);
}

// Función para girar los motores en reversa (antihorario)
void MotorAntihorario() {
  // Invertir la lógica del motor A para corregir la dirección
  digitalWrite(motorAIn1, HIGH); // Cambiar HIGH
  digitalWrite(motorAIn2, LOW);  // Cambiar LOW
  digitalWrite(motorAEnable, HIGH);

  // Motor B reversa
  digitalWrite(motorBIn3, LOW);
  digitalWrite(motorBIn4, HIGH);
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
