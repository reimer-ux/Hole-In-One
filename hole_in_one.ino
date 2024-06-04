#include <Adafruit_CircuitPlayground.h>

const byte buttonPin = 4;
const byte switchPin = 7;
bool ButtonFlag = false;
bool SwitchFlag = true;
int correct;
int score;
int blank;


void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
  randomSeed(analogRead(0));
  correct = random(10);
  Serial.println(correct);
  CircuitPlayground.setPixelColor(correct, 15, 15, 15);
}

void switchISR() {
  SwitchFlag = !SwitchFlag;
}

void buttonISR() {
  ButtonFlag = !ButtonFlag;
}

void loop() {
  
  if (ButtonFlag) {
    if (score == correct) {
      for (int i = 0; i < 10; ++i) {
        CircuitPlayground.setPixelColor(i, 255, 255, 255);
        }
      } else {
        for (int i = 0; i < 10; ++i) {
        CircuitPlayground.setPixelColor(i, 255, 0, 0);
        }
      }
    } else {
      for (int i = 0; i < 10; ++i) {
        blank = (i+9)%10;
        score = i;
        CircuitPlayground.setPixelColor(i, 100, 100, 100);
        if (blank != correct) {
          CircuitPlayground.setPixelColor(blank, 0, 0, 0);
        } else {
          CircuitPlayground.setPixelColor(correct, 15, 15, 15);
        }
        Serial.println(score);
        delay(200);
      }
  }

}
