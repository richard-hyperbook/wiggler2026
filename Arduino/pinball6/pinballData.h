//#define FAIRY 1



#define WIGGLER 1

#define LED_PIN 13



#ifdef FAIRY

#define NO_OF_INPUT_PINS 47
#define MAX_LOOP_COUNT 1000
#define INPUT_PIN_COUNT 20
#define LED_COUNT 100
#define SOL 2
#define DIGITAL_START 22
#define DIGITAL_LENGTH 34
#define ANALOG_LENGTH 10
#define TOTAL_LENGTH 44
#define SOLENOID_PIN_START 2
#define SOLENOID_LENGTH 10
// #define RELAY_PIN 2
#define BUTTON_L 66
#define BUTTON_R 67

// #define RELAY 2 //ok
// #define BUMPER_L 3 //ok
// #define BALL_RETURN 4
// #define FLIPPER_R 5
// #define POP_BUMPER 6
// #define BUMPER_R 7
// #define FLIPPER_L 8 //ok
// #define KICK_OUT 10

#define RELAY 0
#define BUMPER_L 4 //ok
#define BALL_RETURN 8 //ok
#define FLIPPER_R 7 //ok
#define POP_BUMPER 3 //ok
#define BUMPER_R 5 //ok
#define FLIPPER_L 6 //ok
#define KICK_OUT 10 //ok

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
#define BALL_RETURN_MILLIS 300

#define SERIAL_2_MP3_RX 17
#define SERIAL_2_MP3_TX 16

#define MIN_X 752
#define MAX_X 2430
#define MIN_Y 213
#define MAX_Y 3282
#define X_BANDWIDTH 50
#define Y_BANDWITH 50
#define PLAYFIELD_LEDS 77
#define ROWS 100
#define COLUMNS 2
#define SWEEP_WIDTH 150
#define SWEEP_INCREMENT 20

#define LED_50000_POINTS_TOP 0
#define LED_SPECIAL_WHEN_LIT 2
#define LED_WALL_4_1 4
#define LED_C_BUTTON 5
#define LED_WALL_3_1 6
#define LED_WALL_3_2 7
#define LED_WALL_4_2 8
#define LED_BUTTON_1000_POINTS_RIGHT 9
#define LED_WALL_3_3 10
#define LED_D_BUTTON 11
#define LED_WALL_4_4 12
#define LED_WALL_4_5 13
#define LED_WALL_4_6 14
#define LED_D 15
#define LED_C 16
#define LED_50000_POINTS_RIGHT 17
#define LED_WALL_3_4 19
#define LED_BONUS_10 21
#define LED_BONUS_9 22
#define LED_BONUS_8 23
#define LED_BONUS_7 24
#define LED_BONUS_6 25
#define LED_CIRCLE_6 26
#define LED_CIRCLE_5 27
#define LED_BONUS_5 28
#define LED_BONUS_4 29
#define LED_BONUS_3 30
#define LED_BONUS_2 31
#define LED_BONUS_1 32
#define LED_OFF_BUMPER 33
#define LED_WALL_2_2 34 //?
#define LED_WALL_2_1 36 //?
#define LED_WALL_2_1 38 //?
#define LED_RED_TARGET 39
#define LED_WAL_2_2 40 //?
#define LED_BUTTON_A 41
#define LED_WALL_1_1 42
#define LED_WALL_1_2 44
#define LED_WALL_2_2 45 //?
#define LED_BUTTON_1000_POINTS_LEFT 46
#define LED_WALL_1_3 47
#define LED_WALL_2_4 48
#define LED_BUTTON_B 49

//NEW SKETCH

