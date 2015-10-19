#include <Arduino.h>
#include <MsTimer2.h>
#include <servo.h>
void setMode();
void setup();
void loop();
void state_run();
void state_walk();
void state_stop();
#line 1 "src/Timer.ino"
// day3
// typedef, enumの利用法
// timerの利用法
// timerを使ってセンサからの値を取得して、その値によりモードを切り替える。

//#include <MsTimer2.h>
//#include <servo.h>
// typedefは既存の型名に新しい型名を与える
// [用法] typedef somename SN;

Servo servo1;
Servo servo2;
Servo servo3;


static int value;

typedef enum{
  STOP,
  WALK,
  RUN
} MODE;

MODE mode;

void setMode(){

  value = analogRead(A0);
  if(value>700){
    mode = RUN;
  } else if(value>400 && value<=700){
    mode = WALK;
  } else {
    mode = STOP;
  }

}


void setup()
{
  // servo
  servo1.attach(3);
  servo2.attach(6);
  servo3.attach(9);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  MsTimer2::set(1000, setMode);
  MsTimer2::start();

  mode = STOP;
}

void loop()
{
  switch (mode){
    case WALK:
      state_walk();
      Serial.println("walk");
      break;
    case RUN:
      state_run();
      Serial.println("run");
      break;
    case STOP:
      state_stop();
      Serial.println("stop");
      break;
    default:
      break;
  }
}

void state_run(){
  servo1.write(10);
  servo2.write(10);
  servo3.write(10);
  delay(500);
  servo1.write(50);
  servo2.write(50);
  servo3.write(50);
  delay(500);
  //Serial.println("run");
}

void state_walk(){
  servo1.write(50);
  servo2.write(50);
  servo3.write(50);
  delay(500);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  delay(500);
  //Serial.println("walk");
}

void state_stop(){
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  delay(500);
  servo1.write(160);
  servo2.write(160);
  servo3.write(160);
  delay(500);
}

