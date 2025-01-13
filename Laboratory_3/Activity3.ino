const int tempSensorPin = A0;  
const int photoResistorPin = A2;  
const int ledPin = 12;  

const int tempThreshold = 50;  
const int brightnessThreshold = 220;  

void setup() {
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600); 
}

void loop() {
  
  int tempValue = analogRead(tempSensorPin);
  
  float voltage = tempValue * (5.0 / 1023.0);  
  float temperatureC = (voltage - 0.5) * 100.0;  

  int brightnessValue = analogRead(photoResistorPin);

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" °C, Brightness: ");
  Serial.println(brightnessValue);

  if (temperatureC >= tempThreshold && brightnessValue >= brightnessThreshold) {
    
    digitalWrite(ledPin, HIGH);  
    delay(100);  
    digitalWrite(ledPin, LOW);  
    delay(100); 
  } else {
    digitalWrite(ledPin, LOW);  
  }

  delay(100);  
}
