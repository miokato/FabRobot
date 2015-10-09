#include <Arduino.h>

void setup();
void loop();
int smoothByMeanFilter();
void forward();
void right();
#line 1 "src/sketch.ino"
#define BUFFER_LENGTH 5
#define SENSORPIN 5
// ref
#define REF 3
#define SPEED 40
// motors
#define RM1 4
#define RM2 5
#define LM1 6
#define LM2 7


int buffer[BUFFER_LENGTH];
int index = 0;

void setup(){
    Serial.begin(9600);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    analogWrite(REF, SPEED);
}


void loop(){
    int raw = analogRead(SENSORPIN);
    buffer[index] = raw;

    index = (index + 1) % BUFFER_LENGTH;

    int smoothed = smoothByMeanFilter();

    if(smoothed > 300){
        right();
    } else {
        forward();
    }

    // prints
    Serial.print(raw);
    Serial.print("\t");
    Serial.print(smoothed);
    Serial.print("\t");
    Serial.println();

    delay(100);

}

int smoothByMeanFilter(){
    long sum = 0;

    for(int i=0; i<BUFFER_LENGTH; i++){
        sum += buffer[i];
    }

    return (int)(sum / BUFFER_LENGTH);
}

void forward(){
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    Serial.println("forward");
}
void right(){
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    Serial.println("right");
}

