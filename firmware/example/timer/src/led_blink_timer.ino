#include <MsTimer2.h>
#define LED_PIN 13
#define SENSOR_PIN 0

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  MsTimer2::set(100, ReadSensor);
  MsTimer2::start();
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

void ReadSensor() {
  int raw = analogRead(SENSOR_PIN);
  Serial.println(raw);
}

