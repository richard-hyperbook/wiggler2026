
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
#define SOL 2
#define DIGITAL_START 22
#define DIGITAL_LENGTH 34
#define ANALOG_LENGTH 10
#define TOTAL_LENGTH 44
#define SOLENOID_PIN_START 2
#define SOLENOID_LENGTH 7
#define RELAY_PIN 2
#define BUTTON_L 66
#define BUTTON_R 67

#define RELAY 2
#define BUMPER_L 3
#define FLIPPER_L 4
#define FLIPPER_R 5
#define POP_BUMPER 6
#define BUMPER_R 7
#define BALL_RETURN 8

#define BUMPER_R_TOP_SWITCH 62
#define BUMPER_R_BOTTOM_SWITCH 63
#define BUMPER_R_LED_TOP 65
#define BUMPER_R_LED_BOTTOM 66
#define BUMPER_L_TOP_SWITCH 38
#define BUMPER_L_BOTTOM_SWITCH 39

#define BUMPER_L_LED_TOP 74
#define BUMPER_L_LED_BOTTOM 73
#define POP_BUMPER_SWITCH 64

#define BUMPER_DELAY 10
#define LED_DELAY 20
#define BUMPER_MILLIS 300
#define FLIPPER_MILLIS 1000


#define ACTION_R_BUMPER 1
#define ACTION_L_BUMPER 2
#define ACTION_POP_BUMPER 3

#define ADD_1000 4
#define AA ADD_1000
#define ADD_10000 5
#define AB Add_10000
#define ADD_50000 6
#define AC ADD_50000
#define BOUNCE_TIME 100
#define ACTION_L_FLIPPER 7
#define ACTION_R_FLIPPER 8
#define ACTION_TEST 9


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

int outpin = 9;
int outValue = 0;
//int digitalPins[DIGITAL_LENGTH];
// int inputValues[TOTAL_LENGTH];
char inputChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
char oldChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
int analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 };
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
int solenoidPins[]  //= { 2, 3, 4, 5, 6, 7, 8 };
  = { RELAY_PIN, BUMPER_L, FLIPPER_L, FLIPPER_R, POP_BUMPER, BUMPER_R };

