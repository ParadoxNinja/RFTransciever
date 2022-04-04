#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(2,3); //CE,CSN
const byte address[6] = "00001";

#define joysticButton1 0
#define joysticButton2 1
#define pushButton1 4
#define pushButton2 5
#define slideSwitchA 6
#define slideSwitchB 7

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
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  pinMode(joysticButton1,INPUT_PULLUP);
  pinMode(joysticButton2,INPUT_PULLUP);
  pinMode(pushButton1,INPUT_PULLUP);
  pinMode(pushButton2,INPUT_PULLUP);
  pinMode(slideSwitchA,INPUT_PULLUP);
  pinMode(slideSwitchB,INPUT_PULLUP);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);

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

void loop() {
  
  data.j1X = map(analogRead(A0),0,1023,0,255);
  data.j1Y = map(analogRead(A1),0,1023,0,255);
  data.j1B = digitalRead(joysticButton1);
  
  data.j2X = map(analogRead(A2),0,1023,0,255);
  data.j2Y = map(analogRead(A3),0,1023,0,255);
  data.j2B = digitalRead(joysticButton2);
  
  data.potA = map(analogRead(A4),0,1023,0,255);
  data.potB = map(analogRead(A5),0,1023,0,255);

  data.toggleSwitchA = digitalRead(slideSwitchA);
  data.toggleSwitchB = digitalRead(slideSwitchB);

  data.pushButtonA = digitalRead(pushButtonA);
  data.pushButtonB = digitalRead(pushButtonB);
  
  radio.write(&data, sizeof(Data_Package));
  
}
