const int PinIN1 = 7;
const int PinIN2 = 6;

const int PinIN3 = 9;
const int PinIN4 = 10;

void setup() {
  Serial.begin(9600);
  pinMode(PinIN1, OUTPUT);
  pinMode(PinIN2, OUTPUT);
  pinMode(PinIN3, OUTPUT);
  pinMode(PinIN4, OUTPUT);
}
 

void loop() {

  MotorHorario();
  Serial.println("Giro del Motor en sentido horario");
  delay(5000);

  MotorAntihorario();
  Serial.println("Giro del Motor en sentido antihorario");
  delay(5000);

  MotorStop();
  Serial.println("Motor Detenido");
  delay(3000);

}
//función para girar el motor en sentido horario
void MotorHorario()
{
  digitalWrite (PinIN1, HIGH);
  digitalWrite (PinIN2, LOW);

  digitalWrite(PinIN3, HIGH);
  digitalWrite(PinIN4, LOW);
}
//función para girar el motor en sentido antihorario
void MotorAntihorario()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, HIGH);
}

//función para apagar el motor
void MotorStop()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, LOW);
}