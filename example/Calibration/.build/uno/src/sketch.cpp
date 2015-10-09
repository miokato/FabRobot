#include <Arduino.h>

void setup();
void loop();
void measureBaseline();
void onBrightenUp();
void onDarkenUp();
#line 1 "src/sketch.ino"
#define SENSOR_PIN A0
#define LED_PIN 13

#define INIT 0
#define BRIGHT 1
#define DARK 2

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
    state = BRIGHT;
  } else if(sensorValue < (threshold - hysteresis)){
    state = DARK;
  }

  // 前回の状態と今回の状態が異なれば関数を呼び出す
  if((lastState!=BRIGHT) && (state==BRIGHT)){
    onBrightenUp();
  } else if((lastState!=DARK) && (state==DARK)){
    onDarkenUp();
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
    hysteresis = (1023 - threshold) / 10;
  } else {
    hysteresis = threshold / 10;
  }

  Serial.print("threshold = ");
  Serial.println(threshold);
  Serial.print("hysteresis = ");
  Serial.println(hysteresis);
}

void onBrightenUp(){
  digitalWrite(LED_PIN, LOW);
  Serial.println("Brighten up");
}

void onDarkenUp(){
  digitalWrite(LED_PIN, HIGH);
  Serial.println("Darken up");
}
