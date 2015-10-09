#define THRESHOLD 511
#define HYSTERESYS 102

#define SENSOR_PIN A0
#define LED_PIN 9

boolean wasBright = true;

void setup(){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop(){

  boolean isBright = wasBright;

  int brightness = analogRead(SENSOR_PIN);

  if(brightness > (THRESHOLD + HYSTERESYS)){
    isBright = true;
  } else if(brightness < (THRESHOLD - HYSTERESYS)){
    isBright = false;
  } else {
  }

  if(!wasBright && isBright){
    onBrightenUp();
  } else if(wasBright && !isBright){
    onDarkenUp();
  }

  wasBright = isBright;

  delay(10);
}

void onBrightenUp(){
  digitalWrite(LED_PIN, LOW);
}

void onDarkenUp(){
  digitalWrite(LED_PIN, HIGH);
}

  