#define LED_WALL_1_4 51
#define LED_WALL_1_5 52
#define LED_A 53
#define LED_B 54
#define LED_CIRCLE_1 55
#define LED_CIRCLE_2 56
#define LED_CIRCLE_3 57
#define LED_CIRCLE_4 58
#define LED_CIRCLE_7 60
#define LED_CIRCLE_8 61
#define LED_CIRCLE_9 62
#define LED_CIRCLE_10 63
#define LED_R_BUMPER_TOP 65
#define LED_R_BUMPER_BOTTOM 66
#define LED_R_EXTRA_BALL_WHEN_LIT 67
#define LED_SHOOT_AGAIN_WHEN_LIT 70
#define LED_DOUBLE_BONUS_WHEN_LIT 71
#define LED_R_BUMPER_BOTTOM 73
#define LED_R_BUMPER_TOP 74
#define LED_L_EXTRA_BALL_WHEN_LIT 76
#define LED_GAME_OVER 78
#define LED_BALL_IN_PLAY_1 79
#define LED_BALL_IN_PLAY_2 80
#define LED_BALL_IN_PLAY_3 81
#define LED_BALL_IN_PLAY_4 82
#define LED_BALL_IN_PLAY_5 83
#define LED_INSTRUCTIONS 85
#define LED_NAMPLATE_L 89
#define LED_NAMPLATE_R 90
#define LED_POP_BUMPER 92

int ledCircleArray[] = {0,LED_CIRCLE_1,LED_CIRCLE_2,LED_CIRCLE_3,LED_CIRCLE_4,LED_CIRCLE_5,
      LED_CIRCLE_6,LED_CIRCLE_7,LED_CIRCLE_8,LED_CIRCLE_9,LED_CIRCLE_10};
int ledBonusArray[] = {0, LED_BONUS_1,LED_BONUS_2,LED_BONUS_3,LED_BONUS_4,LED_BONUS_5,
    LED_BONUS_6,LED_BONUS_7,LED_BONUS_8,LED_BONUS_9,LED_BONUS_10};
int bonusLamp[] = {0, LED_CIRCLE_1, LED_CIRCLE_2, LED_CIRCLE_3, LED_CIRCLE_4, LED_CIRCLE_5,
      LED_CIRCLE_6, LED_CIRCLE_7, LED_CIRCLE_8, LED_CIRCLE_9, LED_CIRCLE_10,
        LED_BONUS_1, LED_BONUS_2, LED_BONUS_3, LED_BONUS_4, LED_BONUS_5,
    LED_BONUS_6, LED_BONUS_7, LED_BONUS_8, LED_BONUS_9, LED_BONUS_10};
#define BOUNCE_TIME 100

int sweepCounter = 5;
bool isVerticalSweep = true;
int ledCoords[ROWS][COLUMNS] = {
{1338,246}, //0
{ 0,0 }, //1
{1761,213  }, //2
{0,0  }, //3
{2247,501  }, //4
{ 2067, 543 }, //5
{ 2019,702 }, //6
{ 2121,867 }, //7
{  2316,879}, //8
{2436,183  }, //9
{ 2190,1128  }, //10
{  2286,1317}, //11
{ 2430,1386  }, //12
{ 2370,1662  }, //13
{  2245,1917 }, //14
{  2166,2079 }, //15
{  2019,1890 }, //16
{  1905,1701 }, //17
{  0,0 }, //18
{   2049,1395}, //19
{   0,0}, //20
{   1620,1809}, //21
{  1662,1965 }, //22
{   1662, 2121}, //23
{   1662,2274}, //24
{   1662,2439}, //25
{1650,2610      }, //26
{1509,2610}, //27
{ 1500, 2439 }, //28
{ 1500, 2274 }, //29
{ 1500,  2121}, //30
{ 1500,  1965}, //31
{ 1500,  1809}, //32
{  1287,1713 }, //33
{   933,1569}, //34
{ 0,0  }, //35
{ 1314,1332  }, //36
{  0,0 }, //37
{   1125,597}, //38
{ 1038,107  }, //39
{  1068,703 }, //40
{  897,831 }, //41
{ 711,993  }, //42
{  0,0 }, //43
{ 693,981  }, //44
{ 981,1092  }, //45
{  840,1188 }, //46
{ 729,1461  }, //47
{  987,1449 }, //48
{  915,1557 }, //49
{  0,0 }, //50
{   777,1662}, //51
{ 73,1941  }, //52
{  1050,1889 }, //53
{  990,2103 }, //54
{ 1050,2268  }, //55
{ 1200,2385  }, //56
{   1290,2490}, //57
{ 1383,2583  }, //58
{  0,0 }, //59
{  1767,2583 }, //60
{  1884,2500 }, //61
{ 1971,2391  }, //62
{ 2010,2277  }, //63
{  0,0 }, //64
{  2184,2847 }, //65
{   2118,2991}, //66
{  0,0 }, //67
{  0,0 }, //68
{  0,0 }, //69
{  1584,3117 }, //70
{  1585, 2928}, //71
{  0,0 }, //72
{   1047,3006}, //73
{   1005,2871}, //74
{   0,0}, //75
{   752,3282}, //76
{   0,0}, //77
{   0,0}, //78
{   0,0}, //79
{   0,0}, //80
{   0,0}, //81
{   0,0}, //82
{   0,0}, //83
{   0,0}, //84
{   0,0}, //85
{   0,0}, //86
{   0,0}, //87
{   0,0}, //88
{   0,0}, //89
{   0,0}, //90
{   0,0}, //91
{   1761,1889}, //92

};


