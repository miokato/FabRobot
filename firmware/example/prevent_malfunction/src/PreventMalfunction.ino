#define UNKNOWN 0
#define BRIGHT 1
#define DARK 2

#define TIME_TO_WAIT 1000
#define THRESHOLD_H 700
#define THRESHOLD_L 300

#define SENSOR_PIN A0
#define LED_PIN 9

int state = UNKNOWN;
int nextState = UNKNOWN;
unsigned long lastChange = 0;
int lastSensorState = UNKNOWN;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  unsigned long now = millis();
  int brightness = analogRead(SENSOR_PIN);

  int sensorState = lastSensorState;

  // 読み取った値と閾値を比較して、現在のセンサの状態をセット
  if(brightness > THRESHOLD_H){
    sensorState = bright;
  } else if(brightness < THRESHOLD_L){
    sensorState = dark;
  }

  // 前回のセンサの値と今回の値が異なれば
  if(lastSensorState != sensorState) {
    if(sensorState == bright){
      nextState = bright;
      lastChange = now;
    } else if(sensorState == dark){
      nextState = dark;
      lastChange = now;
    }
  }

  lastSensorState = sensorState;
  // 現在の状態と次に移行する状態が異なり、かつセンサの状態が変化してから一定時間が経過していたら
  if(state != nextState && ((now - lastChange) > TIME_TO_WAIT)) {
    if(nextState == bright){
      digitalWrite(LED_PIN, LOW);
    } else if(nextState == dark){
      digitalWrite(LED_PIN, HIGH);
    }
    state = nextState;
  }
  delay(100);
}

}
