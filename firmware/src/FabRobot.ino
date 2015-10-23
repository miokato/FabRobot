#include <TimerOne.h>

// 使用するArduinoのピン
#define SENSOR_PIN  A5
#define LED_PIN     13
#define L_MOTOR_1   4
#define L_MOTOR_2   5
#define R_MOTOR_1   6
#define R_MOTOR_2   7

// ロボットの速度 
#define SPEED 50

// ロボットの状態
#define FORWARD 1
#define BACK    2
#define RIGHT   3
#define LEFT    4
#define STOP    5
// ロボットの状態(1~5)を保存するための変数
int state;

// センサ用のフィルタ
#define BUFFER_LENGTH 5
#define THRESHOLD 500
#define DEADZONE  80
int buffer[BUFFER_LENGTH];
int index = 0;

// ロボットのLEDの状態を保存するための変数
boolean led_state = false;

void setup() {
  state = STOP;
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

void ledBlink() {
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
  if(state!=FORWARD) {
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, HIGH);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, HIGH);
  digitalWrite(L_MOTOR_2, LOW);
  Serial.println("forward");
  state = FORWARD;
}

void back() {
  if(state!=BACK) {
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, HIGH);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, HIGH);
  state = BACK;
}

void right() {
  if(state!=RIGHT) {
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, HIGH);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, HIGH);
  state = RIGHT;
}

void left() {
  if(state!=LEFT) {
    stopMotor();
    delay(1);
  }
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, HIGH);
  digitalWrite(L_MOTOR_1, HIGH);
  digitalWrite(L_MOTOR_2, LOW);
  state = LEFT;
}

void stopMotor() {
  digitalWrite(R_MOTOR_1, LOW);
  digitalWrite(R_MOTOR_2, LOW);
  digitalWrite(L_MOTOR_1, LOW);
  digitalWrite(L_MOTOR_2, LOW);
  state = STOP;
}
