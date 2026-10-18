
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif
#include "pinballData.h"
#include "RedMP3.h"
// #include "fairy_visual_pinball.cpp"
#define SERIAL_2_MP3_RX 17
#define SERIAL_2_MP3_TX 16
#define DIFF 300


typedef int (*FuncP0)();

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(0, 0, 0);

uint32_t colorPin = strip.Color(0, 0, 0);
int inpin = 22;
uint32_t green = strip.Color(255, 0, 0);
uint32_t red = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t white = strip.Color(150, 255, 0);//strip.Color(255, 255, 255);
uint32_t off = strip.Color(0, 0, 0);
int ledCounter = 0;
#define MAXLEDCOUNTER 50

#ifdef FAIRY
void aLBumper() {
  operateSolenoidWithDelay(BUMPER_L, BUMPER_MILLIS);
  operateLedWithDelay(BUMPER_L_LED_TOP, LED_DELAY);
  operateLedWithDelay(BUMPER_L_LED_BOTTOM, LED_DELAY);
  Serial.println("<140>" + String(sweepCounter));

  addScore(1000);
}

void aRBumper() {
  operateSolenoidWithDelay(BUMPER_R, BUMPER_MILLIS);
  operateLedWithDelay(BUMPER_R_LED_TOP, LED_DELAY);
  operateLedWithDelay(BUMPER_R_LED_BOTTOM, LED_DELAY);
   Serial.println("<60>" + String(sweepCounter));

  addScore(1000);
}
void aPopBumper() {
  // Serial.println("<70>");
  operateSolenoidWithDelay(POP_BUMPER, BUMPER_MILLIS);
  addScore(1000);
}

//char soundString [] = {0x7E, 0x03, 0x33, 0x03, 0xEF, 0x00};
char soundString[] = { 0x7E, 0x04, 0x41, 0x00, 0x03, 0xEF, 0x00 };
char volumeString[] = { 0x7E, 0x03, 0x31, 0x1F, 0xEF, 0x00 };
char allSongsString[] = { 0x7E, 0x03, 0x33, 0x00, 0xEF, 0x00 };

void makeSounds() {
  for (char i = 7; i < 12; i++) {
    delay(500);
    soundString[4] = i;
     Serial.println("<100>" + String(int(i)) + "~" + String(i));
    Serial2.write(soundString, 6);
  }
}

int sol = 2;

void aLFlipper() {
  // operateSolenoidWithDelay(RELAY, FLIPPER_MILLIS);
  operateSolenoidWithDelay(sol, 300);
  Serial.println("<57>" + String(sol));
  
}
void aRFlipper() {
  // operateSolenoidWithDelay(FLIPPER_R, FLIPPER_MILLIS);
  // operateSolenoidWithDelay(BALL_RETURN, FLIPPER_MILLIS);
  // operateSolenoidWithDelay(BALL_RETURN, FLIPPER_MILLIS);
  operateSolenoidWithDelay(sol, 1000);
  Serial.println("<57>" + String(sol));
}
void a() {
}


void a100() {
  addScore(1000);
  // Serial.println("<83>");
}
void a1000() {
  addScore(1000);
}
void a5000() {
  addScore(5000);
}
void a10000() {
  addScore(10000);
}

void astartGame() {
  Serial.println("<130>" + String(0));
  // strip.setPixelColor(ledBonusArray[xcount], blue);
  // xcount++;
  // if (xcount > 10) xcount = 0;
  if (!gameOn) {
    // gameOn = true6;
    strip.setPixelColor(LED_OFF_BUMPER, white);
    strip.setPixelColor(LED_POP_BUMPER, off);
    score = 0;
    eBCount = 0;
    ball = 1;
   // operateSolenoidWithDelay(BALL_RETURN, BALL_RETURN_MILLIS);
    ballUp = true;
    strip.setPixelColor(LED_SHOOT_AGAIN_WHEN_LIT, white);
  }
sol++;
if (sol > 11){
  sol = 2;
}  
Serial.println("<59>" + String(sol));
}

void lightBonus(){
  for(int x = 1; x <= 20; x++){
    strip.setPixelColor(bonusLamp[x], off);
  }
  if ((bonus > 0) && (bonus < 21)){
    strip.setPixelColor(bonusLamp[bonus], white);
  }
}

void bonusCount(){
  if (bonus < 20){
    if (bonus > 0){
      bonus--;
      lightBonus();
    }
  }
}

void drainHit(){
}

void aballRestingInExit(){ //Bonus Hole
  bonusCount();
  drainHit();

}

