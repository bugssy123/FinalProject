int ledPins[] = {8, 9, 10, 11, 12};
int brightness = 0;
int fadeAmount = 5;
int index = 0;

void setup() {
  index = 0;
  while (index < 5){
    pinMode(ledPins[index], OUTPUT);
    index++;
  }
}

void loop(){
  index = 0;
  while (index < 5){
    fadeSettings (ledPins[index], true);
    index++;
  }
  index = 0;
  while (index < 5){
    fadeSettings (ledPins[index], false);
    index++;
  }

  brightness = brightness + fadeAmount;
  if(brightness <= 0 || brightness >= 255){
    fadeAmount = -fadeAmount;
  }
}

void fadeSettings (int pin, bool fadeIn){
  int brightness = (fadeIn) ? 0 : 255;
  int fadeAmount = (fadeIn) ? 5 : -5;

  while ((fadeIn && brightness <= 255) || (!fadeIn && brightness >= 0)){
  analogWrite(pin, brightness);
  brightness += fadeAmount;
  delay(30);
}
}