unsigned long solenoidCounters[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int inputPinValues[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};
unsigned long inputPinCounters[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};
int inputPinFunctionIndex01[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};
int inputPinFunctionIndex10[] = {
  AA, AA, AA, AA, AA, AA, AA, AA, AA, AA,
  AA, AA, AA, AA, AA, AA, AA, ACTION_L_BUMPER, ACTION_L_BUMPER, AA,
  AA, AA, AA, AA, AA, AA, AA, AA, AA, AA,
  AA, AA, AA, AA, AA, AA, AA, AA, AA, AA,
  ACTION_R_BUMPER, ACTION_R_BUMPER, ACTION_POP_BUMPER, AA, ACTION_L_FLIPPER, ACTION_R_FLIPPER, AA
};

int count = 0;
String bluetoothChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
long score = 0;
long lastScore = 0;
int noOfInputPins = 0;
String inputString;
int solenoidIndex = -1;
int ledCounters[LED_COUNT];
int ledNumber = -1;
int counter = 0;


void actionLBumper() {
  operateSolenoidWithDelay(BUMPER_L, BUMPER_MILLIS);
  operateLedWithDelay(BUMPER_L_LED_TOP, LED_DELAY);
  operateLedWithDelay(BUMPER_L_LED_BOTTOM, LED_DELAY);
  addScore(1000);
}
void actionRBumper() {
  operateSolenoidWithDelay(BUMPER_R, BUMPER_MILLIS);
  operateLedWithDelay(BUMPER_R_LED_TOP, LED_DELAY);
  operateLedWithDelay(BUMPER_R_LED_BOTTOM, LED_DELAY);
  strip.setPixelColor(ledNumber, off);
  ledNumber++;
  strip.setPixelColor(ledNumber, white);
  Serial.println("<80>" + String(ledNumber)); 
  Serial1.println(String(ledNumber) + "<<<");
  if (ledNumber > LED_COUNT){
    ledNumber = -1;
  }
  addScore(1000);
}
void actionLFlipper() {
  Serial.println("<50>" + String(FLIPPER_L));
  operateSolenoidWithDelay(FLIPPER_L, FLIPPER_MILLIS);
  operateSolenoidWithDelay(BALL_RETURN, FLIPPER_MILLIS);
}
void actionRFlipper() {
  operateSolenoidWithDelay(FLIPPER_R, FLIPPER_MILLIS);
  operateSolenoidWithDelay(BALL_RETURN, FLIPPER_MILLIS);
}

void actionPopBumper() {
  operateSolenoidWithDelay(POP_BUMPER, BUMPER_MILLIS);
  addScore(1000);
}


void actionInputChanges(int index, int cpv) {
  // Serial.println("<6>" + String(index) + "|" + String(cpv) + ">");
  if (cpv == 1) {
    int actionIndex = inputPinFunctionIndex01[index];
    // Serial.println("<4A>" + String(index) + "|" + String(actionIndex) + ">");
    switch (actionIndex) {
      case 0:
        {
          break;
        }
      case 1:
        {

          break;
        }
      default:
        {

          break;
        }
    }
  } else {

    int actionIndex = inputPinFunctionIndex10[index];
    // Serial.println("<4B>" + String(index) + "|" + String(actionIndex) + ">");
    switch (actionIndex) {
      case 0:
        {
          break;
        }
      case ACTION_R_BUMPER:
        {
          actionRBumper();
          break;
        }
      case ACTION_L_BUMPER:
        {
          actionLBumper();
          break;
        }
      case ACTION_POP_BUMPER:
        {
          actionPopBumper();
          break;
        }
      case ADD_1000:
        {
          addScore(1000);
          break;
        }
      case ADD_10000:
        {
          addScore(10000);
          break;
        }
      case ADD_50000:
        {
          addScore(50000);
          break;
        }
      case ACTION_L_FLIPPER:
        {
          actionLFlipper();
          break;
        }
      case ACTION_R_FLIPPER:
        {
          actionRFlipper();
          break;
        }
      default:
        {
          break;
        }
    }
  }
}


void scanInputs() {
  //Serial.println("<3>");
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    int pin = inputPins[i];
    byte cpv = digitalRead(pin);
    if (cpv != inputPinValues[i]) {
      unsigned long timeDiff = millis() - inputPinCounters[i];
      String timeDiffString = String(timeDiff);
      if (timeDiff < BOUNCE_TIME) {
        Serial.println("<17>" + timeDiffString);
      } else {
        inputPinCounters[i] = millis();
        Serial.println("<18>" + timeDiffString);
        actionInputChanges(i, cpv);
      }
    }

    inputPinValues[i] = cpv;
  }
  //  Serial.println("<1>");
}

void driveOutputs() {
  //Serial.println("<30>");
  for (int i = 0; i < SOLENOID_LENGTH; i++) {
    int j = solenoidPins[i];
    if (solenoidCounters[j] != 0) {
      Serial.print("<31>");
      Serial.print(j);
      Serial.print("?");
      Serial.println(solenoidCounters[j]);
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
  }
  digitalWrite(RELAY, 1);
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
  Serial.println("<52>" + String(solenoidCounters[solenoidNumber]));
}


void operateLedWithDelay(int ledNumber, int delay) {
  ledCounters[ledNumber] = delay;
  //Serial.println(ledCounters[ledNumber]);
}

// void decrementSolenoidCounters() {
//   for (int i = 0; i < SOLENOID_LENGTH; i++) {
//     solenoidPins[i] = SOLENOID_PIN_START + i;
//     pinMode(solenoidPins[i], OUTPUT);
//     digitalWrite(solenoidPins[i], 0);
//   }
// }

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
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
}

void loop() {
  scanInputs();
  driveOutputs();

  for (int i = 0; i < (LED_COUNT); i++) {
    if (ledCounters[i] > 0) {
      ledCounters[i]--;
    }

    if (ledCounters[i] > 0) {
      strip.setPixelColor(i, white);
      Serial.println("<7A>" + String(i) + "|" + String(ledCounters[i]) + ">");
    } else {
      if (ledCounters[i] == 0) {
        strip.setPixelColor(i, off);
        Serial.println("<7B>" + String(i) + "|" + String(ledCounters[i]) + ">");
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
     Serial.println("<8B>" + String(blinkToken));
  }
  if (score != lastScore) {
    Serial.println("<9>" + String(score) + "^" + millis());
    Serial1.print(score);
    lastScore = score;
  }

  strip.show();
}