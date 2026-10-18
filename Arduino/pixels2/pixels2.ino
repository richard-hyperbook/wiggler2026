// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN 13

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 100
#define SOL 2
#define DIGITAL_START 22
#define DIGITAL_LENGTH 34
#define ANALOG_LENGTH 10
#define TOTAL_LENGTH 44
#define SOLENOID_PIN_START 2
#define SOLENOID_LENGTH 6
#define RELAY_PIN 2

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

uint32_t color = strip.Color(0, 0, 0);

uint32_t colorPin = strip.Color(0, 0, 0);
int inpin = 22;
uint32_t green = strip.Color(255, 0, 0);
uint32_t red = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t white = strip.Color(255, 255, 255);
uint32_t off = strip.Color(0, 0, 0);

int outpin = 9;
int outValue = 0;
int digitalPins[DIGITAL_LENGTH];
int inputValues[TOTAL_LENGTH];
char inputChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
char oldChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYZ";
int analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 };
int inputPins [] = {
                  /* 0   1   2   3   4   5   6   7   8   9 */
               /*0*/22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
               /*1*/32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
               /*2*/42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
               /*           54, 55, 56, 57, 58, 59, 60, 61, */  
               /*3*/52, 53, A0, A1, A2, A3, A4, A5, A6, A7,
               /*   62, 63, 64, 65, 66, 67, 68, 69  */  
               /*4*/A8, A9,A10,A11,A12,A13,A14,A15};
int solenoidPins[] = { 2, 3, 4, 5, 6, 7, 8 };
int count = 0;
String bluetoothChars = "aBCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJLKMNOPQRSTUVWXYz";
int counter = 0;
int noOfInputPins = 0;
String inputString;

void setup() {
  noOfInputPins = sizeof(inputPins) / sizeof(int);
  //Serial.println(999);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  for (int i = 0; i < noOfInputPins; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < SOLENOID_LENGTH; i++) {
    solenoidPins[i] = SOLENOID_PIN_START + i;
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], 0);
  }

  //for (int i = 0; i < ANALOG_LENGTH; i++){
  //}
  Serial.begin(9600);
  Serial1.begin(9600);
  strip.begin();             // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();              // Turn OFF all pixels ASAP
  strip.setBrightness(250);  // Set BRIGHTNESS to about 1/5 (max = 255)
                             //pinMode (inpin, INPUT_PULLUP);
 noOfInputPins = sizeof(inputPins) / sizeof(int);
 // Serial1.print("AT\r\n");
  //while(Serial1.available() < 2){
   // Serial.print('£');
 // }
  inputString = Serial1.readString();
  Serial.println(inputString);

  //Serial1.print("AT+HELP\r\n");
  //while(Serial1.available() < 2){
  //  Serial.print('^');
  //}
  //inputString = Serial1.readString();
  //Serial.println(inputString);
  // Serial1.print(noOfInputPins);
  //Serial1.println('@');


  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, off);
  }
  strip.show();
  //pinMode(outpin, OUTPUT);
  //pinMode (SOL, OUTPUT);
  //digitalWrite(solenoidPins[0], 1);

  //Serial.println(solenoidPins[0]);
  digitalWrite(solenoidPins[0], 1);
}


// loop() function -- runs repeatedly as long as board is on ---------------



void loop() {
  // strip.setPixelColor(count, white);
  // if (count != 0) {
    // strip.setPixelColor(count - 1, off);
  // }
  // if (count >= LED_COUNT) {
    // count = 0;
  // } else {
    // count++;
  // }
  //Serial.println(count);
  // strip.show();
  //delay(2000);
  //}
  // Fill along the length of the strip in various colors...
  //colorWipe(strip.Color(255,   0,   0), 50); // Red
  //colorWipe(strip.Color(  0, 255,   0), 50); // Green
  //colorWipe(strip.Color(  0,   0, 255), 50); // Blue
  //colorWipe(strip.Color(  255,   255, 255), 50); // Blue
  //colorWipe(strip.Color(  255,   255, 255), 100);
  //colorWipe(strip.Color(  255,   0, 0), 100);
  //colorWipe(strip.Color(  0,   255, 0), 100);
  //colorWipe(strip.Color(  0,   0, 255), 100);
  //colorWipe(strip.Color(  0,   0, 0), 100);

  // Do a theater marquee effect in various colors...
  //theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
  //int buttonState = digitalRead(22);

  /*if (buttonState) {
  color = green;
  //Serial.println("GREEN");
  outValue = 0;
} else {
  color = blue;
    Serial.println("BLUE");
    outValue = 255;

}
*/
  //  analogWrite (SOL, outValue);
  /*  color = green;
  strip.setPixelColor(0, color);   
  for(int c=0; c<strip.numPixels(); c++) {
       
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
   strip.show();  
*/

  for (int i = 0; i < noOfInputPins; i++) {
    inputValues[i] = digitalRead(inputPins[i]);
    //Serial.println(digialPins[i]);
    if (inputValues[i] == 1) {
      inputChars[i] = '1';
      // colorPin = white;
    } else {
      inputChars[i] = '0';
      // colorPin = blue;
    }
    // strip.setPixelColor(i, colorPin);
  // }
   //for (int i = 0; i < noOfInputPins; i++) {
      if ((inputChars[i] != oldChars[i])) {
        if (inputValues[i] == 0) {
          Serial1.print('0');
          // if (i == 4) {
            // digitalWrite(solenoidPins[6], 1);
          // }
        } else {
          Serial1.print('1');
          // if (i == 4) {
            // digitalWrite(solenoidPins[6], 0);
          // }
        }
        Serial1.print('=');
        Serial1.println(i+22);
        // Serial1.println(inputChars);
      }
      oldChars[i] = inputChars[i];
    }

  
    // if ((i < 7) && (i > 0)) {
      // int barInput = 0;
      // if (inputValues[i] == 0) {
        // barInput = 1;
      // }
      //Serial.println(barInput);
      // digitalWrite(solenoidPins[i], barInput);
    // }
  }
  // int val;
  // for (int i = 0; i < ANALOG_LENGTH; i++) {

  //   // val = analogRead(analogPins[i]);
  //   // if (i == 4){Serial.println(val);}
  //   if (val > 512) {
  //     inputValues[i + DIGITAL_LENGTH] = 1;
  //     inputChars[i + DIGITAL_LENGTH] = '1';
  //     inputValues[i + DIGITAL_LENGTH] = 0;
  //     colorPin = white;
  //   } else {
  //     inputChars[i + DIGITAL_LENGTH] = '0';
  //     colorPin = blue;
  //   }
  //   strip.setPixelColor(i + DIGITAL_LENGTH, colorPin);
  // }


  // strip.show();

  //rainbow(1);             // Flowing rainbow cycle along the whole strip
  //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
    // Serial1.print(counter);
// counter++;
  // Serial1.println('+');

  
  //Serial1.println('AT+TYPE');
  // bluetoothChars = Serial1.readString();
  // Serial.println('*');
  // Serial.println(bluetoothChars);
 // delay(20);
// }



/*
// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
*/
