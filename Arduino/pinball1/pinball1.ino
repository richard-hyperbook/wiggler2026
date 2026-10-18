
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
#define SOLENOID_LENGTH 6
#define RELAY_PIN 2
#define BUTTON_L 66
#define BUTTON_R 67
#define FLIPPER_L 4
#define FLIPPER_R 5
#define BUMPER_R_TOP_SWITCH 62
#define BUMPER_R_BOTTOM_SWITCH 63
#define BUMPER_R 7
#define BUMPER_R_LED_TOP 65
#define BUMPER_R_LED_BOTTOM 66
#define BUMPER_L_TOP_SWITCH 38
#define BUMPER_L_BOTTOM_SWITCH 39
#define BUMPER_L 3
#define BUMPER_L_LED_TOP 74
#define BUMPER_L_LED_BOTTOM 73
#define POP_BUMPER_SWITCH 64
#define POP_BUMPER 6
#define BUMPER_DELAY 10
#define LED_DELAY 20

#define ACTION_R_BUMPER 1
#define ACTION_L_BUMPER 2
#define ACTION_POP_BUMPER 3
#define ADD_1000 4
#define AA ADD_1000
#define ADD_10000 5
#define AB Add_10000
#define ADD_50000 6
#define AC ADD_50000



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
int solenoidPins[] = { 2, 3, 4, 5, 6, 7, 8 };
int solenoidCounters[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int inputPinValues[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};
int inputPinCounters[] = {
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
  ACTION_R_BUMPER, ACTION_R_BUMPER, ACTION_POP_BUMPER, AA, AA, AA, AA
};

int count = 0;
String bluetoothChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
long score = 0;
long lastScore = 0;
int noOfInputPins = 0;
String inputString;
int solenoidIndex = -1;
int ledCounters[LED_COUNT];
int ledNumber = 0;
int counter = 0;

void actionLBumper() {
  operateSolenoidWithDelay(BUMPER_L, BUMPER_DELAY);
  operateLedWithDelay(BUMPER_L_LED_TOP, LED_DELAY);
  operateLedWithDelay(BUMPER_L_LED_BOTTOM, LED_DELAY);
  addScore(1000);
}
void actionRBumper() {
  operateSolenoidWithDelay(BUMPER_R, BUMPER_DELAY);
  operateLedWithDelay(BUMPER_R_LED_TOP, LED_DELAY);
  operateLedWithDelay(BUMPER_R_LED_BOTTOM, LED_DELAY);
  addScore(1000);
}

void actionPopBumper() {
  operateSolenoidWithDelay(POP_BUMPER, BUMPER_DELAY);
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
      default:
        {
          break;
        }
    }
  }
}


void scanInputs() {
  if (loopCounter > MAX_LOOP_COUNT) {
    loopCounter = 0;
    Serial.println("<2>");
    for (int i = 0; i < MAX_LOOP_COUNT; i++) {
      if (inputPinCounters[i] < 0) {
        inputPinCounters[i] = 0;
      }
    }
  }
  //Serial.println("<3>");
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {

    inputPinCounters[i]--;
    int pin = inputPins[i];
    byte cpv = digitalRead(pin);
    // if (i == 40){
    // Serial.print("<" + String(i) + "|" + String(pin) + "+" + String(cpv) + "&" + String(inputPinCounters[i]) + ">");
    // }
    // Serial.println(cpv);


    if (inputPinCounters[i] < 1) {
      if (cpv != inputPinValues[i]) {
        inputPinCounters[i] = INPUT_PIN_COUNT;
        // if ((i == 40) || (i == 41)) {
        // Serial.println("<5>" + String(i) + "|" + String(pin) + "+" + String(cpv) + "&" + String(inputPinCounters[i]) + ">");
        // }
        actionInputChanges(i, cpv);
      }
    }
    inputPinValues[i] = cpv;
  }
  //  Serial.println("<1>");
}


void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    delay(wait);                                 //  Pause for a moment
  }
}

void testSolenoids() {

  inputString = Serial1.readString();
  int n = inputString.toInt();
  Serial.print(n);
  Serial.println('?');
  Serial.println(inputString);
  Serial.println('<');

  if (n > 0) {
    solenoidIndex = n - 2;
  }
  //  }
  /*
  if (solenoidIndex >= 0) {
    if (digitalRead(inputPins[BUTTON_L]) > 0) {
      Serial.print('-');
      digitalWrite(solenoidPins[solenoidIndex], 0);
    } else {
      Serial.print('+');
      digitalWrite(solenoidPins[solenoidIndex], 1);
    }
  }
  */
}

