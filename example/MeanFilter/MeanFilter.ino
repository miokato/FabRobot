#define BUFFER_LENGTH 5
#define SENSORPIN 5

int buffer[BUFFER_LENGTH];
int index = 0;

void setup(){
    Serial.begin(9600);
}

void loop(){
    int raw = analogRead(SENSORPIN);
    buffer[index] = raw;
    index = (index + 1) % BUFFER_LENGTH;
    int smoothed = smoothByMeanFilter();

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

