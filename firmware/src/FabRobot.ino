#include <MsTimer2.h>
#include <TimerOne.h>
#include "MotorDriver.h"

// Arduinoで使用するピン番号の定義
#define SENSOR_PIN  A5
#define L_MOTOR_1   4
#define L_MOTOR_2   5
#define R_MOTOR_1  6
#define R_MOTOR_2  7
#define SPEED 50

#define FORWARD 1
#define BACK    2
#define RIGHT   3
#define LEFT    4
#define STOP    5
// ロボットの状態(1~5)を使用するための定数 state
int state;
boolean led_state = false;

MotorDriver md(R_MOTOR_1, R_MOTOR_2, L_MOTOR_1, L_MOTOR_2);

void setup()
{
  state = STOP;
  analogWrite(3, SPEED); // モーターの速度
  // シリアル通信を開始する
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Timer1.initialize(150000);
  Timer1.attachInterrupt(led_blink);
}

void led_blink(){
  led_state = !led_state;
  digitalWrite(13, led_state);
}

void loop()
{
  //int value = analogRead(SENSOR_PIN);
  //Serial.println(value);
  //if(value>500){
  //  md.goBack();
  //  delay(200);
  //  md.turnLeft();
  //  delay(300);
  //} else {
  //  md.goForward();
  //}
  // シリアル通信受信結果によって処理を切り替える
  switch(Serial.read()){
    case 'a': // 前進
      md.goForward();
      break;
    case 's': // 後退
      md.goBack();
      break;
    case 'd': // 右回転
      md.turnRight();
      break;
    case 'f': // 左回転
      md.turnLeft();
      break;
    case 'g': // 停止
      md.doStop();
      break;
  }
}

