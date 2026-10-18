class Component{
  public: 
    bool state;
  Component(bool myState){
    state = myState;
  }  
  Component(bool x, Component a, Component b){
    state = x;
  }
};

class Switch: public Component{
  
};

class Join: public Component{
  Component a;
  Component b;
  bool isAnd;
  public:
  Join(bool x, Component aa, Component bb) 
  : Component(){
    isAnd = x;
    a = aa;
    b = bb;
  }
  
  void compute(){
    if (isAnd){
    return Component(a.state && b.state);
    }
    return Component(a.state || b.state);
  )}
};

Switch s1, s2;
Join j1(true, s1, s2);


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
