#include <Arduino.h>

void setup();
void loop();
int meanFilter(int raw);
void forward();
void back();
void right();
void left();
void stopMotor();
#line 1 "src/sketch.ino"
// define arduino pins
#define SENSOR_PIN           A5 
#define LEFT_MOTOR_GREEN_PIN 4
#define LEFT_MOTOR_WHITE_PIN 5
#define RIGHT_MOTOR_GREEN_PIN  6
#define RIGHT_MOTOR_WHITE_PIN  7
int motorPins[4] = {LEFT_MOTOR_GREEN_PIN, LEFT_MOTOR_WHITE_PIN, RIGHT_MOTOR_GREEN_PIN, RIGHT_MOTOR_WHITE_PIN};
#define SPEED 60

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
  for(int i=0; motorPins[i]!='\0'; i++){
    pinMode(motorPins[i], OUTPUT);
  }
  Serial.begin(9600);
  // set motor input pins to output
}

void loop()
{

  int smoothedValue = meanFilter(analogRead(A0));
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
  Serial.println("back");
  state = BACK;
}

void right(){
  if(state!=RIGHT){
    stopMotor();
    delay(100);
  }
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, LOW);
  Serial.println("right");
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
  Serial.println("left");
  state = LEFT;
}

void stopMotor(){
  digitalWrite(RIGHT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_WHITE_PIN, LOW);
  digitalWrite(LEFT_MOTOR_GREEN_PIN, LOW);
  digitalWrite(LEFT_MOTOR_WHITE_PIN, LOW);
  Serial.println("stop");
  state = STOP;
}
