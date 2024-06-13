#include <Adafruit_CircuitPlayground.h>

// ISR values
bool buttonFlag = false;
bool switchFlag = true;
bool switchState = true;

// Game-specific values
byte correct;
byte score;
byte winScore = 20;
byte spinSpeed = 120;
byte brightnessBall;
byte brightnessGoal;
byte lives = 5;

// Jingles
int winTune[2][8] = {
  { 233.08, 349.23, 466.16, 349.23, 311.13, 233.08, 440.00, 466.16 },
  { 180, 180, 180, 90, 90, 250, 90, 180 }
};
int loseTune[2][4] = {
  { 392.00, 329.63, 261.63, 65.496 },
  { 150, 350, 150, 500 }
};

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(7), switchISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(4), buttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), buttonISR, FALLING);
  gameReset(); }

void switchISR() {
  switchFlag = !switchFlag; }

void buttonISR() {
  buttonFlag = !buttonFlag; }

// Uses randomized value to reset the board for each round
void gameReset() {
  CircuitPlayground.setPixelColor(correct, 0, 0, 0);
  randomSeed(analogRead(0));
  correct = random(10);
  CircuitPlayground.setPixelColor(correct, brightnessGoal, brightnessGoal, brightnessGoal);
  buttonFlag = false; }

void loop() {
  // Detects change in switch state
  if (switchFlag) {
    delay(20);
    switchState = digitalRead(7);
    switchFlag = false; }

  // Changes brightness in quiet mode
  if (switchState) {
    brightnessBall = 120;
    brightnessGoal = 13; } 
  else {
    brightnessBall = 50;
    brightnessGoal = 1; }

  // Main gameplay
  if (buttonFlag) { // Has the player pressed the score button?
    if (score == correct) { // Yes, and the score equals the correct value
      for (int i = 0; i < 2; ++i) { // Flash green animation
        CircuitPlayground.setPixelColor(score, 0, 0, 0);
        delay(60);
        CircuitPlayground.setPixelColor(score, 0, brightnessBall, 0);
        delay(60); }
      spinSpeed = spinSpeed-20; // Increase speed
      gameReset();
      } else { // No
        CircuitPlayground.setPixelColor(correct, brightnessGoal, 0, 0); // Tint goal red
        for (int i = 0; i < 2; ++i) { // Flash red animation
          CircuitPlayground.setPixelColor(score, brightnessBall, 0, 0);
          delay(60);
          CircuitPlayground.setPixelColor(score, 0, 0, 0);
          delay(60); }
        lives = lives-1; // Subtract a life
        gameReset(); }
    } else if (spinSpeed == winScore) { // Win condition, if the player meets the required win score
        for (int i = 0; i < 10; ++i) { // Paint entire screen green
          CircuitPlayground.setPixelColor(i, 0, brightnessBall, 0); }
        if (switchState) { // Play win jingle
          for (int i = 0; i < 8; ++i) {
            CircuitPlayground.playTone(winTune[0][i], winTune[1][i]); }
        }
        delay(100000);
    } else if (lives == 0) { // Lose condition, if the player runs out of lives
        for (int i = 0; i < 10; ++i) { // Paint entire screen red
          CircuitPlayground.setPixelColor(i, brightnessBall, 0, 0); }
        if (switchState) { // Play lose jingle
          for (int i = 0; i < 4; ++i) {
            CircuitPlayground.playTone(loseTune[0][i], loseTune[1][i]); }
        }
        delay(100000);
    } else { for (int i = 0; i < 10; ++i) { // Spinning effect
        if (buttonFlag) { // Interrupt function for instant response
          break; }
        score = i; // Set score to i integer
        CircuitPlayground.setPixelColor(i, brightnessBall, brightnessBall, brightnessBall); // Paint i integer to screen
        if ((i+9)%10 != correct) {  // Blank out the previous i integer to screen
          CircuitPlayground.setPixelColor((i+9)%10, 0, 0, 0); } else {
          CircuitPlayground.setPixelColor(correct, brightnessGoal, brightnessGoal, brightnessGoal); }
        delay(spinSpeed); }
  }
}