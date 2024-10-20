#include <ArduinoHttpClient.h>
//#include <WiFi.h>
#include <ArduinoJson.h>  // Librería para manejar JSON
#include <RH_ASK.h>
#include <SPI.h>  // No se usa pero se necesita para compilar

/////// WiFi Settings ///////
char ssid[] = "Robotica";
char pass[] = "Colombia2024#";

char serverAddress[] = "192.168.2.108";  // Dirección del servidor
int port = 3000;

//WiFiClient wifi;
//HttpClient client = HttpClient(wifi, serverAddress, port);
//int status = WL_IDLE_STATUS;

RH_ASK driver;

// Declaración de datos iniciales
String reading[3] = { "0", "0", "0" };
String commands[3] = { "Apagar primero", "Apagar segundo", "Apagar tercero" };

int pinPrimerLED = 2;
int pinSegundoLED = 3;
int pinTercerLED = 4;
int pinZumbador = 5;
int cont = 0;
void setup() {

  pinMode(pinPrimerLED, OUTPUT);
  pinMode(pinSegundoLED, OUTPUT);
  pinMode(pinTercerLED, OUTPUT);
  pinMode(pinZumbador, OUTPUT);  // Pin del zumbador
  Serial.begin(9600);
  driver.init();
  Serial.print("Driver init: ");
  Serial.println(driver.init());

  // Conexión WiFi
  //while (status != WL_CONNECTED) {
  //  Serial.print("Conectando a la red: ");
  //  Serial.println(ssid);
  //  status = WiFi.begin(ssid, pass);
  //  delay(1000);
  //}

  //Serial.println("Conexión WiFi exitosa!");
  //Serial.print("IP Address: ");
  //Serial.println(WiFi.localIP());
}

void tonoVariable(int frecuencia) {
  tone(pinZumbador, frecuencia);  // Envia una señal con la frecuencia deseada
}

void loop() {
  uint8_t mensaje[32];  // Buffer para recibir el mensaje
  uint8_t mensajeLen = sizeof(mensaje);

  if (driver.recv(mensaje, &mensajeLen)) {
    String mensaje1 = (char *)mensaje;
    // Extraer los valores del mensaje recibido
    int mIndex = mensaje1.indexOf('M');
    int jIndex = mensaje1.indexOf('J');
    int kIndex = mensaje1.indexOf('K');
    int lIndex = mensaje1.indexOf('L');

    int m = mensaje1.substring(mIndex + 2, jIndex - 1).toInt();
    int j = mensaje1.substring(jIndex + 2, kIndex - 1).toInt();
    int k = mensaje1.substring(kIndex + 2, lIndex - 1).toInt();

    Serial.print("1er sensor: ");
    Serial.println(m);
    Serial.print("2do sensor: ");
    Serial.println(j);
    Serial.print("3er sensor: ");
    Serial.println(k);

    // Condiciones para encender o apagar LEDs
    // Primer sensor
    if (m >= 20 && m <= 2000) {
      Serial.println("Encender primer LED");
      digitalWrite(pinPrimerLED, HIGH);
      commands[0] = "Encender primero";
    } else {
      Serial.println("Apagar primer LED");
      digitalWrite(pinPrimerLED, LOW);
      commands[0] = "Apagar primero";
    }

    // Segundo sensor
    if (j >= 20 && j <= 2000) {
      Serial.println("Encender segundo LED");
      digitalWrite(pinSegundoLED, HIGH);
      commands[1] = "Encender segundo";

    } else {
      Serial.println("Apagar segundo LED");
      digitalWrite(pinSegundoLED, LOW);
      commands[1] = "Apagar segundo";
    }

    // Tercer sensor
    if (k >= 20 && k <= 2000) {
      Serial.println("Encender tercer LED y activar zumbador");
      digitalWrite(pinTercerLED, HIGH);
      digitalWrite(pinZumbador, HIGH);
      //tonoVariable(1000);
      //delay(2000);
      //noTone(pinZumbador);
      commands[2] = "Encender tercero";

    } else {
      Serial.println("Apagar tercer LED y zumbador");
      digitalWrite(pinZumbador, LOW);
      digitalWrite(pinTercerLED, LOW);
      //noTone(pinZumbador);
      commands[2] = "Apagar tercero";
    }

    //// Crear el objeto JSON para enviar al servidor
    //StaticJsonDocument<200> jsonDoc;
    //// Crear una lista (array) para los valores de los sensores
    //JsonArray sensorValuesArray = jsonDoc.createNestedArray("sensor_values");
    //sensorValuesArray.add(m);
    //sensorValuesArray.add(j);
    //sensorValuesArray.add(k);
    //
    //// Crear una lista (array) para los comandos
    //JsonArray commandArray = jsonDoc.createNestedArray("commands");
    //for (int i = 0; i < 3; i++) {
    //  commandArray.add(commands[i]);  // Agregar cada comando al array
  }
  //
  //// Convertir el objeto JSON a un string
  //String jsonData;
  //serializeJson(jsonDoc, jsonData);
  ////
  //Serial.println("Haciendo solicitud POST con JSON...");
  //client.beginRequest();
  //client.post("/recibir_datos");
  ////
  ////// Especificar tipo de contenido JSON
  //client.sendHeader("Content-Type", "application/json");
  //client.sendHeader("Content-Length", jsonData.length());
  //client.beginBody();
  //client.print(jsonData);  // Enviar los datos JSON
  //client.endRequest();
  ////
  ////// Leer el código de estado y la respuesta del servidor
  //int statusCode = client.responseStatusCode();
  //String response = client.responseBody();
  //
  //Serial.print("Status code: ");
  //Serial.println(statusCode);
  //Serial.print("Response: ");
  //Serial.println(response);
}
