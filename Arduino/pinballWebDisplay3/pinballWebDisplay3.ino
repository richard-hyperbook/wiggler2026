
#include <Arduino.h>
#include <ES32Lab.h>
// #include <SoftwareSerial.h>
#include "SoftwareSerial.h"
#include <TFT_eSPI.h>
#include <SPI.h>
// #include <Wire.h>
#include <WiFi.h>
// #include <WiFiClient.h>
#include <WebServer.h>
// #include <ESPmDNS.h>
#include <WebServer.h>  // standard library
#include "SuperMon.h"   // .h file that stores your html page code

const char *ssid = "AV2";
const char *password = "0279410364";

WebServer server(80);

const int led = 12;
unsigned long hh, mm, ss, targetTime;
String incoming = "zzz";
String lastIncoming = "ccc";
bool complete = false;
uint8_t buffer[700] = { 0 };
size_t size;
String timeString = "BBB";

void handleRoot() {
   Serial.println("<10>");
  digitalWrite(led, 1);
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
   Serial.println("*" + incoming + "*");
  snprintf(temp, 400,

           "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>Fairy</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Pinball\
    %02d:%02d:%02d\
    %s</h1>\
  </body>\
</html>",

           hr, min % 60, sec % 60, lastIncoming
          );
  server.send(200, "text/html", temp);
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
   Serial.println("<11>");
}

// SoftwareSerial SoftSerial(37, 38);
// Bonezegei_SoftSerial SoftSerial(21, 22);
EspSoftwareSerial::UART SoftSerial;
// SoftwareSerial SoftSerial;
// TFT_Plus tft;
TFT_eSPI tft;
#define TFT_GREY 0xBDF7

void setup(void) {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);  // Adding a black background colour erases previous text automatically
  targetTime = millis() + 1000;
  Serial.begin(9600);
  Serial.println("START");

  // SoftSerial.begin(9600);
  // SoftSerial.setDebugOutput(false);
  // SoftSerial.swap();

  SoftSerial.begin(9600, EspSoftwareSerial::SWSERIAL_8N1, 12, 13, false, 95);
  //  SoftSerial.enableIntTx(true);

 pinMode(led, OUTPUT);
  digitalWrite(led, 0);
//  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(WiFi.status());
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // if (MDNS.begin("esp32")) {
    // Serial.println("MDNS responder started");
  // }

  server.on("/", handleRoot);
  //server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  delay(1000);
    SoftSerial.println("   @");
}


void loop() {
    server.handleClient();
  if (targetTime < millis()) {
    targetTime = millis() + 1000;
    ss++;  // Advance second
    if (ss == 60) {
      ss = 0;
      mm++;  // Advance minute
      if (mm > 59) {
        mm = 0;
        hh++;  // Advance hour
        if (hh > 23) {
          hh = 0;
        }
      }
    }
    while (SoftSerial.available()) {

      char c = SoftSerial.read();
      if (c != '@') {
        incoming = incoming + c;
      } else {
        complete = true;
        lastIncoming = incoming;
      }
        // Serial.println("<12>");
    }
    String hhh = String(hh);
    String mmm = String(mm);
    String sss = String(ss);
    timeString = hhh + ":" + mmm + ":" + sss;
    tft.drawCentreString("        ", 64, 50, 4);
    tft.drawCentreString(timeString, 64, 30, 4);
    if (complete) {
      tft.drawCentreString("                  ", 64, 100, 4);
      tft.drawCentreString(incoming, 64, 100, 4);
      SoftSerial.println(timeString + "@");
      Serial.println(">" + incoming);
      Serial.println("=" + timeString);
      complete = false;
      incoming = "";
    }
  }
  // Serial.println("<13>");
  //delay(2);//allow the cpu to switch to other tasks
  //  SoftSerial.println("X@");
  server.handleClient();
}



