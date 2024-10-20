#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;
int L = 0;
void setup()
{
  Serial.begin(4800);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  driver.init();

}

void loop()
{
  long m, j, k;

  m = analogRead(A0);
  j = analogRead(A1);
  k = analogRead(A2);

  // primer sensor

  Serial.print("1er sensor: ");
  Serial.println(m);

  Serial.print("2do sensor: ");
  Serial.println(j);

  Serial.print("3er sensor:");
  Serial.println(k);

  char mensaje[32];
  snprintf(mensaje, sizeof(mensaje), "M:%ld,J:%ld,K:%ld,L:%ld", m, j, k, L);

  driver.send((uint8_t *)mensaje, strlen(mensaje));
  driver.waitPacketSent();  
  
  Serial.println(driver.send((uint8_t *)mensaje, strlen(mensaje)));
}
