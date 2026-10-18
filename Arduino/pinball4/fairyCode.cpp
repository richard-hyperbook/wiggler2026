#include "fairyData.h"

bool inPlay = true;
// long score = 0;
long lastScore = 0;
int bonus = 0;
int advance = 0;
int ballNumber = 0;


//Visual Pinball variables
bool gameOn = false;
long score = 0;
int eBCount = 0;
int ball = 0;
bool ballUp = false;


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


// int xcount = 0;







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