void incrementBonus() {
  bonus++;
  if (bonus > MAX_BONUS) {
    bonus = 0;
    addScore(100000);
  }
  Serial.println("<84>" + String(bonus));
  for (int i = 0; i <= MAX_ADVANCE; i++) {
    if (i == bonus) {
      strip.setPixelColor(ledBonusArray[i], white);
    } else {
      strip.setPixelColor(ledBonusArray[i], off);
    }
  }
}

void incrementAdvance() {
  advance++;
  if (advance > MAX_ADVANCE) {
    advance = 0;
    incrementBonus();
  }
  for (int i = 0; i <= MAX_ADVANCE; i++) {
    if (i == advance) {
      strip.setPixelColor(ledCircleArray[i], white);
    } else {
      strip.setPixelColor(ledCircleArray[i], off);
    }
  }
}

bool on = false;
void aSpinner() {
  addScore(100);
  incrementAdvance();
}

FuncP0 inputFuncPs[] = {

  &a,           //22  //0 kick out
  &a,           //23  //1 top blue target 'on bumper' first switch
  &aPopBumper,  //24  //2 pop bumper
  &a,           //25  //3 left top bumper pop playfield
  &a,           //26  //4 left bottom bumper pop playfield
  &aSpinner,    //27  //5 spinner
  &a,           //28  //6 top red target
  &a,           //29  //7 A button
  &a1000,       //30  //8 left 1000 points button
  &a,           //31  //9 D button
  &a,           //32  //10 off bumper button
  &a,           //33  //11 A target first
  &aRBumper,    //34  //12 right lower bumper main playfield upper switch
  &a,           //35  //13 B target first
  &aRBumper,    //36  //14 right lower bumper main playfield lower switch
  &a,           //37  //15 left top bumper pop playfield
  &aLBumper,    //38  //16 left lower bumper main playfield upper switch
  &aLBumper,    //39  //17 left lower bumper main playfield lower switch
  &a,           //40  //18 left inner lane to flipper (Advance)
  &a10000,      //41  //19 left outer exit lane
  &aLFlipper,   //42  //20 left flipper button
  &a,           //43  //21 left flipper
  &aballRestingInExit,           //44  //22 ball resting in exit
  &a,           //45  //23 ball rolling down to launch
  &a,           //46  //24 right flipper
  &a,           //47  //25
  &a1000,       //48  //26 right 1000 points button
  &a,           //49  //27 right bottom bumper pop playfield
  &aRFlipper,   //50  //28 right flipper button
  &a,           //51  //29 middle blue target 'on bumper'
  &a,           //52  //30 right top bumper pop playfield
  &astartGame,  //53  //31 start button
  &a,           //A0  //56 //32
  &a,           //A1  //57 //33 D target
  &a,           //A2  //58 //34 right inner lane to flipper (Advance)
  &a,           //A3  //57 //35 right outer exit lane
  &a,           //A4  //56 //36 XXX
  &a10000,      //A5  //59 //37 right upper bumper main playfield
  &a,           //A6  //60 //38 C target
  &a,           //A7  //61 //39 D target
  &a,           //A8  //40
  &a,           //A9  //41
  &a,           //A10  //42
  &a,           //A11  //43
  &a,           //A12  //44
  &a,           //A13  //45
  &a,           //A14  //46

};
#endif

////////////////////////////////////////////////////////////

#ifdef WIGGLER
void aLBumper() {
  operateSolenoidWithDelay(SOL_L_SLINGSHOT, BUMPER_MILLIS);
  addScore(1000);
}


void a() {
  //  Serial.println("<304>");
}

int ledIndex = 0;
uint32_t ledArray[] = {white, green, blue, red, white};

void aStep(){
  Serial.println("<310>" + String(ledNumber));
  strip.setPixelColor(ledNumber, off);
  ledNumber++;
  strip.setPixelColor(ledNumber, ledArray[ledIndex]);
   Serial.println("<303>" + String(ledNumber));
  if (ledNumber >= NO_OF_LEDS){
    ledNumber = 0;
    ledIndex++;
    if (ledIndex >= (sizeof(ledArray) / sizeof(ledArray[0]))){
      ledIndex = 0;
    }
  }
  int j = solenoidPins[solNumber];
  digitalWrite(j, 0);
  solNumber++;
  if (solNumber >= SOLENOID_LENGTH){
    solNumber = 0;
  }
  j = solenoidPins[solNumber];
  digitalWrite(j, 1);
  addScore(1);
 Serial.println("<311>" + String(j));


}

void a100() {
  addScore(1000);
  // Serial.println("<83>");
}
void a1000() {
  addScore(1000);
}
void a5000() {
  addScore(5000);
}
void a10000() {
  addScore(10000);
}

