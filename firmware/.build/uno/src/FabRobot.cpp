#include <Arduino.h>
#include <MsTimer2.h>
#include <TimerOne.h>
#include "MeanFilter.h"
void setup();
void led_blink();
void loop();
void forward();
void back();
void right();
void left();
void stopMotor();
#line 1 "src/FabRobot.ino"
//#include <MsTimer2.h>
//#include <TimerOne.h>
//#include "MeanFilter.h"

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

MeanFilter myFilter;

void setup()
{
  int i = myFilter.meanFilter(analogRead(A0));
  state = STOP;
  analogWrite(3, SPEED); // モーターの速度
  // モーター制御用デジタルI/OピンをOUTPUTに設定
  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);
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
  int value = analogRead(SENSOR_PIN);
  Serial.println(value);
  if(value>500){
    back();
    delay(200);
    right();
    delay(300);
  } else {
    forward();
  }
  // シリアル通信受信結果によって処理を切り替える
//  switch(Serial.read()){
//    case 'a': // 前進
//      forward();
//      break;
//    case 's': // 後退
//      back();
//      break;
//    case 'd': // 右回転
//      right();
//      break;
//    case 'f': // 左回転
//      left();
//      break;
//    case 'g': // 停止
//      stopMotor();
//      break;
//  }
}

void forward(){
  if(state!=FORWARD){
    stopMotor();
    delay(100);
  }
  digitalWrite(R_MOTOR_1, HIGH);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, HIGH);
  digitalWrite(L_MOTOR_2, LOW);
  Serial.println("forward");
  state = FORWARD;
}

void back(){
  if(state!=BACK){
    stopMotor();
    delay(100);
  }
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, HIGH);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, HIGH);
  state = BACK;
}

void right(){
  if(state!=RIGHT){
    stopMotor();
    delay(100);
  }
  digitalWrite(R_MOTOR_1, HIGH);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, HIGH);
  state = RIGHT;
}

void left(){
  if(state!=LEFT){
    stopMotor();
    delay(100);
  }
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, HIGH);
  digitalWrite(L_MOTOR_1, HIGH);
  digitalWrite(L_MOTOR_2, LOW);
  state = LEFT;
}

void stopMotor(){
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, LOW);
  state = STOP;
}
