
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
int element1 = 0;
int digit1 = 0;
int xx = 0;

typedef int (*FuncP0)();

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(0, 0, 0);

uint32_t colorPin = strip.Color(0, 0, 0);
int inpin = 22;
uint32_t green = strip.Color(255, 0, 0);
uint32_t red = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t white = strip.Color(150, 255, 50);  //strip.Color(255, 255, 255);
uint32_t off = strip.Color(0, 0, 0);
int ledCounter = 0;
#define MAXLEDCOUNTER 50

#ifdef WIGGLER

void aLBumper() {
  operateSolenoidWithDelay(INDEX_SOL_L_SLINGSHOT, BUMPER_MILLIS);
  addToScore(1000);
}

void a() {
  //  //=//+Serial.println("<304>");
}

int ledIndex = 0;
uint32_t ledArray[] = { white, green, blue, red, white };

void setLed(int ledN, bool state) {
  // debugInt('O', ledN);
  if (state) {
    strip.setPixelColor(ledN, white);
  } else {
    strip.setPixelColor(ledN, off);
  }
  ledState[ledN] = state;
}

void aStep() {
  //=//+Serial.println("<310>" + String(ledNumber));
  strip.setPixelColor(ledNumber, off);
  ledNumber++;
  strip.setPixelColor(ledNumber, ledArray[ledIndex]);
  ////=//+Serial.println("<303>" + String(ledNumber));
  if (ledNumber >= NO_OF_LEDS) {
    ledNumber = 0;
    ledIndex++;
    if (ledIndex >= (sizeof(ledArray) / sizeof(ledArray[0]))) {
      ledIndex = 0;
    }
  }
  int j = solenoidPins[solNumber];
  //digitalWrite(solNumber, 0);
  solNumber++;
  //=//+Serial.println("<XXXXX>" + String(solNumber) + "&" + String(j));
  if (solNumber > SOLENOID_LENGTH + 1) {
    solNumber = -1;
  }
  j = solenoidPins[solNumber];
  operateSolenoidWithDelay(solNumber, 500);
  addToScore(1);
  ////=//+Serial.println("<311>" + String(j));
}

void firstBallPlayed() {
  if (state == STATE_ON) {
    state = STATE_IN_PLAY;
  }
}

void a1() {
  addToScore(1);
  ////=//+Serial.println("<83-1>");
}
void a10() {
  addToScore(10);
  ////=//+Serial.println("<83-10>");
}
void a100() {
  addToScore(100);
  ////=//+Serial.println("<83-100>");
}
void a1000() {
  //addToScore(1000);
}
void aHit200() {
  addToScore(1);
  setLed(LED_TOP_200, true);
  setLed(LED_HIT_WHEN_LIT_TO_LITE_R, true);
  Serial.println("<83-200>");
}

 int x = 0;
void aTopSideChutes() {
   setLed(x, false);
    x++;
    setLed(x, true);
    if(x > 60){
      x = 0;
    }
   a10();
}

void aLMushroom() {
  debugInt('M', ledState[LED_WIGGLESVILLE_100]);
  if (ledState[LED_WIGGLESVILLE_100]) {
    setLed(LED_WIGGLESVILLE_300, true);
  } else {
    if (ledState[LED_WIGGLESVILLE_300]) {
      setLed(LED_WIGGLESVILLE_500, true);
    } else {
      setLed(LED_WIGGLESVILLE_100, true);
    }
  }
  if (!ledState[LED_WIGGLE_ALLEY_A]) {
    setLed(LED_WIGGLE_ALLEY_A, true);
  } else {
    if ((ledState[LED_WIGGLE_ALLEY_A]) && !(ledState[LED_WIGGLE_ALLEY_B])) {
      setLed(LED_WIGGLE_ALLEY_B, true);
    } else {
      if ((ledState[LED_WIGGLE_ALLEY_B]) && !(ledState[LED_WIGGLE_ALLEY_C])) {
        setLed(LED_WIGGLE_ALLEY_C, true);
      } else {
        if ((ledState[LED_WIGGLE_ALLEY_C]) && !(ledState[LED_WIGGLE_ALLEY_D])) {
          setLed(LED_WIGGLE_ALLEY_D, true);
        }
      }
    }
  }
  debugInt('N', ledState[LED_WIGGLESVILLE_100]);
}

