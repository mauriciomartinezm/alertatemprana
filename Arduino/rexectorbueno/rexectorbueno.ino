  #include <RH_ASK.h>
  #include <SPI.h> // Not actually used but needed to compile

  RH_ASK driver;
  int m, j, k;
  void setup()
  {
    pinMode(13, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(7, OUTPUT); // pin de zumbador
    Serial.begin(9600);
    driver.init();
  }
  void tonoVariable(int frecuencia) {
    tone(7, frecuencia);  // Envia una señal con la frecuencia deseada
  }

  void loop()
  {
    uint8_t msg[32];  // Buffer para recibir el mensaje
    uint8_t msgLen = sizeof(msg);
    if (driver.recv(msg, &msgLen))
    {
      String mensaje = (char *)msg;
      //Serial.print("Mensaje recibido: ");
      //Serial.println(mensaje);

      // Extraer los valores del mensaje recibido
      int mIndex = mensaje.indexOf('M');
      int jIndex = mensaje.indexOf('J');
      int kIndex = mensaje.indexOf('K');
      int lIndex = mensaje.indexOf('L');

      m = mensaje.substring(mIndex + 2, jIndex - 1).toInt();
      j = mensaje.substring(jIndex + 2, kIndex - 1).toInt();
      k = mensaje.substring(kIndex + 2, lIndex - 1).toInt();

      Serial.print("1er sensor: ");
      Serial.println(m);
      Serial.print("2do sensor: ");
      Serial.println(j);
      Serial.print("3er sensor: ");
      Serial.println(k);

      // Condiciones para encender o apagar LEDs
      // Primer sensor
      if (m >= 50 && m <= 1000)
      {
        Serial.println("Encender primer LED");
        digitalWrite(13, HIGH);
      }
      else
      {
        Serial.println("Apagar primer LED");
        digitalWrite(13, LOW);
      }

      // Segundo sensor
      if (j >= 50 && j <= 1000)
      {
        Serial.println("Encender segundo LED");
        digitalWrite(8, HIGH);
      }
      else
      {
        Serial.println("Apagar segundo LED");
        digitalWrite(8, LOW);
      }

      // Tercer sensor
      if (k >= 100 && k <= 2000)
      {
        Serial.println("Encender tercer LED y activar zumbador");
        digitalWrite(9, HIGH);
        tonoVariable(1000);
        delay(2000);
        noTone(7); 
      }
      else
      {
        Serial.println("Apagar tercer LED y zumbador");
        digitalWrite(9, LOW);
        noTone(7);
      }
    }
  }