int loopCounter = 0;
int blinkToken = 0;
int currentInputIndex = -1;
int currentInputValue = 0;

int count = 0;
String bluetoothChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
int noOfInputPins = 0;
String inputString;
int solenoidIndex = -1;
int ledCounters[LED_COUNT];
int ledNumber = 0;
int counter = 0;


int outpin = 9;
int outValue = 0;
char inputChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
char oldChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
int analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 };
// int inputPins[] = {
//   /* 0   1   2   3   4   5   6   7   8   9 */
//   /*0*/ 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
//   /*1*/ 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
//   /*2*/ 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
//   /*            54, 55, 56, 57, 58, 59, 60, 61, */
//   /*3*/ 52, 53, A0, A1, A2, A3, A4, A5 //, A6, A7,
//   /*    62, 63, 64, 65, 66, 67, 68, 69  */
//  // /*4*/ A8, A9, A10, A11, A12, A13, A14, A15
// };
int solenoidPins[]  = { 2, 3, 4, 5, 6, 7, 8 , 9, 10, 11};
 // = { RELAY, BUMPER_L, FLIPPER_L, FLIPPER_R, POP_BUMPER, BUMPER_R, BALL_RETURN, KICK_OUT };

unsigned long solenoidCounters[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
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


#define MAX_ADVANCE 10
#define MAX_BONUS 10

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

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIGGLER


#define NO_OF_PLAYERS 4
#define NO_OF_SCORE_DIGITS 4
#define TOTAL_NO_OF_SCORE_REELS (NO_OF_PLAYERS * NO_OF_SCORE_DIGITS)
#define NO_OF_BALLS 5
#define MAX_LOOP_COUNT 1000
#define LED_COUNT 50
#define BUMPER_DELAY 10
#define LED_DELAY 20
#define BUMPER_MILLIS 300
#define FLIPPER_MILLIS 1000
#define BALL_RETURN_MILLIS 300


#define NO_OF_LEDS 50
#define FLIPPER_ON_TIME 300

#define LED_SINGSHOT_R_BOTTOM 0
#define LED_SINGSHOT_R_TOP 1
#define LED_FREE_BALL_GATE_OPEN_WHEN_LIT 2
#define LED_OPENS_GATE_WHEN_LIT 3
#define LED_R_PLASTIC_BOTTOM 4
#define LED_R_PLASTIC_MIDDLE_BOTTOM 7
#define LED_R_PLASTIC_MIDDLE_TOP 9
#define LED_R_PLASTIC_TOP 12
#define LED_FAR_R_CHANNEL_BARRIER 11
#define LED_HIT_WHEN_LIT_TO_LITE_R 16
#define LED_MIDDLE_R_CHANNEL_BARRIER 17
#define LED_MIDDLE_L_CHANNEL_BARRIER 18
#define LED_FAR_L_CHANNEL_BARRIER 19
#define LED_L_PLASTIC_TOP 20
#define LED_HIT_WHEN_LIT_TO_LITE_L 21
#define LED_RUBBER_TARGET_R 22
#define LED_RUBBER_TARGET_L 22
#define LED_WIGGLE_ALLEY_PLASTIC_TOP 25
#define LED_WIGGLE_ALLEY_WHEN_LIT_GATE_OPEN 26
#define LED_WIGGLE_ALLEY_PLASTIC_FAR_LEFT_TOP 27
#define LED_WIGGLE_ALLEY_A 28
#define LED_WIGGLE_ALLEY_B 29
#define LED_WIGGLE_ALLEY_C 30
#define LED_WIGGLE_ALLEY_PLASTIC_R 32
#define LED_WIGGLE_ALLEY_D 33
#define LED_WIGGLE_ALLEY_PLASTIC_FAR_LEFT_BOTTOM 34
#define LED_WIGGLESVILLE_100 36 
#define LED_WIGGLESVILLE_300 37
#define LED_WIGGLESVILLE_500 38
#define LED_SINGSHOT_L_TOP 40
#define LED_SINGSHOT_L_BOTTOM 41
#define LED_WHEN_LIT_SAME_PLAYER_SHOOTS_AGAIN 42
#define LED_WHEN_LIT_FLIPS_OUT 43
#define LED_TOP_200 44

#define BUTTON_START A3
#define BUTTON_L A4
#define BUTTON_R A5

#define MIN_X 752
#define MAX_X 2430
#define MIN_Y 213
#define MAX_Y 3282
#define X_BANDWIDTH 50
#define Y_BANDWITH 50
#define PLAYFIELD_LEDS 77
#define ROWS 100
#define COLUMNS 2
#define SWEEP_WIDTH 150
#define SWEEP_INCREMENT 20
#define BOUNCE_TIME 100

#define INDEX_SW_R_MUSHROOM 10
#define INDEX_SW_C_MUSHROOM 11
#define INDEX_SW_L_MUSHROOM 37

int sweepCounter = 5;
bool isVerticalSweep = true;

int loopCounter = 0;
int blinkToken = 0;
int currentInputIndex = -1;
int currentInputValue = 0;

int count = 0;
// int noOfInputPins = 0;
String inputString;
int solenoidIndex = -1;
int ledCounters[LED_COUNT];
int ledNumber = -1;
int solNumber = 0;
unsigned long int counter = 0;

int outpin = 9;
int outValue = 0;
int analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 };
int inputPins[] = {
  /* 0   1   2   3   4   5   6   7   8   9 */
  /*0*/ 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  /*1*/ 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
  /*2*/ 42, 43, 44, 45, 46, 47, 48, 49, 50,
  /*    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, */
  /*3*/             A0, A1, A2, A3, A4, A5, A6,
  /*    62, 63, 64, 65, 66, 67, 68, 69, 70, 71, */
  /*4*/ A7, A8, A9, A10,A11
  
};