void incrementWiggle(int step) {
  int wiggleLedIndexes[] = { LED_WIGGLE_ALLEY_A, LED_WIGGLE_ALLEY_B, LED_WIGGLE_ALLEY_C, LED_WIGGLE_ALLEY_D };
  int wiggleScores[] = { 100, 100, 100, 200 };
  if (ledState[wiggleLedIndexes[step]]) {
    addToScore(wiggleScores[step]);
  } else {
    addToScore(1);
  }
  debugInt('L', step);
}

void aWiggleA() {
  incrementWiggle(0);
}

void aWiggleB() {
  incrementWiggle(1);
}

void aWiggleC() {
  incrementWiggle(2);
}

void aWiggleD() {
  incrementWiggle(3);
}

void aTopMiddleChute() {
  if (ledState[LED_TOP_200]) {
    addToScore(200);
  } else {
    addToScore(10);
  }
  setLed(LED_TOP_200, 0);
}



void delayedBallRelease() {
  operateSolenoidWithDelay(INDEX_SOL_BALL_RELEASE, 500);
}

void aBallInDrain() {
  Serial.println("(95A)");
  setLed(LED_FREE_BALL_GATE_OPEN_WHEN_LIT, false);
  setLed(LED_OPENS_GATE_WHEN_LIT, false);
  digitalWrite(SOL_FREE_BALL_GATE, 0);
  if (/*inPlay*/true) {

    inPlay = false;
    playerUpLights++;
    debugInt('M', playerUpLights);
    if (playerUpLights > canPlayLights) {
      playerUpLights = 1;
      ballInPlayLights++;
      debugInt('P', ballInPlayLights);
    }
    if (ballInPlayLights > 5) {
      ballInPlayLights = 0;
      gameOverLight = 1;
    }
    Serial.println("(95B)");
    operateSolenoidWithDelay(INDEX_SOL_BALL_RETURN_KICKER, 500);
    Serial.println("(95C)");
    sendBBDChanges();

      setTimer(0, delayedBallRelease, 1000);
  
  }
  
    operateSolenoidWithDelay(INDEX_SOL_BALL_RETURN_KICKER, 500);
  
}

void aLThumper() {
   Serial.println("[TL]");
  operateSolenoidWithDelay(INDEX_SOL_L_THUMPER, 500);
  addToScore(1);
}

void aRThumper() {
  Serial.println("[TE]");
  operateSolenoidWithDelay(INDEX_SOL_R_THUMPER, 500);
  addToScore(1);
}

void aCThumper() {
   Serial.println("[TC]");
  operateSolenoidWithDelay(INDEX_SOL_C_THUMPER, 500);
  addToScore(10);
}

void aBallInPlay() {
  isBeforeFirstBallPlayed = false;
  inPlay = true;
  debugInt("O", 0);
  setLed(LED_WHEN_LIT_SAME_PLAYER_SHOOTS_AGAIN, false);
}

void aFlipperL() {

  if (inPlay) {
    operateSolenoidWithDelay(INDEX_SOL_L_FLIPPER, FLIPPER_ON_TIME);
  }
}

void aFlipperR() {
  //=//+Serial.println("<92>");

  if (inPlay) {
    operateSolenoidWithDelay(INDEX_SOL_R_FLIPPER, FLIPPER_ON_TIME);
  }
}

void kickerCommon() {
  setLed(LED_WHEN_LIT_SAME_PLAYER_SHOOTS_AGAIN, true);
  operateSolenoidWithDelay(INDEX_SOL_FREE_BALL_GATE, 10000);
  operateSolenoidWithDelay(INDEX_SOL_BALL_RETURN_KICKER, 500);
}


void aTopKicker() {
  addToScore(200);
  kickerCommon();
}

void aBottomKicker() {
  addToScore(100);
  kickerCommon();
}

void aLChuteToDrain() {
  if (ledState[LED_WIGGLESVILLE_500]) {
    addToScore(500);
  } else {
    if (ledState[LED_WIGGLESVILLE_300]) {
      addToScore(300);
    } else {
      addToScore(100);
    }
  }
}

