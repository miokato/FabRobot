#include <Arduino.h>

void multiply(int a);
#line 1 "src/test.ino"
void multiply(int a){
  int result = a*a;
  Serial.println(result);
}
