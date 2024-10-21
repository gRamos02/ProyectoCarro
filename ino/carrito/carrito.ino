#include <SoftwareSerial.h>

// Pines para el módulo Bluetooth
int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); // RX en pin 2, TX en pin 3

// Pines para los motores
int motor1A = 9;
int motor1B = 8;
const int motor1Enable = 10;
int motor2A = 13;
int motor2B = 12;
const int motor2Enable = 11;

int potenciaIzq = 0;
int potenciaDer = 0;
String values = "";

void setup() {
  Serial.begin(9600);      // Comunicación con el monitor serie
  bluetooth.begin(9600);   // Comunicación serie con el módulo Bluetooth

  // Configuración de los pines de los motores como salidas
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor1Enable, OUTPUT);
  pinMode(motor2Enable, OUTPUT);
}

void loop() {
  // Lee datos del módulo Bluetooth si están disponibles
  while (bluetooth.available()) {
    char receivedChar = bluetooth.read();
    
    // Verifica si es un final de línea para procesar los datos
    if (receivedChar == '\n') {
      // Procesa la cadena para extraer los valores
      int result = sscanf(values.c_str(), "%d %d", &potenciaDer, &potenciaIzq);
      
      
      // Verifica que se hayan leído dos enteros correctamente
      if (result == 2) {
        Serial.print("IZQUIERDA: ");
        Serial.println(potenciaIzq);
        Serial.print("DERECHA: ");
        Serial.println(potenciaDer);
        // Control de motores
        // if(abs(potenciaIzq) > 30){
          controlarMotor(motor1A, motor1B, motor1Enable, potenciaIzq);
        // }else{
          // controlarMotor(motor1A, motor1B, motor1Enable, 0);
        // }
        // if(abs(potenciaDer) > 30){
          controlarMotor(motor2B, motor2A, motor2Enable, potenciaDer);
        // }else{
          // controlarMotor(motor2B, motor2A, motor2Enable, 0);
        // }
      }

      // Limpia la cadena para la siguiente lectura
      values = "";
    } else {
      // Agrega el carácter recibido a la cadena
      values += receivedChar;
    }
  }
}

// Función para controlar un motor según la potencia y regular la velocidad con el pin de habilitación
void controlarMotor(int pinA, int pinB, int enablePin, int potencia) {
  int velocidad = abs(potencia);  // La velocidad es el valor absoluto de la potencia

  if (potencia > 0) {
    // Mueve el motor hacia adelante
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    analogWrite(enablePin, velocidad);  // Controla la velocidad
  } else if (potencia < 0) {
    // Mueve el motor hacia atrás
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    analogWrite(enablePin, velocidad);  // Controla la velocidad
  } else {
    // Detiene el motor
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    analogWrite(enablePin, 0);  // No pasa corriente al motor
  }
}