void aLSlingshot() {
  addToScore(10);
  operateSolenoidWithDelay(INDEX_SOL_L_SLINGSHOT, 500);

}

void aRSlingshot() {
  addToScore(10);
  operateSolenoidWithDelay(INDEX_SOL_R_SLINGSHOT, 500);
}

void aRMushroom() {
  operateSolenoidWithDelay(INDEX_SOL_ZIPPER_FLIPPER_RELEASE, 500);
  setLed(LED_OPENS_GATE_WHEN_LIT, true);
  addToScore(100);
  //operateSolenoidWithDelay(INDEX_SOL_FREE_BALL_GATE, 10000);
}

void aCMushroom() {
  if (ledState[LED_WHEN_LIT_FLIPS_OUT]) {
    operateSolenoidWithDelay(INDEX_SOL_ZIPPER_FLIPPER_ACTIVATE, 500);
    setLed(LED_WHEN_LIT_FLIPS_OUT, false);
  } else {
    operateSolenoidWithDelay(INDEX_SOL_ZIPPER_FLIPPER_ACTIVATE, 500);
    operateSolenoidWithDelay(INDEX_SOL_TOP_HOLE_POT_KICKER, 500);
    operateSolenoidWithDelay(INDEX_SOL_BOTTOM_HOLE_POT_KICKER, 500);
  }
}

void aOpensGateWhenLit() {
  if (ledState[LED_OPENS_GATE_WHEN_LIT]) {
    setLed(LED_FREE_BALL_GATE_OPEN_WHEN_LIT, true);
    digitalWrite(SOL_FREE_BALL_GATE, 1);
  }
}

void resetScores() {
  for (int i = 0; i < NO_OF_PLAYERS; i++) {
    writeScore(i, 0);
  }
}



void aStart() {
  if (isBeforeFirstBallPlayed) {
    debugInt('C', canPlayLights);
    if (canPlayLights < 4) {
      debugInt('D', canPlayLights);
      canPlayLights++;
      debugInt('d', canPlayLights);
    } else {
      state = STATE_IN_PLAY;
    }
    if (canPlayLights == 1) {
      int i;
      for (i = 0; i < TOTAL_NO_OF_SCORE_REELS; i++) {
        bBD[i] = 0;
        debugInt('G', i);
      }
      operateSolenoidWithDelay(INDEX_SOL_BALL_RELEASE, 500);
    }
    resetScores();
    debugInt('E', canPlayLights);
    ballInPlayLights = 1;
    gameOverLight = 0;
    playerUpLights = 1;
    setLed(LED_WIGGLE_ALLEY_WHEN_LIT_GATE_OPEN, true);
    digitalWrite(SOL_GATE_RELAY, 1);
  }
  sendBBD();
}

