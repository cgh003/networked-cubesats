#include <Wire.h>
#include "SparkFunMPL3115A2.h"
#include "SparkFunHTU21D.h"
#include <XBee.h>
MPL3115A2 myPressure;
HTU21D myHumidity;

float potpin = 0;
int ROW = 0;
int LABEL = 1;
int val = 0;

int sensorValueM, sensorValueC, sensorValueH;
XBee xbee = XBee();
uint8_t dat0[] = {0,0,0,0};
uint8_t dat1[] = {0,0,0,0};
uint8_t dat2[] = {0,0,0,0};
uint8_t dat3[] = {0,0,0,0};
uint8_t dat4[] = {0,0,0,0};
uint8_t dat5[] = {0,0,0,0};

int num, num2, num3;
void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
  Wire.begin(); 
  myPressure.begin();
  myHumidity.begin();
  
  myPressure.setModeBarometer(); 

  myPressure.setOversampleRate(7); 
  myPressure.enableEventFlags(); 
}

void loop() {
  delay(3000);
  XBeeAddress64 addr64 = XBeeAddress64();
  addr64.setMsb(0x0013a200);
  addr64.setLsb(0x40b450ee);
 
  // put your main code here, to run repeatedly:
  sensorValueC = analogRead(2);       // read analog input pin 0
  Serial.print("Carbon Monoxide Value: ");
  Serial.print(sensorValueC, DEC);    // prints the value read
  Serial.println(" ppm");
  sendNum0(sensorValueC, 9);
  ZBTxRequest zbTx = ZBTxRequest(addr64, dat0, sizeof(dat0));
  xbee.send(zbTx);
  delay(1000);
  
  sensorValueH = analogRead(1);       // read analog input pin 0
  Serial.print("Hydrogen Value: ");
  Serial.print(sensorValueH, DEC);    // prints the value read
  Serial.println(" ppm");
  sendNum1(sensorValueH, 10);
  ZBTxRequest zbTx1 = ZBTxRequest(addr64, dat1, sizeof(dat1));
  xbee.send(zbTx1);
  delay(1000);
  
  sensorValueM = analogRead(0);       // read analog input pin 0
  Serial.print("Methane Value: ");
  Serial.print(sensorValueM, DEC);    // prints the value read
  Serial.println(" ppm");
  sendNum2(sensorValueM, 11);
  ZBTxRequest zbTx2 = ZBTxRequest(addr64, dat2, sizeof(dat2));
  xbee.send(zbTx2);
  delay(1000);
  
  float pressure = myPressure.readPressure();
  pressure/=1000;
  Serial.print("Pressure(kPa): ");
  Serial.print(pressure, 2);
  Serial.println();
   val = analogRead(pressure);  
   sendNum3(pressure*10, 12);
  ZBTxRequest zbTx3 = ZBTxRequest(addr64, dat3, sizeof(dat3));
  xbee.send(zbTx3);
  delay(1000);
  
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();

  Serial.print("Temperature:");
  Serial.print(temp, 1);
  Serial.println("C, ");
  sendNum5(temp*10, 14);
  ZBTxRequest zbTx5 = ZBTxRequest(addr64, dat5, sizeof(dat5));
  xbee.send(zbTx5);
  delay(1000);
  
  Serial.print("Humidity:");
  Serial.print(humd, 1);
  Serial.print("%");
  sendNum4(humd*10, 13);
  ZBTxRequest zbTx4 = ZBTxRequest(addr64, dat4, sizeof(dat4));
  xbee.send(zbTx4);
  
  delay(1000);
  Serial.println();
  Serial.println();
  delay(1000); 
}

void sendNum0(int num, int sensor){
  dat0[0] = sensor;  
  if(num < 0){
    dat0[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat0[2] = 0;
    dat0[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat0[2] = num2;
    dat0[3] = num3;
 }
}
void sendNum1(int num, int sensor){
  dat1[0] = sensor;  
  if(num < 0){
    dat1[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat1[2] = 0;
    dat1[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat1[2] = num2;
    dat1[3] = num3;
 }
}

void sendNum2(int num, int sensor){
  dat2[0] = sensor;  
  if(num < 0){
    dat2[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat2[2] = 0;
    dat2[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat2[2] = num2;
    dat2[3] = num3;
 }
}
void sendNum3(int num, int sensor){
  dat3[0] = sensor;  
  if(num < 0){
    dat3[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat3[2] = 0;
    dat3[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat3[2] = num2;
    dat3[3] = num3;
 }
}

void sendNum4(int num, int sensor){
  dat4[0] = sensor;  
  if(num < 0){
    dat4[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat4[2] = 0;
    dat4[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat4[2] = num2;
    dat4[3] = num3;
 }
}
void sendNum5(int num, int sensor){
  dat5[0] = sensor;  
  if(num < 0){
    dat5[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat5[2] = 0;
    dat5[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat5[2] = num2;
    dat5[3] = num3;
 }
}


