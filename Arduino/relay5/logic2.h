
#define MAX 200
#define S1 0
#define S2 1
#define W1 2
int a;
enum nodeType { isSwitch,
                isAnd,
                isOr,
                isRelay,
                isUniContact };
struct node {
  bool valid;
  bool state;

  int a;
  int b;
  nodeType type;
};
node nodes[MAX];

void setupNodes(){
  for(i = 0; i < MAX; i++){
    nodes[i] = {false, false, "", &nodes[i], &nodes[i], isSwitch}
void printBool(String prefix, bool value){
  String s = "0";
  if (value) s = "1";
  Serial.println(prefix + s);
}

bool c(node* n) {
  printBool("<3>", n->state);
  bool response = false;
  switch (n->type) {
    case sw1:
      response = n->state;
      break;
    case and1:
      printBool("<4>", n->a->state);
      printBool("<5>", n->a->state);
      response = n->a->state && n->b->state;
       printBool("<6>", response);
     break;
    case or1:
      response = n->a->state || n->b->state;
      break;
    case relay1:
      response = n->a->state;
      break;
      
  }
  n->state = response;
  return response;
}

void logicSetup() {

  printBool("<1>", nodes[W1].state);
  nodes[S1] = { true, &nodes[S1], &nodes[S1], isSwitch };
  nodes[S2] = { false, &nodes[S2], &nodes[S2], isSwitch};
  nodes[W1] = {false, &nodes[S1], &nodes[S2], isAnd };
  c(&nodes[W1]);
 printBool("<2>", nodes[W1].state);
}