FuncP0 inputFuncPs[] = {

  &aBallInDrain,       //22  //0 //SW_DRAIN_KICKER y // if ball in play operates drrain kicker
  &a,                  //23  //1 //SW_ZIP_SOLENOID_CONTACT
  &aRSlingshot,        //24  //2  //SW_R_SLINGSHOT y // scores 10
  &a,                  //25  //3 //SW_IDLE_BALL_HIGH y
  &a,                  //26  //4 //SW_IDLE_BALL_LOW y // allows ball release
  &aLSlingshot,        //27  //5 //SW_L_SLINGSHOT y // scores 10 (???)
  &a,                  //28  //6
  &a,                  //29  //7
  &a10,                //30  //8 //SW_BOTTOM_R_BUMPER y // scores 10
  &aOpensGateWhenLit,  //31  //9 //SW_SENSOR_OPENS_GATE_WHEN_LIT
  &aRMushroom,         //32  //10 //SW_R_MUSHROOM   // open zip flippers, turns ON LED_FREE_BALL_GATE_OPEN_WHEN_LIT, scores 100
  &aCMushroom,         //33  //11 //SW_CENTRE_MUSHROOM y // close zip flippers then kick out balls and increment WSJB if balls in either saucer, if
  // if LED_WHEN_LIT_FLIPS_OUT opens zip flippers
  &a,                //34  //12
  &aBottomKicker,    //35  //13 //SW_BOTTOM_KICKER y // registers that a ball is in the bottom saucer, turns on LED_WHEN_LIT_FLIPS_OUT
  &aTopKicker,       //36  //14 //SW_TOP_KICKER y // registers that a ball is in the top saucer, turns on LED_WHEN_LIT_FLIPS_OUT
  &a,                //37  //15 //SW_L_POP_BUMPER_SOLENOID
  &aHit200,          //38  //16 //SW_TOP_R_BUMPER y // '200 HIT WHEN LIT TO LITE' on, scores 1
  &a,                //39  //17 //SW_R_POP_BUMPER_SOLENOID
  &aHit200,          //40  //18 //SE_TOP_L_BUMPER y // '200 HIT WHEN LIT TO LITE' on, scores 1
  &a,                //41  //19
  &aTopSideChutes,   //42  //20 //SW_R_TOP_CHUTE y, scores 10
  &aTopMiddleChute,  //43  //21 //SW_MIDDLE_CHUTE y // score 10 or 200 when 200 lit,
  &aWiggleA,         //44  //22 //SW_WIGGLE_A y // scores 100 if corresponding light on, otherwise scores 1
  &aWiggleB,         //45  //23 //SW_WIGGLE_B y // scores 100 if corresponding light on, otherwise scores 1
  &a10,              //46  //24 //SW_MIDDLE_L_BUMPER
  &aWiggleC,         //47  //25 //SW_WIGGLE_C y // scores 100 if corresponding light on, otherwise scores 1
  &aWiggleD,         //48  //26 //SW_WIGGLE_D y // scores 200 if corresponding light on, otherwise scores 1
  &a,                //49  //27
  // advances WIGGLE ALLEY adding score lights until all on, scores 100
  &a,               //50  //28
  &a10,             //A0  //54 //29 //SW_BOTTOM_L_BUMPER y // scores 10
  &aLChuteToDrain,  //A1  //55 //30  //SW_L_CHUTE_TO_DRAIN y // scores 100 or 300 or 500 depending on WIGGLESVILLE lights
  &a,               //A2  //56 //31 //SW_L_SLINGSHOT_SOLENOID_CONTACT
  &aLThumper,       //A3  //57 //32 //SW_L_THUMPER y // scores 1
  &aStart,          //A4  //58 //33  //BUTTON_START y
  &aFlipperL,       //A5  //59 //34  //BUTTON_L y
  &aFlipperR,       //A6  //60 //35  //BUTTON_R y
  &aBallInPlay,     //A7  //61 //36  //BALL_IN_PLAY
  &aLMushroom,      //A8  //62  //37    //SW_L_MUSHROOM y  // advances WIGGLESVILLE 100->300->500<- ,
  &a,               //A9  //63   //38   //SW_WIGGLE_E y //
  &aCThumper,       //A10  //64  //39 //SW_C_THUMPER  // scores 10
  &aRThumper,       //A11  //65  //40 //SW_R_THUMPER  //scores 1
  &a,               //A12  //66
  &a,               //A13  //67
  &a,               //A14  //68
  &a,               //A15  //69

};
//#endif

void debugInt(char flag, int v) {
  char debugChars[] = "000000000000";
  debugChars[0] = '<';
  debugChars[1] = flag;
  debugChars[2] = '>';
  debugChars[11] = '\0';
  sprintf(&debugChars[3], "%08i", v);
  Serial.println(debugChars);
}


char playerScoreChars[] = "ABCD";
void loadPlayerScore(int s) {
  sprintf(playerScoreChars, "%04i", s);
  debugInt('A', s);
}


void actionInputChanges(int index, int cpv) {
  Serial.println("<6>" + String(index) + "|" + String(cpv) + ">");
  int actionValue = 1;
  // if ((index == INDEX_SW_R_MUSHROOM) || (index == INDEX_SW_C_MUSHROOM) || (index == INDEX_SW_L_MUSHROOM)){
  //   actionValue = 0;
  // }
  if (cpv == actionValue) {
    //=//+Serial.println("<4A>" + String(index) + ">");
  } else {

    FuncP0 actionP = inputFuncPs[index];
    //debugInt('B', index);
    // score = index;

    // assembleSendScoreArray();
    //=//+Serial.println("<4B>" + String(index) + "#" + String(inputPins[index]) + "$" + String(cpv) + ">");
    actionP();
    ////=//+Serial.println("<4C>" + String(index) + ">");
  }
}


