//pins

int RPin = A0;
int GPin = D0;
int BPin = D1;
int frsPin = A1;

//
bool waiting; //is there a person sit down?
bool connected; //is phone call made?
bool sitDownPublished;

int frsThreshold = 1000;

void setup(){
  setPinMode(RPin, OUTPUT);
  setPinMode(GPin, OUTPUT);
  setPinMode(BPin, OUTPUT);
  setPinMode(frsPin, INPUT);
  setLEDColor("red");
}

void loop(){
  //if somebody is sitting on the chair

  if(isSat()){
    //if just sit down in this loop
    if(!waiting){
      Spark.publish("someone-sit-down", Spark.deviceID());

    //if sat down before this loop
    }else{
      if(!connected){
        
      }
    }

  //if nobody is sitting on the chair
  }else{

    //if just quit from connection
    if(connected){

    //if just quit from waiting
    }else if(waiting){
      initValues();
    }
  }

  //change light colors
  if(!waiting) setLEDColor("red"); //nobody sitting
  if(waiting && !connected) setLEDColor("green"); //sat and waiting for connection
  if(connected) setLEDColor("purple"); //sat and waiting for connection

  delay(200);
}

bool isSt(){
  return analogRead(frsPin) > frsThreshold ? true : false;
}

//set color output for RGB LED
void setLEDColor(String color){
  int r, g, b;
  switch(color){
    case "red":
      r = 0;
      g = 255;
      b = 255;
    case "purple":
      r = 0;
      g = 255;
      b = 0;
    case "blue":
      r = 255;
      g = 255;
      b = 255;
  }
  analogWrite(RPin, r);
  analogWrite(GPin, g);
  analogWrite(BPin, b);
}

void makeConnection(const char *event, const char *data){
  connected = true;
}

void quitConnection(){
  connected = false;
  initValues();
}

void initValues(){
  bool waiting = false;
  bool connected = false;
  bool sitDownPublished = false;
}
