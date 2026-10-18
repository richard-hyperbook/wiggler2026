/*
//#include <String.h>
#include <Arduino.h>
// #include "pinballData.h"


///declarando las variables ;
int hiScore;
int GameOn;
int Players;
int Upball;
int ball;
int PL[1];

int scoreVP[2];
int TempscoreVP[2];
int Credit;
int Credit1[2];
int Credit2[2];
int Credit3[2];
int Tilted;
int Tilts;
int Up;
int x;
int bb;
int bonusVP;
int bonusVPX;

int eBcount;

bool endball;
bool ballUp;
int currTen;
int currHun;
int currTho;
int extra;

// upLight[1] = Up1 ;
/* ;
// Set bonusVPLamp(1) = Light1 ;
// Set bonusVPLamp(2) = Light2 ;
// Set bonusVPLamp(3) = Light3 ;
// Set bonusVPLamp(4) = Light4 ;
// Set bonusVPLamp(5) = Light5 ;
// Set bonusVPLamp(6) = Light6 ;
// Set bonusVPLamp(7) = Light7 ;
// Set bonusVPLamp(8) = Light8 ;
// Set bonusVPLamp(9) = Light9 ;
// Set bonusVPLamp(10) = Light10 ;
// Set bonusVPLamp(11) = Light11 ;
// Set bonusVPLamp(12) = Light12 ;
// Set bonusVPLamp(13) = Light13 ;
// Set bonusVPLamp(14) = Light14 ;
// Set bonusVPLamp(15) = Light15 ;
// Set bonusVPLamp(16) = Light16 ;
// Set bonusVPLamp(17) = Light17 ;
// Set bonusVPLamp(18) = Light18 ;
// Set bonusVPLamp(19) = Light19 ;
// Set bonusVPLamp(20) = Light20 ;

///iniciando ;

#define ByVal char
#define LightStateOff 0
#define LightStateOn 1
#define true true
#define false false
#define LeftFlipperKey 0
#define RightFlipperKey 1
#define LeftTiltKey 2
#define RightTiltKey 3
#define CenterTiltKey 4
#define plungerKey 5


class Light {
public:
  char state;
  int index;
};
Light bonusVPLamp[20];

Light light1;
Light light2;
Light light3;
Light light4;
Light light5;
Light light6;
Light light7;
Light light8;
Light light9;
Light _LED_BONUS10.;
Light light11;
Light light12;
Light light13;
Light light14;
Light light15;
Light light16;
Light light17;
Light light18;
Light light19;
Light light20;

Light light21;
Light light22;
Light light23;
Light light24;
Light light25;
Light light26;
Light light27;
Light light28;
Light light29;
Light _LED_SPECIAL_WHEN_LIT;
Light _LED_50000_POINTS_TOP;
Light _LED_BUTTON_1000_POINTS_LEFT;
Light light33;
Light light34;

void connectLights() {
  //  _LED_BONUS1.index =  ;
  //  _LED_BONUS2.index =  ;
  //  _LED_BONUS3.index =  ;
  //  _LED_BONUS4.index =  ;
  //  _LED_BONUS5.index =  ;
  //  _LED_BONUS6.index =  ;
  //  _LED_BONUS7.index =  ;
  //  light8.index =  ;
  //  _LED_BONUS9.index =  ;
  //  _LED_BONUS10..index =  ;
  //  _LED_SWING1.index =  ;
  //  _LED_SWING2.index =  ;
  //  light13.index =  ;
  //  _LED_SWING4.index =  ;
  //  _LED_SWING5.index =  ;
  //  _LED_SWING6.index =  ;
  //  _LED_SWING7.index =  ;
  //  _LED_SWING8.index =  ;
  //  _LED_SWING9.index =  ;
  //  _LED_SWING10.index =  ;
  //  light21.index =  ;
  //  light22.index =  ;
  //  light23.index =  ;
  //  light24.index =  ;
  //  light25.index =  ;
  //  light26.index =  ;
  //  light27.index =  ;
  //  light28.index =  ;
  //  light29.index =  ;
  _LED_SPECIAL_WHEN_LIT.index = 2;
  _LED_50000_POINTS_TOP.index = 0;
  //  _LED_BUTTON_1000_POINTS_LEFT.index = 46;
  //  light33.index =  ;
  //  light34.index =  ;
}


Light upLight[1];
Light sacabola;  ///shoot again
Light dbonusVPlight;

class Flipper {
public:
  void RotateToStart(){};
  void RotateToEnd(){};
};
Flipper LeftFlipper;
Flipper RightFlipper;

class Kicker {
public:
  bool timerenabled;
  int timerInterval;
  void kick(int a, int b){};
  void destroyball() {
    ;
  }
};
Kicker kicker1;
Kicker kicker2;
Kicker kicker3;
Kicker kicker4;

class Bumper {
public:
  int state;
  int force;
};
Bumper bumper1;

class eMReel {
public:
  void resetToZero(){};
  void addValue(int value){};
  void setValue(int value) {}
};
eMReel eMReel1;
eMReel eMReel2;
eMReel eMReel3;
eMReel eMReel4;
eMReel eMReel5;

class Timer {
public:
  bool enabled;
  int interval;
};
Timer bonusVPHoleTimer;
Timer playerDelayTimer;
Timer tiltTimer;
Timer resetTimer;
Timer ballReleaseTimer;
Timer bonusVPTimer;

class Hole {
public:
  void destroyball() {}
};
Hole bonusVPHole;
Hole drain;

class TextBox {
public:
  String Text;
};
TextBox textBoxGO;
TextBox TiltTextBox;
TextBox CredBox;
TextBox TiltBox;

class Control {
public:
  void pullBack() {}
  void Fire() {}
};
Control plunger;

void playSound(String name) {}
void nudge(int a, int) {}



// init ;
void initVP() {
  scoreVP[1] = 0;
  Up = 1;
  textBoxGO.Text = "fin de partida";
}

///partida extra ;
void awardSpecial() {
  playSound("Knocke");
  Credit = Credit + 1;
  CredBox.Text = Credit;
  ;
}

///partidas extras al superar los handicaps de puntuación ;

void displayScore() {
  if ((scoreVP[Up] >= 100000) && (Credit1[Up] == false)) {
    awardSpecial();
    Credit1[Up] = true;
  }
  if ((scoreVP[Up] >= 150000) && (Credit2[Up] == false)) {
    awardSpecial();
    Credit2[Up] = true;
  }
  if ((scoreVP[Up] >= 200000) && (Credit3[Up] == false)) {
    awardSpecial();
    Credit3[Up] = true;
  };
}


void addReel(int Pts) {
  //  Select Case Up ;
  //  Case 1 ;
  eMReel1.addValue(Pts);
  //  End Select   ;
  ;
}


void tiltCheck() {
  if (Tilted == false) {
    if (Tilts == 0) {
      Tilts = Tilts + random(100);
      tiltTimer.enabled = true;
    } else {
      ;
      Tilts = Tilts + random(100);
    };
    if ((Tilts >= 225) && (Tilted == false)) {
      LeftFlipper.RotateToStart();
      RightFlipper.RotateToStart();
      Tilted = true;
      tiltTimer.enabled = false;
      TiltBox.Text = "falta";
      playSound("ROBuzz");
      GameOn = true;
      endball = true;
    };
  }
}


void addScore(int val) {
  if (Tilted == false) {
    scoreVP[Up] = scoreVP[Up] + val;
    displayScore;
    addReel(val);
  };
}


void startGame() {
  Players = 1;
  bb = 0;  ///estado de la bola
  Up = 1;
  upLight[1].state = 1;
  Credit = Credit - 1;
  CredBox.Text = Credit;
  playSound("inicio");
  Tilted = false;
  Tilts = 0;
  TiltBox.Text = "";
  textBoxGO.Text = "";
  GameOn = true;
  for (int x = 1; x <= 10; x++) {
  }
  for (int x = 1; x <= 2; x++) {
    scoreVP[x] = 0;
    Credit1[x] = false;
    Credit2[x] = false;
  }
  _LED_SWING7.state = 1;
  bumper1.state = 0;
  eMReel1.resetToZero();
  eMReel3.resetToZero();
  eMReel3.resetToZero();  //(1)???
  resetTimer.enabled = true;
  eBcount = 0;
  ball = 1;
}

void gameOver() {
  LeftFlipper.RotateToStart();
  RightFlipper.RotateToStart();
  playSound("fx_ballrel");
  textBoxGO.Text = "fin de partida";
  _LED_SWING1.state = 0;
  _LED_SWING2.state = 0;
  light27.state = 0;
  for (int X = 1; X <= Players; X++) {
    if (scoreVP[x] > hiScore) {
      hiScore = scoreVP[X];
      awardSpecial();
    }
  }
  Players = 0;
  ;
}

///funciones del teclado, flippers, plunger, echar moneda y todo eso ;

void Table1_KeyDown(ByVal keycode) {

  if (keycode == plungerKey) {
    plunger.pullBack();
  }

  if (keycode == LeftFlipperKey) {
    if (GameOn == true) {
      if (Tilted == false) {
        LeftFlipper.RotateToEnd();
        playSound("Flipper");
      }
    }
  };
  if (keycode == RightFlipperKey) {
    if (GameOn == true) {
      if (Tilted == false) {
        RightFlipper.RotateToEnd();
        playSound("Flipper");
      }
    }
  };
  if (keycode == LeftTiltKey) {
    nudge(90, 2);
    tiltCheck();
  };
  if (keycode == RightTiltKey) {
    nudge(270, 2);
    tiltCheck();
  };

  ;
  if (keycode == LeftTiltKey) {
    nudge(90, 2);
    tiltCheck();
  };
  if (keycode == RightTiltKey) {
    nudge(270, 2);
    tiltCheck();
  }


  if (keycode == CenterTiltKey) {
    nudge(0, 2);
    tiltCheck();
  }

  if (keycode == 6) {
    ;
    if (Credit < 9) {
      Credit = Credit + 1;
      ;
      playSound("coin3");
    }
    CredBox.Text = Credit;
    ;
  };
  if (keycode == 2) {
    if (Credit > 0) {
      if ((GameOn = false) && (Players == 0)) {
        startGame();
        return;
      };
      if ((Players < 1) && (scoreVP[1] == 0)) {
        Players = Players + 1;
        Credit = Credit - 1;
        CredBox.Text = Credit;
      }
    };
  };
}

void Table1_KeyUp(ByVal keycode) {

  if (keycode == plungerKey) {
    plunger.Fire();
    playSound("plunger");
  };
  if (keycode == LeftFlipperKey) {
    if (GameOn == true) {
      LeftFlipper.RotateToStart();
    }
  };
  if (keycode == RightFlipperKey) {
    if (GameOn == true) {
      RightFlipper.RotateToStart();
    }
  }

  ;
}

///el tilt la falta ;


void tiltTimer_Timer() {
  if (Tilts > 0) {
    Tilts = Tilts - 1;
  } else {
    tiltTimer.enabled = false;
  }
}

///iniciando el juego, las variables, los rodillos y todo lo demas ;



void resetTimer_Timer() {
  resetTimer.enabled = false;
  ball = 1;
  currTho = 0;
  currHun = 0;
  currTen = 0;
  ballReleaseTimer.enabled = true;
}

void ballReleaseTimer_Timer() {
  ballReleaseTimer.enabled = false;
  //  kicker4.createball.image="Webball" ;
  kicker4.kick(90, 2);
  ballUp = true;
  sacabola.state = 1;
}

void kicker3_hit() {
  kicker3.destroyball();
}

void gate1_hit() {
  playSound("Gate5");
}


///el asunto de los bonusVP ;

void lightbonusVP() {
  for (int X = 1; X <= 20; X++) {
    bonusVPLamp[x].state = LightStateOff;
  }
  if ((bonusVP > 0) && (bonusVP < 21)) {
    bonusVPLamp[bonusVP].state = LightStateOn;
  }
  if (bonusVP == 20) {
    bonusVPLamp[20].state = LightStateOn;
  }
}


void bonusVPHole_Hit() {
  bonusVPHole.destroyball();
  bonusVPHoleTimer.enabled = true;
  bonusVPHoleTimer.interval = 1400;
}


void bonusVPCount() {
  if (bonusVP < 20) {
    bonusVPTimer.enabled = true;
    bonusVPTimer.interval = 200;
  }
}

///los bonos depende del estado de las luces ;

void bonusVPTimer_timer() {
  if (bonusVP > 0) {
    playSound("_bell10");
    for (int x = 1; x <= bonusVPX; x++) {
    }
    bonusVP = bonusVP - 1;
    lightbonusVP;
    if (dbonusVPlight.state == 1) {
      ;
      addScore(3000);
      playSound("bing3");
    }
    if (dbonusVPlight.state == 1) {
      ;
      addScore(2000);
      playSound("bing3");
    }
    if (dbonusVPlight.state == 0) {
      addScore(1000);
      playSound("jet4");
    }
  } else {
    bonusVPTimer.enabled = false;
  }
}

///el asunto del drain de cuando comienza una nueva bola iniciando todo ;

void drain_Hit() {
  ballUp = false;
  drain.destroyball();
  playSound("drain");
  bb = 0;
  Tilts = 0;
  TiltBox.Text = "";
  playerDelayTimer.enabled = true;
  dbonusVPlight.state = 0;
  bumper1.state = 0;
  ///luces del bono ;
  _LED_BONUS1.state = 0;
  _LED_BONUS2.state = 0;
  _LED_BONUS3.state = 0;
  _LED_BONUS4.state = 0;
  _LED_BONUS5.state = 0;
  _LED_BONUS6.state = 0;
  _LED_BONUS7.state = 0;
  light8.state = 0;
  _LED_BONUS9.state = 0;
  _LED_BONUS10..state = 0;
  ///doble bono ;
  _LED_SWING1.state = 0;
  _LED_SWING2.state = 0;
  light13.state = 0;
  _LED_SWING4.state = 0;
  _LED_SWING5.state = 0;
  _LED_SWING6.state = 0;
  _LED_SWING7.state = 0;
  _LED_SWING8.state = 0;
  _LED_SWING9.state = 0;
  _LED_SWING10.state = 0;
  light21.state = 0;  ///luz que avisa el comienzo del doble bono ;

  ///dianas naranjas ;
  light22.state = 0;  ///A ;
  light23.state = 0;  ///B ;
  light24.state = 0;  ///C ;
  light25.state = 0;  ///D ;

  light26.state = 0;   ///50000 con luz ;
  light27.state = 1;   ///apaga bumper ;
  sacabola.state = 0;  ///shoot again  ;
  ;
  ///coladeros ;
  light28.state = 0;
  light29.state = 0;

  ///luz del hoyo especial ;
  _LED_SPECIAL_WHEN_LIT.state = 0;
  ///luz verde de arriba ;
  _LED_50000_POINTS_TOP.state = 0;

  ///luces de las mediocircunferencias ;
  _LED_BUTTON_1000_POINTS_LEFT.state = 0;
  light33.state = 0;
  light34.state = 0;  ///luz del activa bumper ;
}

void bonusVPHoleTimer_Timer() {
  bonusVPHoleTimer.enabled = false;
  if (Tilted == false) {
    bonusVPCount();
  }
  drain_Hit();
}

void addbonusVP() {
  bonusVP = bonusVP + 1;
  if ((_LED_BONUS1.state = 0) && (bonusVP == 1)) {
    _LED_BONUS1.state = 1;

    return;
  }
  if ((_LED_BONUS1.state = 1) && (bonusVP == 2)) {
    _LED_BONUS2.state = 1;
    return;
  }
  if ((_LED_BONUS2.state = 1) && (bonusVP == 3)) {
    _LED_BONUS3.state = 1;
    return;
  }
  if ((_LED_BONUS3.state = 1) && (bonusVP == 4)) {
    _LED_BONUS4.state = 1;
    return;
  }
  if ((_LED_BONUS4.state = 1) && (bonusVP == 5)) {
    ;
    _LED_BONUS5.state = 1;
    return;
  }
  if ((_LED_BONUS5.state = 1) && (bonusVP == 6)) {
    _LED_BONUS6.state = 1;
    return;
  }
  if ((_LED_BONUS6.state = 1) && (bonusVP == 7)) {
    _LED_BONUS7.state = 1;
    return;
  }
  if ((_LED_BONUS7.state = 1) && (bonusVP == 8)) {
    light8.state = 1;
    light29.state = 1;
    return;
  }
  if ((light8.state = 1) && (bonusVP == 9)) {
    _LED_BONUS9.state = 1;
    light28.state = 1;
    return;
  }
  if ((_LED_BONUS9.state = 1) && (bonusVP == 10)) {
    _LED_BONUS10..state = 1;
    _LED_SPECIAL_WHEN_LIT.state = 1;
    return;
  }
  ///doble bonos ;
  if ((_LED_BONUS10..state = 1) && (bonusVP == 11)) {
    _LED_SWING1.state = 1;
    light21.state = 2;
    light26.state = 1;
    return;
  }
  if ((_LED_SWING1.state = 1) && (bonusVP == 12)) {
    _LED_SWING2.state = 1;
    return;
  }
  if ((_LED_SWING2.state = 1) && (bonusVP == 13)) {
    light13.state = 1;
    return;
  }
  if ((light13.state = 1) && (bonusVP == 14)) {
    _LED_SWING4.state = 1;
    return;
  }
  if ((_LED_SWING4.state = 1) && (bonusVP == 15)) {
    ;
    _LED_SWING5.state = 1;
    return;
  }
  if ((_LED_SWING5.state = 1) && (bonusVP == 16)) {
    _LED_SWING6.state = 1;
    return;
  }
  if ((_LED_SWING6.state = 1) && (bonusVP == 17)) {
    _LED_SWING7.state = 1;
    return;
  }
  if ((_LED_SWING7.state = 1) && (bonusVP == 18)) {
    _LED_SWING8.state = 1;
    return;
  }
  if ((_LED_SWING8.state = 1) && (bonusVP == 19)) {
    _LED_SWING9.state = 1;
    return;
  }
  if ((_LED_SWING9.state = 1) && (bonusVP == 20)) {
    _LED_SWING10.state = 1;
    return;
  }
};




void playerDelayTimer_Timer() {
  Tilted = false;
  Tilts = 0;
  TiltBox.Text = "";
  playerDelayTimer.enabled = false;
  upLight[Up].state = LightStateOff;
  if (extra == 0) {
    Up = Up + 1;
    if (Up > Players) {
      ball = ball + 1;
      Up = 1;
    };
  }
  extra = extra - 1;
  if (ball > 5) {
    GameOn = false;
    gameOver();
  } else {
    eMReel3.setValue(ball);
    ballReleaseTimer.enabled = true;
  }
}


///Triggers ;
///Lo que hace accionar la bola ;
void trigger1_hit() {
  bb = 1;
  playSound("ballin");
}

void trigger2_hit() {
  if (_LED_BUTTON_1000_POINTS_LEFT.state == 0) {
    _LED_BUTTON_1000_POINTS_LEFT.state = 1;
    playSound("score500");
    addScore(500);
    return;
  }
  if (_LED_BUTTON_1000_POINTS_LEFT.state == 1) {
    _LED_BUTTON_1000_POINTS_LEFT.state = 2;
    light34.state = 2;
    bumper1.state = 1;
    light27.state = 0;
    playSound("score500");
    addScore(500);
    return;
  }
  if (_LED_BUTTON_1000_POINTS_LEFT.state == 2) {
    _LED_BUTTON_1000_POINTS_LEFT.state = 1;
    bumper1.state = 0;
    light34.state = 0;
    light27.state = 1;
    playSound("score500");
    addScore(500);
    return;
  }
}
void trigger3_hit() {
  if (light33.state == 0) {
    light33.state = 1;
    _LED_BUTTON_1000_POINTS_LEFT.state = 0;
    light34.state = 0;
    playSound("score500");
    addScore(500);
    return;
  }
  if (light33.state == 1) {
    playSound("score500");
    light33.state = 2;
    light34.state = 2;
    bumper1.state = 1;
    light27.state = 0;
    addScore(500);
    return;
  }
  if (light33.state == 2) {
    light33.state = 1;
    playSound("score500");
    addScore(500);
    return;
  }
}
void trigger4_hit() {
  if (sacabola.state == 1) {
    sacabola.state = 0;
  }
}

void trigger5_hit() {
  addScore(500);
  playSound("Score500");
}

void trigger6_hit() {
  if (light28.state == 1) {
    addScore(500);
    playSound("Knocke");
    Credit = Credit + 1;
    CredBox.Text = Credit;
  };
}
void trigger7_hit() {
  if (light29.state == 1) {
    addScore(500);
    playSound("Knocke");
    Credit = Credit + 1;
    CredBox.Text = Credit;
  };
}

///Diana ;

void Wall10_hit() {
  if (_LED_SPECIAL_WHEN_LIT.state == 1) {
    playSound("Knocke");
    Credit = Credit + 1;
    CredBox.Text = Credit;
    addScore(10000);
    _LED_SPECIAL_WHEN_LIT.state = 0;
  } else {
    playSound("ROBuzz");
    addScore(100);
  }
}

void Wall11_hit() { // top blue target 'on bumper'
  if (_LED_SPECIAL_WHEN_LIT.state == 1) {
    playSound("Knocke");
    Credit = Credit + 1;
    CredBox.Text = Credit;
    addScore(10000);
    _LED_SPECIAL_WHEN_LIT.state = 0;
  } else {
    playSound("ROBuzz");
    addScore(100);
  }
}

void wall16_hit() {
  light22.state = 1;
  addScore(100);
  if (_LED_BONUS1.state == 0) {
    _LED_BONUS1.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS1.state == 1) {
    _LED_BONUS2.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS2.state == 1) {
    _LED_BONUS3.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS3.state == 1) {
    _LED_BONUS4.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS4.state == 1) {
    ;
    _LED_BONUS5.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS5.state == 1) {
    _LED_BONUS6.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS6.state == 1) {
    _LED_BONUS7.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS7.state == 1) {
    light8.state = 1;
    light29.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (light8.state == 1) {
    _LED_BONUS9.state = 1;
    light28.state = 1;
    playSound("Score10");
    addScore(1000);
    addbonusVP();
    return;
  }
  if (_LED_BONUS9.state == 1) {
    _LED_BONUS10..state = 1;
    _LED_SPECIAL_WHEN_LIT.state = 1;
    playSound("Score3000");
    addScore(1000);
    addbonusVP();
    return;
  }

  ///doble bonos ;
  if (_LED_BONUS10..state == 1) {
    _LED_SWING1.state = 1;
    light21.state = 2;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING1.state == 1) {
    _LED_SWING2.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING2.state == 1) {
    light13.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (light13.state == 1) {
    _LED_SWING4.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING4.state == 1) {
    ;
    _LED_SWING5.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING5.state == 1) {
    _LED_SWING6.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING6.state == 1) {
    _LED_SWING7.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING7.state == 1) {
    _LED_SWING8.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING8.state == 1) {
    _LED_SWING9.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING9.state == 1) {
    _LED_SWING10.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
}


void wall17_hit() {
  light23.state = 1;
  addScore(100);
  if (_LED_BONUS1.state == 0) {
    _LED_BONUS1.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS1.state == 1) {
    _LED_BONUS2.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS2.state == 1) {
    _LED_BONUS3.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS3.state == 1) {
    _LED_BONUS4.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS4.state == 1) {
    ;
    _LED_BONUS5.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS5.state == 1) {
    _LED_BONUS6.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS6.state == 1) {
    _LED_BONUS7.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS7.state == 1) {
    light8.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (light8.state == 1) {
    _LED_BONUS9.state = 1;
    playSound("Score10");
    addScore(1000);
    addbonusVP();
    return;
  }
  if (_LED_BONUS9.state == 1) {
    _LED_BONUS10..state = 1;
    _LED_SPECIAL_WHEN_LIT.state = 1;
    playSound("Score3000");
    addScore(1000);
    addbonusVP();
    return;
  }

  ///doble bonos ;
  if (_LED_BONUS10..state == 1) {
    _LED_SWING1.state = 1;
    light21.state = 2;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING1.state == 1) {
    _LED_SWING2.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING2.state == 1) {
    light13.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (light13.state == 1) {
    _LED_SWING4.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING4.state == 1) {
    ;
    _LED_SWING5.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING5.state == 1) {
    _LED_SWING6.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING6.state == 1) {
    _LED_SWING7.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING7.state == 1) {
    _LED_SWING8.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING8.state == 1) {
    _LED_SWING9.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING9.state == 1) {
    _LED_SWING10.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
}

void wall18_hit() {
  addScore(100);
  light24.state = 1;
  if (_LED_BONUS1.state == 0) {
    _LED_BONUS1.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS1.state == 1) {
    _LED_BONUS2.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS2.state == 1) {
    _LED_BONUS3.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS3.state == 1) {
    _LED_BONUS4.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS4.state == 1) {
    ;
    _LED_BONUS5.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS5.state == 1) {
    _LED_BONUS6.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS6.state == 1) {
    _LED_BONUS7.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS7.state == 1) {
    light8.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (light8.state == 1) {
    _LED_BONUS9.state = 1;
    playSound("Score10");
    addScore(1000);
    addbonusVP();
    return;
  }
  if (_LED_BONUS9.state == 1) {
    _LED_BONUS10..state = 1;
    _LED_SPECIAL_WHEN_LIT.state = 1;
    playSound("Score3000");
    addScore(1000);
    addbonusVP();
    return;
  }

  ///doble bonos ;
  if (_LED_BONUS10..state == 1) {
    _LED_SWING1.state = 1;
    light21.state = 2;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING1.state == 1) {
    _LED_SWING2.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING2.state == 1) {
    light13.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (light13.state == 1) {
    _LED_SWING4.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING4.state == 1) {
    ;
    _LED_SWING5.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING5.state == 1) {
    _LED_SWING6.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING6.state == 1) {
    _LED_SWING7.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING7.state == 1) {
    _LED_SWING8.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING8.state == 1) {
    _LED_SWING9.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING9.state == 1) {
    _LED_SWING10.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
}

void wall19_hit() {
  addScore(100);
  light25.state = 1;
  if (_LED_BONUS1.state == 0) {
    _LED_BONUS1.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS1.state == 1) {
    _LED_BONUS2.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS2.state == 1) {
    _LED_BONUS3.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS3.state == 1) {
    _LED_BONUS4.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS4.state == 1) {
    ;
    _LED_BONUS5.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS5.state == 1) {
    _LED_BONUS6.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS6.state == 1) {
    _LED_BONUS7.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (_LED_BONUS7.state == 1) {
    light8.state = 1;
    playSound("Score10");
    addScore(100);
    addbonusVP();
    return;
  }
  if (light8.state == 1) {
    _LED_BONUS9.state = 1;
    playSound("Score10");
    addScore(1000);
    addbonusVP();
    return;
  }
  if (_LED_BONUS9.state == 1) {
    _LED_BONUS10..state = 1;
    _LED_SPECIAL_WHEN_LIT.state = 1;
    playSound("Score3000");
    addScore(1000);
    addbonusVP();
    return;
  }

  ///doble bonos ;
  if (_LED_BONUS10..state == 1) {
    _LED_SWING1.state = 1;
    light21.state = 2;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING1.state == 1) {
    _LED_SWING2.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING2.state == 1) {
    light13.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (light13.state == 1) {
    _LED_SWING4.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING4.state == 1) {
    ;
    _LED_SWING5.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING5.state == 1) {
    _LED_SWING6.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING6.state == 1) {
    _LED_SWING7.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING7.state == 1) {
    _LED_SWING8.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING8.state == 1) {
    _LED_SWING9.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
  if (_LED_SWING9.state == 1) {
    _LED_SWING10.state = 1;
    playSound("Score3000");
    addScore(2000);
    addbonusVP();
    return;
  }
}

///flippers ;

void Wall14_Slingshot() {
  playSound("reelclick");
  addScore(10);
}


void wall15_Slingshot() {
  playSound("reelclick");
  addScore(10);
}

///spinner ;

void spinner1_hit() {
  addScore(100);
  playSound("spinner");
}

///Bumpers ;

void bumper1_hit() {
  if (bumper1.state == 1) {
    addScore(1000);
    bumper1.force = 6;
    playSound("bumper100");
  } else {
    addScore(100);
    playSound("score100");
  }
}

///hoyo del especial ;

void kicker1_hit() {
  if (Tilted == false) {
  }
  if (_LED_SPECIAL_WHEN_LIT.state == 1) {
    playSound("Knocke");
    Credit = Credit + 1;
    CredBox.Text = Credit;
    addScore(10000);
    _LED_SPECIAL_WHEN_LIT.state = 0;
    kicker1.timerenabled = true;
    kicker1.timerInterval = 1000;
    ;
  } else {
    bonusVPCount();
    addScore(200);
    kicker1.timerenabled = true;
    kicker1.timerInterval = 1000;
  }
  return;
}

void kicker1_Timer() {
  kicker1.timerenabled = false;
  kicker1.kick(300, 10);
  playSound("ballhit");
}

/// guardar el record ;
void savehs() {
  int FileObj;
  int ScoreFile;
  // Set FileObj=CreateObject("Scripting.FileSystemObject") ;
  // if( Not FileObj.FolderExists(UserDirectory)) {  ;
  // return ;
  // }
  // Set ScoreFile=FileObj.CreateTextFile(UserDirectory & "tab.txt",true) ;
  // ScoreFile.WriteLine hiScore ;
  // ScoreFile.Close ;
  // Set ScoreFile=Nothing ;
  // Set FileObj=Nothing ;
}

void loadhs() {
  ;
  ///cargar el record	 ;
  int FileObj;
  int ScoreFile;
  int temp1;
  // Set FileObj=CreateObject("Scripting.FileSystemObject") ;
  // if( Not FileObj.FolderExists(UserDirectory)) {  ;
  // return ;
  // }
  // if( Not FileObj.FileExists(UserDirectory & "tab.txt")) {
  // return ;
  // }
  // Set ScoreFile=FileObj.GetFile(UserDirectory & "tab.txt") ;
  // Set TextStr=ScoreFile.OpenAsTextStream(1,0) ;
  // if( (TextStr.AtEndOfStream == true)) {
  // return ;
  // }
  // temp1=TextStr.ReadLine ;
  // TextStr.Close ;
  // hiScore = CDbl(temp1) ;
  // Set ScoreFile=Nothing ;
  // Set FileObj=Nothing ;


}
*/