#define SOL_BALL_RETURN_KICKER 12 //SA0
#define SOL_L_SLINGSHOT 11 //SA1
#define SOL_L_FLIPPER 10 //SA2
#define SOL_ZIPPER_FLIPPER_RELEASE 9 //SA3
#define SOL_ZIPPER_FLIPPER_ACTIVATE 8 //SA4
#define SOL_R_FLIPPER 7 //SA5
#define SOL_R_SLINGSHOT 6 //SA6
#define SOL_BALL_RELEASE 5 //SA7
#define SOL_GATE_RELAY 4 //SB0
#define SOL_L_THUMPER 3 //SB1
#define SOL_R_THUMPER 2 //SB2  
#define SOL_C_THUMPER 52 //SB3
#define SOL_TOP_HOLE_POT_KICKER 51 //SB4
#define SOL_FREE_BALL_GATE 53 //SB5
#define SOL_BOTTOM_HOLE_POT_KICKER 49 //SB5


#define INDEX_SOL_BALL_RETURN_KICKER 0 //SA0
#define INDEX_SOL_L_SLINGSHOT 1 //SA1
#define INDEX_SOL_L_FLIPPER 2 //SA2
#define INDEX_SOL_ZIPPER_FLIPPER_RELEASE 3  //SA3
#define INDEX_SOL_ZIPPER_FLIPPER_ACTIVATE 4 //SA4
#define INDEX_SOL_R_FLIPPER 5 //SA5
#define INDEX_SOL_R_SLINGSHOT 6 //SA6
#define INDEX_SOL_BALL_RELEASE 7 //SA7
#define INDEX_SOL_GATE_RELAY 8 //SB0
#define INDEX_SOL_L_THUMPER 9 //SB1
#define INDEX_SOL_R_THUMPER 10//SB2
#define INDEX_SOL_C_THUMPER 11 //SB3
#define INDEX_SOL_TOP_HOLE_POT_KICKER 12 //SB4
#define INDEX_SOL_FREE_BALL_GATE 13 //SB5
#define INDEX_SOL_BOTTOM_HOLE_POT_KICKER 14 //SB6





