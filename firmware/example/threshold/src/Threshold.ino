#define THRESHOLD  500
#define HYSTERESYS 130

#define SENSOR_PIN 0
#define LED_PIN    9

boolean wasNear = true;

void setup(){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}

void loop(){

  boolean isNear = wasNear;

  int brightness = analogRead(SENSOR_PIN);

  if(brightness > (THRESHOLD + HYSTERESYS)) {
    isNear = true;
  } else if(brightness < (THRESHOLD - HYSTERESYS)) {
    isNear = false;
  } else {
  }

  if(!wasNear && isNear) {
    toBeNear();
  } else if(wasNear && !isNear) {
    toBeFar();
  }

  wasNear = isNear;

  delay(10);
}

void toBeNear() {
  Serial.println("to be near");
}

void toBeFar() {
  Serial.println("to be far");
}

  


