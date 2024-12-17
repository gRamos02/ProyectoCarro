#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#include "DHT.h"
#include <L298N.h>

#define DHTPIN 7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

// Pines para los motores
L298N motorA(5,4,3);
L298N motorB(10,8,9);

//Ethernet setup y DB
const byte mac[] PROGMEM  = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

const IPAddress ip(192, 168, 1, 2) PROGMEM ;     // IP estática del Arduino
const IPAddress subnet(255, 255, 255, 0) PROGMEM ; // Máscara de subred
const IPAddress gateway(192, 168, 1, 1) PROGMEM ; // Puerta de enlace

const IPAddress server(192, 168, 1, 10) PROGMEM ; // Dirección IP del servidor MySQL en la nube
const EthernetServer webServer(80) PROGMEM ;

const char usuario[] = "jerry";
const char pass[] = "sp";
const char db_name[]  = "sp_carrito";

//char INSERT_SQL[] = "INSERT INTO temperaturas(temperatura, lugar) VALUES(43.1, '19M')";
char INSERT_SQL[100];
unsigned long lastInsertTime = 0; // Para medir el tiempo desde la última inserción
const unsigned long interval = 10000; // Intervalo de 2 minutos en milisegundos

EthernetClient cliente;
MySQL_Connection conn((Client *)&cliente);


void setup() {
  Serial.begin(9600);      // Comunicación con el monitor serie
  // Configuración de los pines de los motores como salidas

  // controlarMotor(motor2A, motor2B, motor2Enable, 200);
  dht.begin();

  //Iniciar ethernet con ip dinamica
  //if (Ethernet.begin(mac) == 0) {
    //Serial.println("Fallo al obtener una IP mediante DHCP");
    //while (true);
  //}
  // Configuración de Ethernet con IP estática
  Ethernet.begin(mac, ip, gateway, subnet);
  webServer.begin();
  Serial.print(F("IP estática configurada: "));
  Serial.println(Ethernet.localIP());
  
   // Conexión a la base de datos
  Serial.println(F("Conectando..."));
  if (conn.connect(server, 3306, usuario, pass)) {
    delay(1000);
    Serial.println(F("Conexión exitosa."));

    // Selecciona la base de datos
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    char use_db[50];
    sprintf(use_db, "USE %s", db_name);
    cur_mem->execute(use_db);
    delete cur_mem;
  } else {
    Serial.println(F("Connection failed."));
  }

  // Detener todos los motores al inicio
  stopMotors();
  //totalStop();
}

void loop() {
  EthernetClient cliente = webServer.available();
  float t = dht.readTemperature();
  String displayTemp = isnan(t) ? "24.0" : String(t, 2);
  
  if (cliente) {
    Serial.println(F("Nuevo Cliente"));
    boolean espacioenblanco = true;
    String cadena = "";
    
    while (cliente.connected()) {
      if (cliente.available()) { 
        char c = cliente.read();
        Serial.write(c);
        cadena.concat(c);
        
        int posicion = cadena.indexOf("accion=");
        if (posicion != -1) {
          String comando = cadena.substring(posicion + 7);
          //Serial.println(comando);
          // Control de motores basado en comando
          if (comando.startsWith("FORWARD")) {
            moveForward();
          } else if (comando.startsWith("BACKWARD")) {
            moveBackwards();
          } else if (comando.startsWith("LEFT")) {
            moveLeft();
          } else if (comando.startsWith("RIGHT")) {
            moveRight();
          } else if (comando.startsWith("STOP")) {
            stopMotors();
          }
        }
        
        if (c == '\n' && espacioenblanco) {
          cliente.println(F("HTTP/1.1 200 OK"));
          cliente.println(F("Content-Type: text/html"));
          cliente.println();
          cliente.println(F("<html>"));
          cliente.println(F("<head>"));
          cliente.println(F("<style>"));
          cliente.println(F("body {"));
          cliente.println(F("   font-family: Arial, sans-serif;"));
          cliente.println(F("   text-align: center;"));
          cliente.println(F("   background-color: #f4f4f4;"));
          cliente.println(F("   margin: 0;"));
          cliente.println(F("   padding: 0;"));
          cliente.println(F("}"));
          cliente.println(F(".temp {"));
          cliente.println(F("   background-color: #ffddcc;"));
          cliente.println(F("   padding: 10px;"));
          cliente.println(F("   font-size: 20px;"));
          cliente.println(F("   border-radius: 8px;"));
          cliente.println(F("   display: inline-block;"));
          cliente.println(F("   margin-bottom: 20px;"));
          cliente.println(F("}"));
          cliente.println(F(".button {"));
          cliente.println(F("   border-radius: 5px;"));
          cliente.println(F("   font-size: 18px;"));
          cliente.println(F("}"));
          cliente.println(F("</style>"));
          cliente.println(F("</head>"));
          cliente.println(F("<body>"));
          cliente.println(F("<br>"));
          cliente.println(F("<br>"));
          //cliente.println("<div class='temp'>Temperatura Actual: " + displayTemp + " C</div>");
          cliente.println(F("<div style='text-align:center;'>"));
          cliente.println(F("<button class='button' onClick=location.href='./?accion=FORWARD' style='margin:auto;background-color: #A7BEB5;color: snow;padding: 10px;border: 1px solid #3F594A;width:90px;'>Avanzar</button>"));
          cliente.println(F("</div>"));
          cliente.println(F("<span><br></span>"));
          cliente.println(F("<div style='text-align:center;'>"));
          cliente.println(F("<button class='button' onClick=location.href='./?accion=LEFT' style='margin:auto;background-color: #A7BEB5;color: snow;padding: 10px;border: 1px solid #3F594A;width:90px;'>Izquierda</button>"));
          cliente.println(F("<button class='button' onClick=location.href='./?accion=STOP' style='margin:auto;background-color: #C4501B;color: snow;padding: 10px;border: 1px solid #3F594A;width:90px;'>Alto</button>"));
          cliente.println(F("<button class='button' onClick=location.href='./?accion=RIGHT' style='margin:auto;background-color: #A7BEB5;color: snow;padding: 10px;border: 1px solid #3F594A;width:90px;'>Derecha</button>"));
          cliente.println(F("</div>"));
          cliente.println(F("<span><br></span>"));
          cliente.println(F("<div style='text-align:center;'>"));
          cliente.println(F("<button class='button' onClick=location.href='./?accion=BACKWARD' style='margin:auto;background-color: #A7BEB5;color: snow;padding: 10px;border: 1px solid #3F594A;width:90px;'>Abajo</button>"));
          cliente.println(F("</div>"));
          cliente.println(F("</body>"));
          cliente.println(F("</html>"));
          
          break;
        }
        
        if (c == '\n') {
          espacioenblanco = true;
        } else if (c != '\r') {
          espacioenblanco = false;
        }
      }
    }
    
    delay(1);
    cliente.stop();
  }


  dbInsert();
  
}


