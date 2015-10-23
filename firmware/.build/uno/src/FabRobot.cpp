#include <Arduino.h>
#include <TimerOne.h>
void setup();
void ledBlink();
int meanFilter(int raw);
boolean checkDistance(int distance);
void loop();
void forward();
void back();
void right();
void left();
void stopMotor();
#line 1 "src/FabRobot.ino"
//#include <TimerOne.h>

// Arduinoで使用するピン番号の定義
#define SENSOR_PIN  A5
#define LED_PIN     13
#define L_MOTOR_1   4
#define L_MOTOR_2   5
#define R_MOTOR_1   6
#define R_MOTOR_2   7

// ロボットの速度 50~80くらいが適当
#define SPEED 50

// ロボットの状態
#define FORWARD 1
#define BACK    2
#define RIGHT   3
#define LEFT    4
#define STOP    5
// ロボットの状態(1~5)を使用するための定数 state
int robot_state;

// センサ用のフィルタ
#define BUFFER_LENGTH 5
#define THRESHOLD 500
#define DEADZONE  80
int buffer[BUFFER_LENGTH];
int index = 0;


// ロボットのLEDの状態を保存
boolean led_state = false;

void setup()
{
  robot_state = STOP;
  analogWrite(3, SPEED); // モーターの速度
  // モーター制御用デジタルI/OピンをOUTPUTに設定
  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);

  // シリアル通信を開始する
  Serial.begin(9600);

  // タイマー処理でLEDを点滅
  pinMode(13, OUTPUT);
  Timer1.initialize(150000);
  Timer1.attachInterrupt(ledBlink);
}

void ledBlink(){
  led_state = !led_state;
  digitalWrite(13, led_state);
}

int meanFilter(int raw) {
  buffer[index] = raw;
  index = (index + 1) % BUFFER_LENGTH;

  long sum = 0;
  for (int i=0; i<BUFFER_LENGTH; i++) {
    sum += buffer[i];
  }
  return (int)(sum / BUFFER_LENGTH);
}

boolean checkDistance(int distance) {
  boolean is_near;
  if(distance > (THRESHOLD + DEADZONE)) {
    is_near = true;
  } else if (distance < (THRESHOLD - DEADZONE)) {
    is_near = false;
  } else {
  }
  return is_near;
}

void loop() {
  int raw = analogRead(SENSOR_PIN);
  int smoothed = meanFilter(raw);
  boolean is_near = checkDistance(smoothed);
  Serial.println(smoothed);

  if(is_near) {
    back();
    delay(200);
    right();
    delay(300);
  } else {
    forward();
  }
}

void forward() {
  if(robot_state!=FORWARD){
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, HIGH);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, HIGH);
  digitalWrite(L_MOTOR_2, LOW);
  Serial.println("forward");
  robot_state = FORWARD;
}

void back(){
  if(robot_state!=BACK){
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, HIGH);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, HIGH);
  robot_state = BACK;
}

void right() {
  if(robot_state!=RIGHT){
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, HIGH);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, HIGH);
  robot_state = RIGHT;
}

void left() {
  if(robot_state!=LEFT){
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, HIGH);
  digitalWrite(L_MOTOR_1, HIGH);
  digitalWrite(L_MOTOR_2, LOW);
  robot_state = LEFT;
}

void stopMotor() {
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, LOW);
  robot_state = STOP;
}
