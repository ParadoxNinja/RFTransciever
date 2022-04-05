#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(2,3); //CE,CSN
const byte address[6] = "00001";

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

#define j1Xr 3
#define j1Yr 5
#define j1Br 4

#define j2Xr 6
#define j2Yr 9
#define j2Br 7

#define toggleSwitchAr 0
#define toggleSwitchBr 1

#define pushButtonAr 2
#define pushButtonBr 8

#define potABr 10

struct Data_Package {
  byte j1X;
  byte j1Y;
  byte j1B;
  byte j2X;
  byte j2Y;
  byte j2B;
  byte potA;
  byte potB;
  byte toggleSwitchA;
  byte toggleSwitchB;
  byte pushButtonA;
  byte pushButtonB;
};

Data_Package data;

void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  resetData();

  pinMode(j1Xr,OUTPUT);
  pinMode(j1Yr,OUTPUT);
  pinMode(j1Br,OUTPUT);
  
  pinMode(j2Xr,OUTPUT);
  pinMode(j2Yr,OUTPUT);
  pinMode(j2Br,OUTPUT);

  pinMode(toggleSwitchAr,OUTPUT);
  pinMode(toggleSwitchBr,OUTPUT);

  pinMode(pushButtonAr,OUTPUT);
  pinMode(pushButtonBr,OUTPUT);

  pinMode(potABr,OUTPUT);

}

void loop() {

  currentTime = millis();
  if(currentTime - lastReceiveTime > 1000){
    resetData();
  }

  

}

void resetData(){

  data.j1X = 127;
  data.j1Y = 127;
  data.j1B = 0;
  data.j2X = 127;
  data.j2Y = 127;
  data.j2B = 0;
  data.potA = 1;
  data.potB = 1;
  data.toggleSwitchA = 0;
  data.toggleSwitchB = 0;
  data.pushButtonA = 0;
  data.pushButtonB = 0;
  
}