void moveForward(){
  motorA.forward();
  motorB.forward();
  // controlarMotorA(255);
  // controlarMotorB(255);
}

void moveBackwards(){
  motorA.backward();
  motorB.backward();
  // controlarMotorA(-255);
  // controlarMotorB(-255);
}

void moveLeft(){
  motorA.stop();
  motorB.forward();
  // controlarMotorA(0);
  // controlarMotorB(255);
}

void moveRight(){
  motorA.forward();
  motorB.stop();
  // controlarMotorA(255);
  // controlarMotorB(0);
}

void stopMotors(){
  motorA.stop();
  motorB.stop();
  // controlarMotorA(0);
  // controlarMotorB(0);
}

void dbInsert(){
  // Insertar en la base de datos cada 2 minutos
  unsigned long currentMillis = millis();
  if (currentMillis - lastInsertTime >= interval) {
      Serial.println("Intervalo alcanzado. Intentando insertar datos.");
      lastInsertTime = currentMillis;
      
      // Verificar si la conexión está activa
      if (!conn.connected()) {  
          Serial.println("Reconectando...");
          if (conn.connect(server, 3306, usuario, pass)) {
              Serial.println("Reconectado exitosamente.");
              MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
              char use_db[50];
              sprintf(use_db, "USE %s", db_name);
              cur_mem->execute(use_db);
              delete cur_mem;
          } else {
              Serial.println("Error al reconectar.");
              return;  // Sale de loop si la reconexión falla
          }
      }
  
      // Verificar si la lectura de temperatura es válida
      float t = dht.readTemperature();
      if (isnan(t)) {
          Serial.println("Error al leer la temperatura! No se insertarán datos.");
          return; // Salir si hay un error en la lectura
      }
      //float h = dht.readHumidity();
      //if (isnan(h)) {
      //    Serial.println("Error al leer la humedad! No se insertarán datos.");
      //    return; // Salir si hay un error en la lectura
      //}
  
      // Convertir el valor de temperatura a una cadena
      char tempStr[10]; // Suficientemente grande para el valor formateado
      //char humStr[10];
      dtostrf(t, 4, 2, tempStr); // Convierte el float t a string con 2 decimales
      //dtostrf(h, 4, 2, humStr); // Convierte el float t a string con 2 decimales
  
      // Construcción de la consulta SQL
      Serial.println(F("Insertando Datos"));
      sprintf(INSERT_SQL, "INSERT INTO temperaturas(temperatura, humedad) VALUES(%s, '%s')", tempStr, "13.30");
      Serial.print(F("Consulta SQL: "));
      Serial.println(INSERT_SQL); // Imprimir consulta para verificar formato
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(INSERT_SQL);  // Inserta los datos
      delete cur_mem;
  }
}
//tempeartura
String getLastTemperature() {
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  char query[100];
  sprintf(query, "SELECT temperatura FROM temperaturas ORDER BY fecha_hora DESC LIMIT 1");
  
  // Execute query
  cur_mem->execute(query);
  
  // Fetch result
  column_names *cols = cur_mem->get_columns();
  row_values *row = cur_mem->get_next_row();
  
  String lastTemp = "N/A";
  if (row) {
    lastTemp = row->values[0];
  }
  
  delete cur_mem;
  return lastTemp;
}