void scanInputs() {
  //  //=//+Serial.println("<3>" + String(digitalRead(22)));
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    int pin = inputPins[i];
    byte cpv = digitalRead(pin);
    ////+Serial.print(cpv);
    if (cpv != inputPinValues[i]) {
      unsigned long timeDiff = millis() - inputPinCounters[i];
      String timeDiffString = String(timeDiff);
      String stringPin = String(pin);
      String stringIndex = String(i);
      if (timeDiff < BOUNCE_TIME) {
       // Serial.println("<17>" + timeDiffString + "~" + stringIndex + "@" + stringPin);
      } else {
        inputPinCounters[i] = millis();
        Serial.println("<18A>" + timeDiffString + "~" + stringIndex + "@" + stringPin);
        actionInputChanges(i, cpv);
        Serial.println("<18B>" + timeDiffString + "~" + stringIndex + "@" + stringPin);
      }
    }

    inputPinValues[i] = cpv;
  }
  ////=//+Serial.println("<1>");
}

void driveOutputs() {
  // //=//+Serial.println("<30>" + String(solenoidCounters[0]));
  for (int i = 0; i < SOLENOID_LENGTH; i++) {
    int j = solenoidPins[i];
    if (solenoidCounters[i] != 0) {
      //+Serial.print("<331>");
      //+Serial.print(i);
      //+Serial.print("!");
      //+Serial.print(j);
      //+Serial.print("?");
      //=//+Serial.println(solenoidCounters[i]);
      if (solenoidCounters[i] > millis()) {
        digitalWrite(j, 1);
        //=//+Serial.println("<340>" + String(solenoidCounters[i]) + "+" + String(millis()));
      } else {
        solenoidCounters[i] = 0;
        digitalWrite(j, 0);
        //=//+Serial.println("<341>" + String(solenoidCounters[i]) + "+" + String(millis()));
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
    //=//+Serial.println("<110>" + String(j));
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
  //=//+Serial.println("<52>" + String(solenoidNumber) + "*" + String(millis()) + "?" + String(solenoidCounters[solenoidNumber]));
}


void operateLedWithDelay(int ledN, int delay) {
  ledCounters[ledN] = delay;
  ////=//+Serial.println(ledCounters[ledN]);
}



void turnOnStaticLEDS() {
  setLed(LED_R_PLASTIC_BOTTOM, true);
  setLed(LED_R_PLASTIC_MIDDLE_BOTTOM, true);
  setLed(LED_R_PLASTIC_MIDDLE_TOP, true);
  setLed(LED_R_PLASTIC_TOP, true);
  setLed(LED_FAR_R_CHANNEL_BARRIER, true);
  setLed(LED_MIDDLE_R_CHANNEL_BARRIER, true);
  setLed(LED_MIDDLE_L_CHANNEL_BARRIER, true);
  setLed(LED_FAR_L_CHANNEL_BARRIER, true);
  setLed(LED_L_PLASTIC_TOP, true);
  setLed(LED_WIGGLE_ALLEY_PLASTIC_TOP, true);
  setLed(LED_WIGGLE_ALLEY_PLASTIC_FAR_LEFT_TOP, true);
  setLed(LED_WIGGLE_ALLEY_PLASTIC_R, true);
  setLed(LED_WIGGLE_ALLEY_PLASTIC_FAR_LEFT_BOTTOM, true);
}


/*
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
  //  //=//+Serial.println("<61>" + String(sweepCounter));
  if (sweepCounter > maxCoord) {
    sweepCounter = 0;
    isVerticalSweep = !isVerticalSweep;
  }
}
*/

void setup() {
  state = STATE_ON;
  counter = millis();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  //=//+Serial.println("<300>" + String(NO_OF_INPUT_PINS));
  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // noOfInputPins = sizeof(inputPins) / sizeof(int);
  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
    //+Serial.print(String(inputPins[i]) + ",");
    inputPinValues[i] = 0;
    //  if ((i == INDEX_SW_R_MUSHROOM) || (i == INDEX_SW_C_MUSHROOM) || (i == INDEX_SW_L_MUSHROOM)){
    //    inputPinValues[i] = 1;
    //  }
  }
  //=//+Serial.println("<302>" + String(NO_OF_INPUT_PINS));
  setupSolenoids();

  strip.setBrightness(250);  // Set BRIGHTNESS to about 1/5 (max = 255)
  // digitalWrite(solenoidPins[0], 1);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, off);
    ledCounters[i] = -1;
  }
  // strip.setPixelColor(0, blue);
  // strip.setPixelColor(1, white);
  for (int i = 0; i < LENGTH_OF_BBD; i++) {
    lastBBD[i] = 9999;
  }
  isBeforeFirstBallPlayed = true;
  playerUpLights = 0;
  canPlayLights = 0;
  gameOverLight = 1;
  sendBBD();
  turnOnStaticLEDS();
  strip.show();
  delay(1000);
  int i;
  for (i = 0; i > 3; i++) {
    delayCounters[i] = 0;
  }
}

unsigned long oldMilli = 0;
int c = 0;
 unsigned long fc =  millis();
 bool green_color = true;
void loop() {
  ////+Serial.println("<<<<<<>>>>>>" + String(millis() - oldMilli) );
  oldMilli = millis();
  scanInputs();
  // //=//+Serial.println("<401>");
  driveOutputs();
  checkTimers();
  // //=//+Serial.println("<402>");
  // analogWrite(RELAY, 32);
  //  digitalWrite(RELAY, 1);
  for (int i = 0; i < (LED_COUNT); i++) {
    if (ledCounters[i] > 0) {
      ledCounters[i]--;
     
    }

    if (ledCounters[i] > 0) {
      strip.setPixelColor(i, white);
      // //=//+Serial.println("<7A>" + String(i) + "|" + String(ledCounters[i]) + ">");
    } else {
      if (ledCounters[i] == 0) {
        strip.setPixelColor(i, off);
        // //=//+Serial.println("<7B>" + String(i) + "|" + String(ledCounters[i]) + ">");
        ledCounters[i] = -1;
      }
    }
    // if (green_color){
    //  strip.setPixelColor(i, green);
    // } else {
    //  strip.setPixelColor(i, blue);

    // }
  /*  if (millis() - fc > 5000){
      green_color = ! green_color;
      fc = millis();
      //sendDigit(1,c);
      Serial1.print(String(c));
      Serial.println("<80>" + String(c));
      c++;
      if(c > 9)c = 0;
      //  for (int i = 0; i < NO_OF_INPUT_PINS; i++) {
    // pinMode(inputPins[i], INPUT_PULLUP);
      //  }
    }
*/
  }
  // //=//+Serial.println("<403>");
  if (blinkToken == 0) {
    blinkToken = 20;
    strip.setPixelColor(6, red);
    // //=//+Serial.println("<8A>" + String(blinkToken));
  } else {
    blinkToken--;
    strip.setPixelColor(6, off);
    // //=//+Serial.println("<8B>" + String(blinkToken));
  }
  //if (!inPlay) {
  //  sweepDisplay();
  //}
  // xx++;
  // if(xx > 9){
  //   xx = 0;
  // }
  // Serial1.println('A' + String(xx));



  if (Serial.available() > 0) {
    String s = Serial.readString();
    Serial.println("<£>" + s);
    switch (s[0]) {
      case 's':
        aStart();
        break;
      case 'b':
        aBallInPlay();
        break;
      case 't':
        a10();
        break;
      case 'd':
        aBallInDrain();
        break;
      case 'r':
        aRMushroom();
        break;
      case 'l':
        aLMushroom();
        break;
      case 'c':
        aCMushroom();
        break;
      case 'w':
        aWiggleA();
        break;





      default:
        break;
    }
  }


  /* if (Serial1.available()) {
        int inByte = Serial1.read();
        Serial.println(inByte);
        if(inByte == 'Z'){
          aStart();
        }
      }
*/
  recvWithEndMarker();
  showNewData();
  strip.show();
}


const byte numChars = 32;
char receivedChars[numChars];  // an array to store the received data

boolean newData = false;

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '+';
  char rc;

  while (Serial1.available() > 0 && newData == false) {
    rc = Serial1.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("<#>");
    Serial.println(receivedChars);
    newData = false;
    for (int i = 0; i < numChars; i++) {
      if (receivedChars[i] == 'Z') {
        receivedChars[i] = ' ';
        aStart();
        break;
      }if (receivedChars[i] == 'Y') {
        receivedChars[i] = ' ';
        isBeforeFirstBallPlayed = true;
        break;
      }
      receivedChars[i] = ' ';
    }
  }
}

