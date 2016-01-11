#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <arduino.h>

class MotorDriver {

  public:
    // set pin1, pin2 to Right Motor
    // set pin3, pin4 to Left Motor
    MotorDriver(int pin1, int pin2, int pin3, int pin4);
    void goForward();
    void goBack();
    void turnLeft();
    void turnRight();
    void doStop();

  private:
    int __pin1;
    int __pin2;
    int __pin3;
    int __pin4;

    enum Flag {
      ForwardFlag = 1,
      BackFlag = 2,
      RightFlag = 3,
      LeftFlag = 4,
      StopFlag = 5
    } flag;
    
    



};


#endif
