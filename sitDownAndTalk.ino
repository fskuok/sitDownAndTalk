//pins


int redPin = A0;
int greenPin = D0;
int bluePin = D1;
int frsPin = A1;


bool waiting; //is there a person sit down?
bool connected; //is phone call made?
bool sitDownPublished;

//0: nothing happends
//1: somebody sitdown on this chair, wait for another chair
//2: somebody sitdown on other chair, wait for people
//4: connection build
int phase = 0;


char selfId[25];
char targetId[25];
char connectedId[25];

int frsThreshold = 1000;

void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(frsPin, INPUT);
  setLEDColor('red');
  Spark.variable("phase", &phase, INT);
  Spark.subscribe("someone-sit-down", sitDownEventHandler);
  Spark.subscribe("connection-request", connectionRequestHandler);
  Spark.subscribe("quitConnection", quitConnectionHandler);
  Spark.deviceID().toCharArray(selfId, 25);
}

void loop(){

  switch(phase){
    case 0://0: nothing happends

      if(isSat()){
        Spark.publish("someone-sit-down", selfId);
        phase = 1;
      }

      break;

    case 1://1: waiting for another chair

      //if the person leaves
      if(!isSat()){
        phase = 0;
        //here should publish an event
      }

      break;

    case 2://2: waiting for people


      //a person sit down
      if(isSat()){
        phase = 4;
        Spark.publish("connection-request", targetId);
      }

      break;

    case 4://4: connection build
      break;
  }

  setLEDColor(phase);
  delay(100);
}

void sitDownEventHandler(const char *event, const char *id){
  char temp[25];
  strcpy(temp, id);
  //if this event come from this chair, ignore it
  if(strcmp(temp,selfId) == 0){
  //if this event from other chair
  //
  }else if(phase == 0){
    strcpy(targetId, id);
    phase = 2;
  }else if(phase == 1){
    makeConnection();
    phase = 4;
  }
}

void connectionRequestHandler(const char *event, const char *id){
  char temp[25];
  strcpy(temp, id);
  //
  if(strcmp(temp, selfId) != 0){
    phase = 4;
    makeConnection();
  //if the request is not for this chair
  //which means some other two chair connected
  }else if(phase == 2){
    phase = 0;
  }
}

void quitConnectionHandler(const char *event, const char *id){
  quitConnection();
}

bool isSat(){
  return analogRead(frsPin) > frsThreshold ? true : false;
}

//set color output for RGB LED
void setLEDColor(int phase){
  int r, g, b;
  switch(phase){
    case 0:
      r = 0;
      g = 255;
      b = 255;
      break;
    case 2:
      r = 0;
      g = 255;
      b = 255;
      break;
    case 1:
      r = 0;
      g = 255;
      b = 0;
      break;
    case 4:
      r = 255;
      g = 255;
      b = 255;
      break;
  }
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}


void makeConnection(){
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