void sendDigit(int index, int newValue) {
  if ((index >= 0) && (index < LENGTH_OF_BBD) && (newValue >= 0) && (newValue <= 9)) {
    char indexChar = (char)(index + (int)'A');
    Serial1.println(indexChar + String(newValue) + "+");
    Serial.println("[X]" + String(indexChar) + "*" + String(newValue) + "+");
    //Serial.print(indexChar + String(newValue));
  }
}

void sendBBDChanges() {
  int i;
  //+Serial.println("<600>" + String(0));
  for (i = 0; i < LENGTH_OF_BBD; i++) {
    if (bBD[i] != lastBBD[i]) {
      sendDigit(i, bBD[i]);
      lastBBD[i] = bBD[i];
      Serial.println("[H]" + String(bBD[i]));
    }
  }
}

void sendBBD() {
  int i;
  //=//+Serial.println("<601A>" + String(bBD[16]));
  for (i = 0; i < LENGTH_OF_BBD; i++) {
    sendDigit(i, bBD[i]);
    lastBBD[i] = bBD[i];
    //debugInt('I', i);
  }
}

const int indexes[4][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 } };

int readScore(int player) {
  int score = 0;
  if ((player >= 1) && (player <= 4)) {
    score = bBD[indexes[player - 1][3]] * 1000;
    score = score + bBD[indexes[player - 1][2]] * 100;
    score = score + bBD[indexes[player - 1][1]] * 10;
    score = score + bBD[indexes[player - 1][0]];
  }
  return score;
}

