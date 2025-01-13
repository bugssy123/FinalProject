const int photoResistorPin = A0;
const int greenLEDPin = 11;
const int yellowLEDPin = 12;
const int redLEDPin = 13;

float lowThreshold = 40.0;  
float highThreshold = 70.0; 
bool isAutomatic = true; 
String environment = "Cloudy"; 
String activeLED = "None";

unsigned long lastUpdate = 0; 

void setup() {
  Serial.begin(9600);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  turnOffAllLEDs();
  Serial.println("System Initialized in AUTOMATIC mode.");
}

void loop() {
  if (isAutomatic) {
    int sensorValue = analogRead(photoResistorPin);
    float lightIntensity = map(sensorValue, 0, 1023, 0, 100);

    if (millis() - lastUpdate >= 1000) {
      lastUpdate = millis();
      adjustThresholds(lightIntensity);  // Automatically adjust environment based on light intensity
      updateLEDs(lightIntensity);  // Update LEDs based on thresholds
      displayData(lightIntensity);
    }
  }

  if (Serial.available()) {
    handleCommand(Serial.readString());
  }
}

void adjustThresholds(float intensity) {
  if (intensity <= 40.0) {
    environment = "Cloudy";
  } else if (intensity <= 70.0) {
    environment = "Normal";
  } else {
    environment = "Bright Sunlight";
  }
}

void updateLEDs(float intensity) {
  turnOffAllLEDs();

  if (intensity <= lowThreshold) { 
    digitalWrite(greenLEDPin, HIGH);
    activeLED = "Green";
  } else if (intensity <= highThreshold) { 
    digitalWrite(yellowLEDPin, HIGH);
    activeLED = "Yellow";
  } else { 
    digitalWrite(redLEDPin, HIGH);
    activeLED = "Red";
  }
}

void displayData(float intensity) {
  Serial.print("Light Intensity: ");
  Serial.print(intensity);
  Serial.println("%");
  Serial.print("Current Mode: ");
  Serial.println(isAutomatic ? "Automatic" : "Manual");
  Serial.print("Active LED: ");
  Serial.println(activeLED);
  Serial.print("Environment: ");
  Serial.println(environment);
}

void handleCommand(String command) {
  command.trim(); 

  if (command.equalsIgnoreCase("MODE AUTO")) {
    isAutomatic = true;
    Serial.println("Switched to AUTOMATIC mode.");
  } else if (command.equalsIgnoreCase("MODE MANUAL")) {
    isAutomatic = false;
    Serial.println("Switched to MANUAL mode.");
  } else if (command.startsWith("SET LOW ") && !isAutomatic) {
    lowThreshold = command.substring(8).toFloat();
    Serial.print("Low threshold set to: ");
    Serial.println(lowThreshold);

    // Update LED based on the new low threshold
    updateManualLEDs(lowThreshold);
  } else if (command.startsWith("SET HIGH ") && !isAutomatic) {
    highThreshold = command.substring(9).toFloat();
    Serial.print("High threshold set to: ");
    Serial.println(highThreshold);

    // Simulate light intensity based on the high threshold
    simulateManualLightIntensity(highThreshold);
  } else {
    Serial.println("Error: Wrong command");
  }
}

void simulateManualLightIntensity(float threshold) {
  // Simulate light intensity directly based on the input threshold (in manual mode)
  updateManualLEDs(threshold);
}

void updateManualLEDs(float threshold) {
  // Directly set LED based on the threshold value
  if (threshold <= 40) { // Cloudy (Green LED)
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    activeLED = "Green";
  } 
  else if (threshold > 40 && threshold <= 70) { // Normal (Yellow LED)
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
    activeLED = "Yellow";
  } 
  else if (threshold > 70) { // Bright Sunlight (Red LED)
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
    activeLED = "Red";
  }
}

void turnOffAllLEDs() {
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);
}
