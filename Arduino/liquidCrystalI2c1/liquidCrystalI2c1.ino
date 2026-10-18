#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("ABCDEFGHIJKLMNOP");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("012345678901234567890");
}

void loop() {
for (int i = 0; i < 1000; i++){
  // lcd.clear();
  lcd.print(i);
  
}
while(1);
}