void writeScore(int player, int score) {
  ////=//+Serial.println("(505)" + String(player) + "$" + String(score));
  if ((player >= 1) && (player <= 4)) {
    int playerIndex = (player - 1) * 4;
    int i;
    int s = score;
    int multiplyer = 10;
    ////=//+Serial.println("(506)" + String(playerIndex) + "$" + String(s));
    for (i = 0; i < 4; i++) {
      int rem = s % multiplyer;
      bBD[playerIndex + i] = (rem * 10) / multiplyer;
      s = s - rem;
      multiplyer = multiplyer * 10;
      ////=//+Serial.println("(507)" + String(rem) + "$" + String(s) + "~" + String(playerIndex + 3 - i));
    }
  }
}

void addToScore(int add) {
  if (!gameOverLight) {
    int s = readScore(playerUpLights);
    ////=//+Serial.println("(503)" + String(s) + "$" + String(s) + "%" + String(playerUpLights));
    s = s + add;
    writeScore(playerUpLights, s);
    ////=//+Serial.println("(504)" + String(s) + "$" + String(s));
    sendBBDChanges();
  }
}



void checkTimers() {
  ////=//+Serial.println("(595)");
  int i;
  for (i = 0; i < 3; i++) {
    if (delayCounters[i] != 0) {
      //=//+Serial.println("(596)");
      if (delayCounters[i] < millis()) {
        delayCounters[i] = 0;
        //=//+Serial.println("(597)");
        delayCallbacks[i]();
      }
    }
  }
}

void setTimer(int timerNo, func_type func, unsigned long millsec) {
  delayCounters[timerNo] = millsec + millis();
  delayCallbacks[timerNo] = func;
  //=//+Serial.println("(598)" + String(delayCounters[0]) + "$" );
  // //=//+Serial.println(delayCallbacks[0]);
}

#endif
/* ToDo
-Right thumper not working
-Zipper release not working
-Right slighshot oscillates
-Remote control to set number of player
Score not resetting on new game
Power on load display
Reset button
Ball feed on ball capture
Ball in play count not always working
Both yellow mushromws not working
When ball goes in hole new ball in not laumched
- Thumper lights not working
*/
