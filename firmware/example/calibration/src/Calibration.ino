#define SENSOR_PIN 0
#define LED_PIN    13

#define INIT       0
#define NEAR     1
#define FAR       2

int threshold = 0;
int hysteresis = 0;

int lastState = INIT;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  measureBaseline();
}

void loop()
{
  int state = lastState;

  int sensorValue = analogRead(SENSOR_PIN);

  // センサの値に応じて現在の状態を決定
  if(sensorValue > (threshold + hysteresis)) {
    state = NEAR;
  } else if(sensorValue < (threshold - hysteresis)){
    state = FAR;
  }

  // 前回の状態と今回の状態が異なれば関数を呼び出す
  if((lastState!=NEAR) && (state==NEAR)){
    toBeNear();
  } else if((lastState!=FAR) && (state==FAR)){
    toBeFar();
  }

  lastState = state;

  delay(100);
      
}

void measureBaseline() {
  long total = 0;
  int count = 0;

  Serial.println("Calibrating...");

  while(millis() < 5000){
    int sensorValue = analogRead(SENSOR_PIN);
    total += sensorValue;
    count++;
    delay(1);
  }

  Serial.println("Done!");
  Serial.println();

  // 合計と回数から平均を求めてシリアルにプリント
  int average = total / count;
  Serial.print("total = ");
  Serial.println(total);
  Serial.print("count = ");
  Serial.println(count);
  Serial.print("average = ");
  Serial.println(average);

  // 求めた平均から閾値とヒステリシスを決定
  threshold = int((float)average * 0.9);
  if(threshold > 511) {
    hysteresis = (1023 - threshold) / 5;
  } else {
    hysteresis = threshold / 5;
  }

  Serial.print("threshold = ");
  Serial.println(threshold);
  Serial.print("hysteresis = ");
  Serial.println(hysteresis);
}

void toBeNear(){
  digitalWrite(LED_PIN, LOW);
  Serial.println("to be near");
}

void toBeFar(){
  digitalWrite(LED_PIN, HIGH);
  Serial.println("to be far");
}