int solenoidPins[] = {
 SOL_BALL_RETURN_KICKER, //SA0
 SOL_L_SLINGSHOT, //SA1
 SOL_L_FLIPPER, //SA2
 SOL_ZIPPER_FLIPPER_RELEASE, //SA3
 SOL_ZIPPER_FLIPPER_ACTIVATE, //SA4
 SOL_R_FLIPPER, //SA5
 SOL_R_SLINGSHOT, //SA6
 SOL_BALL_RELEASE, //SA7
 SOL_GATE_RELAY, //SB0
 SOL_L_THUMPER, //SB1
 SOL_R_THUMPER, //SB2
 SOL_C_THUMPER, //SB3
 SOL_TOP_HOLE_POT_KICKER, //SB4
 SOL_FREE_BALL_GATE, //SB5
 SOL_BOTTOM_HOLE_POT_KICKER //SB6
};


unsigned long delayCounters[3] = {0, 0, 0};
typedef void (*func_type)(void);
func_type delayCallbacks[3];
//void (*delayCallbacks[3])(void);


unsigned long solenoidCounters[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
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



int currentPlayer = 1;
bool inPlay = true;
// long score = 0;
long lastScore = 0;
int bonus = 0;
int advance = 0;
int ballNumber = 0;
bool isBeforeFirstBallPlayed = true;


//Visual Pinball variables
bool gameOn = false;
//long score = 0;
int eBCount = 0;//
int ball = 0;
bool ballUp = false;

#define NO_OF_INPUT_PINS sizeof(inputPins) / sizeof(inputPins[0])
#define SOLENOID_LENGTH sizeof(solenoidPins) / sizeof(solenoidPins[0])

#define LENGTH_OF_BBD 25
int bBD [LENGTH_OF_BBD] = {0};
int lastBBD [LENGTH_OF_BBD] = {9};


#define NO_OF_LEDS 50
bool ledState [NO_OF_LEDS] = {false} ;

#define p1m3 bBD[0]
#define p1m2 bBD[1]
#define p1m1 bBD[2]
#define p1m0 bBD[3]
#define p2m3 bBD[4]
#define p2m2 bBD[5]
#define p2m1 bBD[6]
#define p2m0 bBD[7]
#define p3m3 bBD[8]
#define p3m2 bBD[9]
#define p3m1 bBD[10]
#define p3m0 bBD[11]
#define p4m3 bBD[12]
#define p4m2 bBD[13]
#define p4m1 bBD[14]
#define p4m0 bBD[15]
#define playerUpLights bBD[16]
#define gameOverLight bBD[17]
#define ballInPlayLights bBD[18]
#define canPlayLights bBD[19]
#define wiggleJetSuperBonus1 bBD[20]
#define wiggleJetSuperBonus2 bBD[21]
#define wiggleJetSuperBonus3 bBD[22]
#define wiggleJetSuperBonus4 bBD[23]
#define additionalDisplayedDigit bBD[24]


/*
Wiggler back box displays:
ScoreString (char array), all chars = 0 to 9
0..3, ABCDD, Player 1 score (thousands 0. humdreds 1, tens 2, units 3)
4..7, EFGH, Player 2 score
8..11, IJKL, Player 3 score
12..15, MNOP, Player 4 score
16, Q, 1up to 4up
17, R, 1 = 'GAME OVER' light
18, S, 1 to 5 'BALL IN PLAY' light
19, T, 1 to 4 'CAN PLAY'
20..23, UVWX,  Four single reel counters labelled 'WIGGLE JET SUPER BONUS'
24, Y, additional displayed digit
*/


#define STATE_OFF 0
#define STATE_ON 1
//#define STATE_START_GAME 2
#define STATE_IN_PLAY 3
#define STATE_BALL_DRAINED 4
#define STATE_GAME_OVER 5
int state = STATE_OFF;


#endif

/* 


center amd right mushroom contacts inetermittant



*/