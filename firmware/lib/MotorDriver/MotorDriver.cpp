#include "MotorDriver.h"

MotorDriver::MotorDriver(int pin1, int pin2, int pin3, int pin4) {
  __pin1 = pin1;
  __pin2 = pin2;
  __pin3 = pin3;
  __pin4 = pin4;

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  flag = StopFlag;
}

void MotorDriver::goForward() {
  if(flag != ForwardFlag){
    doStop();
    delay(10);
  }
  digitalWrite(__pin1, HIGH);
  digitalWrite(__pin2, LOW);
  digitalWrite(__pin3, HIGH);
  digitalWrite(__pin4, LOW);
  flag = ForwardFlag;
  Serial.println(flag);
}

void MotorDriver::goBack() {
  if(flag != BackFlag){
    doStop();
    delay(10);
  }
  digitalWrite(__pin1, LOW);
  digitalWrite(__pin2, HIGH);
  digitalWrite(__pin3, LOW);
  digitalWrite(__pin4, HIGH);
  flag = BackFlag;
  Serial.println(flag);
}

void MotorDriver::turnRight() {
  if(flag != RightFlag) {
    doStop();
    delay(10);
  }
  digitalWrite(__pin1, HIGH);
  digitalWrite(__pin2, LOW);
  digitalWrite(__pin3, LOW);
  digitalWrite(__pin4, LOW);
  flag = RightFlag;
  Serial.println(flag);
}

void MotorDriver::turnLeft() {
  if(flag != LeftFlag) {
    doStop();
    delay(10);
  }
  digitalWrite(__pin1, LOW);
  digitalWrite(__pin2, LOW);
  digitalWrite(__pin3, HIGH);
  digitalWrite(__pin4, LOW);
  flag = LeftFlag;
  Serial.println(flag);
}

void MotorDriver::doStop() {
  digitalWrite(__pin1, LOW);
  digitalWrite(__pin2, LOW);
  digitalWrite(__pin3, LOW);
  digitalWrite(__pin4, LOW);
  flag = StopFlag;
  Serial.println("stop");
}


