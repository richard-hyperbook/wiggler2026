
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define NO_OF_INPUT_PINS 47
#define MAX_LOOP_COUNT 1000
#define INPUT_PIN_COUNT 20
#define LED_PIN 13
#define LED_COUNT 100
#define SOLENOID_LENGTH 6
#define SOLENOID_PIN_START 2
int inputPins[] = {
  /* 0   1   2   3   4   5   6   7   8   9 */
  /*0*/ 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  /*1*/ 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
  /*2*/ 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
  /*    54, 55, 56, 57, 58, 59, 60, 61, */
  /*3*/ 52, 53, A0, A1, A2, A3, A4, A5, A6, A7,
  /*    62, 63, 64, 65, 66, 67, 68, 69  */
  /*4*/ A8, A9, A10, A11, A12, A13, A14, A15
};

int solenoidPins[] = { 2, 3, 4, 5, 6, 7, 8 };
int ledCounters[LED_COUNT];
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(0, 0, 0);

uint32_t colorPin = strip.Color(0, 0, 0);
int inpin = 22;
uint32_t green = strip.Color(255, 0, 0);
uint32_t red = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t white = strip.Color(255, 255, 255);
uint32_t off = strip.Color(0, 0, 0);

int loopCounter = 0;
int blinkToken = 0;
long score = 0;


void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    delay(wait);                                 //  Pause for a moment
  }
}


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();
score = 0;

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < SOLENOID_LENGTH; i++) {
    solenoidPins[i] = SOLENOID_PIN_START + i;
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], 0);
  }

  strip.setBrightness(250);  // Set BRIGHTNESS to about 1/5 (max = 255)
  digitalWrite(solenoidPins[0], 1);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, off);
    ledCounters[i] = -1;
  }
  strip.setPixelColor(0, green);
  strip.show();
}


void addScore(long increment) {
  score = score + increment;
  String scoreString = String(score) + '@';
  Serial1.print(scoreString);
  Serial.println(scoreString);
  //Serial.println(score);
}


void loop() {
  //scanInputs();
  addScore(1);
  


  if (blinkToken == 0) {
    blinkToken = 1;
    strip.setPixelColor(6, blue);
    // Serial.println("<8A>" + String(blinkToken));
  } else {
    blinkToken = 0;
    strip.setPixelColor(6, off);
    // Serial.println("<8B>" + String(blinkToken));
  }
 
  strip.show();
  delay (2000);
}