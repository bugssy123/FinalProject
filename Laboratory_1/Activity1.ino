int ledPins[] = {12, 11, 10, 9, 8}; 
int numLEDs = 5; 

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], HIGH);  
    delay(1000);                     
  }

  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], LOW);   
    delay(1000);                     
  }
}
