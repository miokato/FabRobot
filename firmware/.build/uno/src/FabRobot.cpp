#include <Arduino.h>

void setup();
void loop();
int meanFilter(int raw);
void forward();
void back();
void right();
void left();
void stopMotor();
#line 1 "src/FabRobot.ino"
//#define DEBUG
//#define TEST

// define arduino pins
#define SENSOR_PIN             A5 
#define LEFT_MOTOR_GREEN_PIN   4
#define LEFT_MOTOR_WHITE_PIN   5
#define RIGHT_MOTOR_GREEN_PIN  6
#define RIGHT_MOTOR_WHITE_PIN  7

#define SPEED 50

// status
#define FORWARD 1
#define BACK    2
#define RIGHT   3
#define LEFT    4
#define STOP    5

int state;

// using mean filter
#define BUFFER_LENGTH 5
int buffer[BUFFER_LENGTH];
int index = 0;

void setup()
{
  state = STOP;
  // set motor speed
  analogWrite(3, SPEED);
  // set direction of motor pins
  pinMode(LEFT_MOTOR_GREEN_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_WHITE_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_GREEN_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_WHITE_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int smoothedValue = meanFilter(analogRead(SENSOR_PIN));
  //int smoothedValue = analogRead(SENSOR_PIN);

#ifdef TEST
  switch(Serial.read()){
    case 'a':
      forward();
      break;
    case 's':
      back();
      break;
    case 'd':
      right();
      break;
    case 'f':
      left();
      break;
    case 'g':
      stopMotor();
      break;
  }
#else
  if(smoothedValue>500){
    back();
    delay(200);
    right();
    delay(300);
  } else {
    forward();
  }
#endif
}

int meanFilter(int raw) {
  buffer[index] = raw;
  index = (index + 1) % BUFFER_LENGTH;

  long sum = 0;
  for(int i=0; i<BUFFER_LENGTH; i++){
    sum += buffer[i];
  }
  return (int)(sum / BUFFER_LENGTH);
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
#ifdef DEBUG
  Serial.println(digitalRead(RIGHT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(RIGHT_MOTOR_WHITE_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_WHITE_PIN));
  Serial.println("forward");
#endif
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
#ifdef DEBUG
  Serial.println(digitalRead(RIGHT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(RIGHT_MOTOR_WHITE_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_WHITE_PIN));
  Serial.println("back");
#endif
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
#ifdef DEBUG
  Serial.println(digitalRead(RIGHT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(RIGHT_MOTOR_WHITE_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_WHITE_PIN));
  Serial.println("right");
#endif
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
#ifdef DEBUG
  Serial.println(digitalRead(RIGHT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(RIGHT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(RIGHT_MOTOR_WHITE_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_GREEN_PIN));
  Serial.println(digitalRead(LEFT_MOTOR_WHITE_PIN));
  Serial.println("left");
#endif
  state = LEFT;
}

void stopMotor(){
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, LOW);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, LOW);
#ifdef DEBUG
  Serial.println("stop");
#endif
  state = STOP;
}
