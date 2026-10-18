#define MAX 10
class Wire{
  public: 
    bool state;
    bool active;
    Wire(){
        state = false;
        active = false;
      }
    }
}
class Wire: public Switch{

}
class Loom{
  public:
    Wire andContacts[MAX];
    Wire orContacts[MAX];
    bool on(){
      bool r = false;
      for (i = 0; i < MAX; i++){
        if (andContacts[i].active){
          if (i == 0){
            r = true;
          }
          r = r && andContacts[i];
        } else break;
      }
      for(i = 0; i < MAX; i++){
        if (orContacts[i]).active){
          r = r ¦¦ orContacts[i];
        } else break;
      }
      return r;
    }
}
// class Contact{
//   private:
//     Loom input;
//   public:
//   Contact(Wires wires[MAX]){
//     for(int i = 0; i < MAX; i++){
//       inputs[i] = wires[i];
//     }
//   }
  
// }
class Device: public Uniselector{
  private:
    int selection = 0;
  public:
  Uniselector(Wire wires[MAX]){
    for(int i = 0; i < MAX; i++){
      iputs[i] = wires[i];
    }
  }
  
    Wire isSelected(int pos){
      return (pos == state);
    }
}
class Relay{
   public: 
     Loom loom;
     bool on(){
       loom.on;
     }
}


Switch anAddLens;
Relay E;
Loom Eloom()

void setup() {
  Eloom.andContacts = {anAddLens, E};

}

void loop() {
  print 
  E.
}
