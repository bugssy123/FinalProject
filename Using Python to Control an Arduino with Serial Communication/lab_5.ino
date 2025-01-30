// Pin Definitions
const int photoResistorPin = A0; // Photoresistor analog input
const int greenLedPin = 13;      // Green LED pin
const int yellowLedPin = 12;     // Yellow LED pin
const int redLedPin = 11;        // Red LED pin

// Thresholds
int lowThreshold = 40;  // Default Low Threshold
int highThreshold = 70; // Default High Threshold

// Modes
bool isAutomaticMode = true; // true = Automatic Mode, false = Manual Mode

// Timing
unsigned long lastUpdateTime = 0; // Timer for Serial Updates
const unsigned long updateInterval = 1000; // Update Interval (ms)

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize LED pins
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  // Turn off all LEDs initially
  turnOffAllLeds();

  Serial.println("System Initialized.");
}

void loop() {
  // Read Photoresistor Value and Convert to Percentage
  int sensorValue = analogRead(photoResistorPin);
  int lightIntensity = map(sensorValue, 0, 1023, 0, 100); // Convert to percentage

  // Handle Automatic Mode
  if (isAutomaticMode) {
    adjustThresholdsBasedOnLight(lightIntensity);
  }

  // Determine Active LED and Environment
  String activeLed = determineActiveLed(lightIntensity);
  String environment = determineEnvironment(lightIntensity);

  // Update Serial Monitor Every Second
  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();
    displayStatus(lightIntensity, activeLed, environment);
  }

  // Handle Serial Commands
  handleSerialCommands();
}

// Function to Adjust Thresholds Dynamically in Automatic Mode
void adjustThresholdsBasedOnLight(int lightIntensity) {
  if (lightIntensity <= 40) {
    lowThreshold == 0;
    highThreshold == 40;
  } else if (lightIntensity <= 70) {
    lowThreshold == 41;
    highThreshold = 70;
  } else if (lightIntensity <= 70){
    lowThreshold == 71;
    highThreshold == 100;
  }
}

// Function to Determine Active LED Based on Light Intensity
String determineActiveLed(int lightIntensity) {
  // Turn off all LEDs first
  turnOffAllLeds();

  // Determine which LED to turn on based on light intensity
  if (lightIntensity >= 0 && lightIntensity <= lowThreshold) {
    digitalWrite(greenLedPin, HIGH); // Light up Green LED
    return "Green";
  } else if (lightIntensity > lowThreshold && lightIntensity <= highThreshold) {
    digitalWrite(yellowLedPin, HIGH); // Light up Yellow LED
    return "Yellow";
  } else if (lightIntensity > highThreshold && lightIntensity <= 100) {
    digitalWrite(redLedPin, HIGH); // Light up Red LED
    return "Red";
  } else {
    return "None"; // Return "None" if lightIntensity is out of range
  }
}

// Function to Determine Environment Based on Light Intensity
String determineEnvironment(int lightIntensity) {
  // Determine the environment based on light intensity percentage
  if (lightIntensity >= 0 && lightIntensity <= 40) {
    return "Cloudy"; // Low light levels
  } else if (lightIntensity > 40 && lightIntensity <= 70) {
    return "Normal"; // Medium light levels
  } else if (lightIntensity > 70 && lightIntensity <= 100) {
    return "Bright Sunlight"; // High light levels
  } else {
    return "Invalid Light Intensity"; // Catch any unexpected values
  }
}

// Function to Display System Status on Serial Monitor
void displayStatus(int lightIntensity, String activeLed, String environment) {
  Serial.print("Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.print("% Current Mode: ");
  Serial.print(isAutomaticMode ? "Automatic" : "Manual");
  Serial.print(" Active LED: ");
  Serial.print(activeLed);
  Serial.print(" Environment: ");
  Serial.println(environment);
}

// Function to Handle Serial Commands
void handleSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove Leading and Trailing Whitespace

    if (command.equalsIgnoreCase("MODE AUTO")) {
      isAutomaticMode = true;
      Serial.println("Switched to Automatic Mode.");
    } else if (command.equalsIgnoreCase("MODE MANUAL")) {
      isAutomaticMode = false;
      Serial.println("Switched to Manual Mode.");
    } else if (command.startsWith("SET LOW ")) {
      if (!isAutomaticMode) {
        lowThreshold = command.substring(9).toInt();
        Serial.print("Low Threshold Set to: ");
        Serial.println(lowThreshold);
      } else {
        Serial.println("Error: Command Only Allowed in Manual Mode.");
      }
    } else if (command.startsWith("SET HIGH ")) {
      if (!isAutomaticMode) {
        highThreshold = command.substring(9).toInt();
        Serial.print("High Threshold Set to: ");
        Serial.println(highThreshold);
      } else {
        Serial.println("Error: Command Only Allowed in Manual Mode.");
      }
    } else {
      Serial.println("Error: Wrong Command.");
    }
  }
}

// Helper Function to Turn Off All LEDs
void turnOffAllLeds() {
  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}
