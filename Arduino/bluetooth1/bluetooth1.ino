
char data[1000];

void setup() {
  // put your setup code here, to run once:
Serial1.begin(38400); // Default communication rate of the Bluetooth module
Serial.begin(9600); 
// Default communication rate of the Bluetooth module
for(int i = 0; i < 100; i++){
  data[i] = 0;
}
 Serial.println(4);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println(">");
  Serial1.println('AT+VERSION?');
 // while (Serial1.available() == 0) {}     //wait for data available
  String teststr = Serial1.readString();  //read until timeout
//  Serial1.readByte(data, 10);
  //teststr.trim();                        // remove any \r \n whitespace at the end of the String
  
   // Serial.println(teststr);
   
   // Serial.println(teststr);
 
//for(int i = 0; i < 100; i++){
 // Serial.print(data[i]);
 // Serial.print(',');
//}
Serial.println('<');

}