void operateSolenoidWithDelay(int solenoidNumber, int delay) {
  solenoidCounters[solenoidNumber] = delay;
  // Serial.println(solenoidCounters[solenoidNumber]);
}


void operateLedWithDelay(int ledNumber, int delay) {
  ledCounters[ledNumber] = delay;
  //Serial.println(ledCounters[ledNumber]);
}

void decrementSolenoidCounters() {
  for (int i = 0; i < SOLENOID_LENGTH; i++) {
    solenoidPins[i] = SOLENOID_PIN_START + i;
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], 0);
  }
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();


  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // noOfInputPins = sizeof(inputPins) / sizeof(int);
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < SOLENOID_LENGTH; i++) {
    solenoidPins[i] = SOLENOID_PIN_START + i;
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], 0);
  }

  //for (int i = 0; i < ANALOG_LENGTH; i++){
  //}
  // Turn OFF all pixels ASAP
  strip.setBrightness(250);  // Set BRIGHTNESS to about 1/5 (max = 255)
                             //pinMode (inpin, INPUT_PULLUP);
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

  // digitalWrite(FLIPPER_L, 1 - digitalRead(BUTTON_L));
  // digitalWrite(FLIPPER_R, 1 - digitalRead(BUTTON_R));
  for (int i = SOLENOID_PIN_START + 1; i < (SOLENOID_PIN_START + SOLENOID_LENGTH); i++) {
    if (solenoidCounters[i] > 0) {
      solenoidCounters[i]--;
    }
    if (solenoidCounters[i] > 0) {
      digitalWrite(i, 1);
    } else {
      digitalWrite(i, 0);
    }
    if (solenoidCounters[i] > 0) {
      // Serial.print(i);
      // Serial.print('-');
      // Serial.print(solenoidCounters[i]);
      // Serial.println('.');
    }
  }
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
    // if (ledCounters[i] > 0) {
    // Serial.print(i);
    // Serial.print('-');
    // Serial.print(ledCounters[i]);
    // Serial.println('.');
    // }
  }


  // if (digitalRead(BUTTON_L) == 0) {
  //   operateSolenoidWithDelay(FLIPPER_L, BUMPER_DELAY);
  //   incScore();
  // }
  // if (digitalRead(BUTTON_R) == 0) {
  //   operateSolenoidWithDelay(FLIPPER_R, BUMPER_DELAY);
  //   incScore();
  // }



  // if ((digitalRead(BUMPER_L_TOP_SWITCH) == 0) || (digitalRead(BUMPER_L_BOTTOM_SWITCH) == 0)) {
  //   operateSolenoidWithDelay(BUMPER_L, BUMPER_DELAY);
  //   operateLedWithDelay(BUMPER_L_LED_TOP, LED_DELAY);
  //   operateLedWithDelay(BUMPER_L_LED_BOTTOM, LED_DELAY);
  //   incScore();
  // }
  // if (digitalRead(POP_BUMPER_SWITCH) == 0) {
  //   operateSolenoidWithDelay(POP_BUMPER, BUMPER_DELAY);
  //   incScore();
  // }

  // if (Serial1.available() > 0) {
  //   inputString = Serial1.readString();
  //   // Serial.println(inputString);
  //   Serial1.print('@');

  //   ledNumber = inputString.toInt();
  //   // Serial1.println(ledNumber);
  //   if (ledNumber != 0) {
  //     operateLedWithDelay(ledNumber, LED_DELAY);
  //   }
  // }


  if (blinkToken == 0) {
    blinkToken = 20;
    strip.setPixelColor(6, green);
    // Serial.println("<8A>" + String(blinkToken));
  } else {
    blinkToken--;
    strip.setPixelColor(6, off);
    // Serial.println("<8B>" + String(blinkToken));
  }
  if (score != lastScore) {
    Serial.println("<9>" + String(score) + "^" + millis());
    //Serial1.print(score);
    lastScore = score;
  }
  /*
  if ((score % 10000) == 0){
    Serial.println("<13>");
    Serial1.print("AT");
    score = score + 1000;
  }
  if (Serial1.available() > 0){
    Serial.println("<14>");
    Serial.println("{" + Serial1.read() + '}');
  }
*/
  strip.show();
}