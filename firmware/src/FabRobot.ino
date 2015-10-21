// Arduinoで使用するピン番号の定義
#define LEFT_MOTOR_GREEN_PIN   4
#define LEFT_MOTOR_WHITE_PIN   5
#define RIGHT_MOTOR_GREEN_PIN  6
#define RIGHT_MOTOR_WHITE_PIN  7
#define SPEED 90

#define FORWARD 1
#define BACK    2
#define RIGHT   3
#define LEFT    4
#define STOP    5
// ロボットの状態(1~5)を使用するための定数 state
int state;

void setup()
{
  state = STOP;
  analogWrite(3, SPEED); // モーターの速度
  // モーター制御用デジタルI/OピンをOUTPUTに設定
  pinMode(LEFT_MOTOR_GREEN_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_WHITE_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_GREEN_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_WHITE_PIN, OUTPUT);
  // シリアル通信を開始する
  Serial.begin(9600);
}

void loop()
{
  // シリアル通信受信結果によって処理を切り替える
  switch(Serial.read()){
    case 'a': // 前進
      forward();
      break;
    case 's': // 後退
      back();
      break;
    case 'd': // 右回転
      right();
      break;
    case 'f': // 左回転
      left();
      break;
    case 'g': // 停止
      stopMotor();
      break;
  }
}

void forward(){
  if(state!=FORWARD){
    stopMotor();
    delay(100);
  }
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, LOW);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, LOW);
  Serial.println("forward");
  state = FORWARD;
}

void back(){
  if(state!=BACK){
    stopMotor();
    delay(100);
  }
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, HIGH);
  state = BACK;
}

void right(){
  if(state!=RIGHT){
    stopMotor();
    delay(100);
  }
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, LOW);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, HIGH);
  state = RIGHT;
}

void left(){
  if(state!=LEFT){
    stopMotor();
    delay(100);
  }
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, LOW);
  state = LEFT;
}

void stopMotor(){
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, LOW);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, LOW);
  state = STOP;
}
