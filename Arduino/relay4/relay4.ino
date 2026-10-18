//#include <SoftwareSerial.h>
#include <Arduino.h>
//#include <dummy.h>

#include <ESP8266SSDP.h>
#include <ESP8266WiFi.h>
//#include <SoftwareSerial.h>

#define MAX 200
#define S1 0
#define S2 1
#define W1 2
int a;
enum nodeType { sw1,
                and1,
                or1,
                relay1 };
struct node {
  bool state;
  node* a;
  node* b;
  nodeType type;
};
node nodes[MAX];



bool c(node* n) {
  bool response = false;
  switch (n->type) {
    case sw1:
      response = n->state;
      break;
    case and1:
      response = n->a->state && n->b->state;
      break;
    case or1:
      response = n->a->state || n->b->state;
      break;
    case relay1:
      response = n->a->state;
      break;
      ;
  }
  return response;
}

void setup() {
  delay(3000);
  Serial.begin(115200);
  // Serial.setDebugOutput(false);
  // delay(1000);
  Serial.println("<1>" + (nodes[W1].state));
  nodes[S1] = { false, &nodes[S1], &nodes[S1], sw1 };
  nodes[S2] = { false, &nodes[S2], &nodes[S2], sw1 };

  nodes[W1] = { false, &nodes[S1], &nodes[S2], and1 };
  Serial.println("<2>" + (nodes[W1].state));
}

void loop() {
   a=a+1;
 a=a-1;
 delay(1000);
}