void astartGame() {
  Serial.println("<130>" + String(0));
}


FuncP0 inputFuncPs[] = {

  &aStep,       //22  //0 //SW_DRAIN_KICKER y
  &a,           //23  //1 //SW_ZIP_SOLENOID_CONTACT
  &a,           //24  //2 
  &a,           //25  //3 //SW_IDLE_BALL_HIGH y
  &a,           //26  //4 //SW_IDLE_BALL_LOW y
  &a,           //27  //5 //SW_L_SLINGSHOT y
  &a,           //28  //6 
  &a,           //29  //7 
  &a,           //30  //8 //SW_BOTTOM_R_BUMPER y
  &a,           //31  //9 
  &a,           //32  //10
  &a,           //33  //11 //SW_CENTRE_MUSHROOM y
  &a,           //34  //12 
  &a,           //35  //13 //SW_BOTTOM_KICKER y
  &a,           //36  //14 //SW_TOP_KICKER y
  &a,           //37  //15 //SW_L_POP_BUMPER_SOLENOID
  &a,           //38  //16 //SW_TOP_R_BUMPER y 
  &a,           //39  //17 //SW_R_POP_BUMPER_SOLENOID
  &a,           //40  //18 //SE_TOP_L_BUMPER y
  &a,           //41  //19
  &a,           //42  //20 //SW_R_TOP_CHUTE y
  &a,           //43  //21 //SW_MIDDLE_CHUTE y
  &a,           //44  //22 //SW_WIGGLE_A y
  &a,           //45  //23 //SW_WIGGLE_B y
  &a,           //46  //24 //SW_MIDDLE_L_BUMPER
  &a,           //47  //25 //SW_WIGGLE_C y
  &a,           //48  //26 //SW_WIGGLE_D y
  &a,           //49  //27 //SW_L_MUSHROOM y
  &a,           //50  //28 //SW_WIGGLE_E y
  &a,           //A0  //54 //29 //SW_BOTTOM_L_BUMPER y
  &a,           //A1  //55 //30  //SW_L_CHUTE_TO_DRAIN y 
  &a,           //A2  //56 //31 //SW_L_SLINGSHOT_SOLENOID_CONTACT
  &a,           //A3  //57 //32 //SW_L_POP_BUMPER y
  &a,           //A4  //58 //33  //BUTTON_START y
  &a,           //A5  //59 //34  //BUTTON_L y
  &aStep,       //A6  //60 //35  //BUTTON_R y
  &a,           //A7  //61 //36  //BUTTON_R y ????
  &a,           //A8  //62 
  &a,           //A9  //63
  &a,           //A10  //64
  &a,           //A11  //65
  &a,           //A12  //66
  &a,           //A13  //67
  &a,           //A14  //68
  &a,           //A15  //69

};
#endif


void actionInputChanges(int index, int cpv) {
  // Serial.println("<6>" + String(index) + "|" + String(cpv) + ">");
  if (cpv == 1) {
    // Serial.println("<4A>" + String(index) + ">");
  } else {

    FuncP0 actionP = inputFuncPs[index];
    score = index;
     String scoreString = String(score) + '@';
     Serial1.print(scoreString);
    //  Serial.println("<4B>" + String(index) + "#" + String(inputPins[index]) + "$" + String(cpv) + ">");
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
        //  Serial.println("<17>" + timeDiffString + "~" + stringIndex + "@" + stringPin);
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
  // Serial.println("<30>");
  for (int i = 1; i < SOLENOID_LENGTH; i++) {
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
  Serial.println("<300>" + String(NO_OF_INPUT_PINS));
  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // noOfInputPins = sizeof(inputPins) / sizeof(int);
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
     Serial.print(String(inputPins[i]) + ",");
  }
   Serial.println("<302>" + String(NO_OF_INPUT_PINS));
  setupSolenoids();

  strip.setBrightness(250);  // Set BRIGHTNESS to about 1/5 (max = 255)
  // digitalWrite(solenoidPins[0], 1);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, off);
    ledCounters[i] = -1;
  }
  strip.setPixelColor(0, blue);
  strip.setPixelColor(1, white);
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

  // unsigned long diff = millis() - counter;
  // if ((diff >= DIFF)){
  //   // operateSolenoidWithDelay(BUMPER_L, FLIPPER_MILLIS);
  //   counter = millis();
  //   strip.setPixelColor(ledCounter, off);
  //   ledCounter++;
  //   if(ledCounter > MAXLEDCOUNTER){
  //     ledCounter = 0;
  //   }
  //   strip.setPixelColor(ledCounter, white);

  // }

  // addScore(1);
  strip.show();
}