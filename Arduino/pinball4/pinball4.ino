
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif
#include "fairyData.h"
#include "RedMP3.h"
// #include "fairy_visual_pinball.cpp"
#define SERIAL_2_MP3_RX 17
#define SERIAL_2_MP3_TX 16
#define DIFF 1000



Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(0, 0, 0);

uint32_t colorPin = strip.Color(0, 0, 0);
int inpin = 22;
uint32_t green = strip.Color(255, 0, 0);
uint32_t red = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t white = strip.Color(255, 255, 255);
uint32_t off = strip.Color(0, 0, 0);
int ledCounter = 0;
//  unsigned long counter = 0;
#define MAXLEDCOUNTER 50


//char soundString [] = {0x7E, 0x03, 0x33, 0x03, 0xEF, 0x00};
char soundString[] = { 0x7E, 0x04, 0x41, 0x00, 0x03, 0xEF, 0x00 };
char volumeString[] = { 0x7E, 0x03, 0x31, 0x1F, 0xEF, 0x00 };
char allSongsString[] = { 0x7E, 0x03, 0x33, 0x00, 0xEF, 0x00 };

void makeSounds() {
  for (char i = 7; i < 12; i++) {
    delay(500);
    soundString[4] = i;
    //  Serial.println("<100>" + String(int(i)) + "~" + String(i));
    Serial2.write(soundString, 6);
  }
}

int sol = 2;
void actionInputChanges(int index, int cpv) {
  // Serial.println("<6>" + String(index) + "|" + String(cpv) + ">");
  if (cpv == 1) {

    // Serial.println("<4A>" + String(index) + ">");

  } else {

    FuncP0 actionP = inputFuncPs[index];
    // Serial.println("<4B>" + String(index) + "#" + String(cpv) + ">");
    actionP();
    // Serial.println("<4C>" + String(index) + ">");
  }
}


void scanInputs() {
  // Serial.println("<3>" + String(digitalRead(22)));
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    int pin = inputPins[i];
    byte cpv = digitalRead(pin);
    if (cpv != inputPinValues[i]) {
      unsigned long timeDiff = millis() - inputPinCounters[i];
      String timeDiffString = String(timeDiff);
      String stringPin = String(pin);
      String stringIndex = String(i);
      if (timeDiff < BOUNCE_TIME) {
        Serial.println("<17>" + timeDiffString + "~" + stringIndex + "@" + stringPin);
      } else {
        inputPinCounters[i] = millis();
        Serial.println("<18>" + timeDiffString + "~" + stringIndex + "@" + stringPin);
        actionInputChanges(i, cpv);
      }
    }

    inputPinValues[i] = cpv;
  }
  //  Serial.println("<1>");
}

void driveOutputs() {
  //Serial.println("<30>");
  for (int i = 1; i < SOLENOID_LENGTH; i++) {
    int j = solenoidPins[i];
    if (solenoidCounters[j] != 0) {
      // Serial.print("<31>");
      // Serial.print(j);
      // Serial.print("?");
      // Serial.println(solenoidCounters[j]);
      if (solenoidCounters[j] > millis()) {
        digitalWrite(j, 1);
      } else {
        solenoidCounters[j] = 0;
        digitalWrite(j, 0);
      }
    }
  }
}

void setupSolenoids() {
  for (int i = 0; i < SOLENOID_LENGTH; i++) {
    int j = solenoidPins[i];
    solenoidCounters[j] = 0;
    pinMode(j, OUTPUT);
    digitalWrite(j, 0);
    Serial.println("<110>" + String(j));
  }
  //  digitalWrite(RELAY, 0);
  // analogWrite(RELAY, 64);
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    delay(wait);                                 //  Pause for a moment
  }
}

void operateSolenoidWithDelay(int solenoidNumber, int delay) {
  solenoidCounters[solenoidNumber] = delay + millis();
   Serial.println("<52>" + String(solenoidNumber) + "*" + String(solenoidCounters[solenoidNumber]) + "?" + String(solenoidCounters[solenoidNumber]));
}


void operateLedWithDelay(int ledNumber, int delay) {
  ledCounters[ledNumber] = delay;
  //Serial.println(ledCounters[ledNumber]);
}

void sweepDisplay() {

  int xOrY = 0;
  int maxCoord = MAX_X;
  if (isVerticalSweep) {
    xOrY = 1;
    maxCoord = MAX_Y;
  }
  for (int i = 0; i < PLAYFIELD_LEDS; i++) {
    if (ledCoords[i][xOrY] != 0) {
      strip.setPixelColor(i, off);
      if (abs(ledCoords[i][xOrY] - (sweepCounter)) < SWEEP_WIDTH) {
        strip.setPixelColor(i, white);
      }
    }
  }
  sweepCounter = sweepCounter + SWEEP_INCREMENT;
  //  Serial.println("<61>" + String(sweepCounter));
  if (sweepCounter > maxCoord) {
    sweepCounter = 0;
    isVerticalSweep = !isVerticalSweep;
  }
}


void setup() {
  counter = millis();

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // noOfInputPins = sizeof(inputPins) / sizeof(int);
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  setupSolenoids();

  strip.setBrightness(250);  // Set BRIGHTNESS to about 1/5 (max = 255)
  // digitalWrite(solenoidPins[0], 1);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, off);
    ledCounters[i] = -1;
  }
  strip.setPixelColor(0, green);
  strip.setPixelColor(LED_POP_BUMPER, white);
  strip.show();
  delay(1000);
  // analogWrite(RELAY, 32);
}


void addScore(long increment) {
  score = score + increment;
  String scoreString = String(score) + '@';
  Serial1.print(scoreString);
}



void loop() {
  scanInputs();
  driveOutputs();
  // analogWrite(RELAY, 32);
  //  digitalWrite(RELAY, 1);
  for (int i = 0; i < (LED_COUNT); i++) {
    if (ledCounters[i] > 0) {
      ledCounters[i]--;
    }

    if (ledCounters[i] > 0) {
      strip.setPixelColor(i, white);
      // Serial.println("<7A>" + String(i) + "|" + String(ledCounters[i]) + ">");
    } else {
      if (ledCounters[i] == 0) {
        strip.setPixelColor(i, off);
        // Serial.println("<7B>" + String(i) + "|" + String(ledCounters[i]) + ">");
        ledCounters[i] = -1;
      }
    }
  }

  if (blinkToken == 0) {
    blinkToken = 20;
    strip.setPixelColor(6, red);
    // Serial.println("<8A>" + String(blinkToken));
  } else {
    blinkToken--;
    strip.setPixelColor(6, off);
    // Serial.println("<8B>" + String(blinkToken));
  }
  if (score != lastScore) {
    // Serial.println("<9>" + String(score) + "^" + millis());
    //Serial1.print(score);
    lastScore = score;
  }
  if (!inPlay) {
    sweepDisplay();
  }

  unsigned long diff = millis() - counter;
  if ((diff >= DIFF)){
    // operateSolenoidWithDelay(BUMPER_L, FLIPPER_MILLIS);
    counter = millis();
    strip.setPixelColor(ledCounter, off);
    ledCounter++;
    if(ledCounter > MAXLEDCOUNTER){
      ledCounter = 0;
    }
    strip.setPixelColor(ledCounter, white);

  }


  strip.show();
}

//#include "fairyCode.cpp"