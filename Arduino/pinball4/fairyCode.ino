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

