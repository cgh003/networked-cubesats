
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <XBee.h>
#include <Wire.h> //I2C Arduino Library

/*
 This example uses software serial and the TinyGPS++ library by Mikal Hart
 Based on TinyGPSPlus/DeviceExample.ino by Mikal Hart
 Modified by acavis
*/

#include <SparkFunTSL2561.h>



// Choose two Arduino pins to use for software serial
// The GPS Shield uses D2 and D3 by default when in DLINE mode
int RXPin = 2;
int TXPin = 3;

//Hardware pin definitions
int UVOUT = A0; //Output from the sensor
int REF_3V3 = A1; //3.3V power on the Arduino board


// The Skytaq EM-506 GPS module included in the GPS Shield Kit
// uses 4800 baud by default
int GPSBaud = 4800;

// Create a TinyGPS++ object called "gps"
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

// Create an SFE_TSL2561 object, here called "light":

SFE_TSL2561 light;

// Global variables:

boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds

#define address 0x1E //0011110b, I2C 7bit address of HMC5883
XBee xbee = XBee();
int num, num2, num3;
uint8_t data[] = {0,0,0,0};
uint8_t dat0[] = {0,0,0,0};
uint8_t dat1[] = {0,0,0,0};
uint8_t dat2[] = {0,0,0,0};
uint8_t dat3[] = {0,0,0,0};
uint8_t dat4[] = {0,0,0,0};
uint8_t dat5[] = {0,0,0,0};
uint8_t dat6[] = {0,0,0,0,0};
uint8_t dat7[] = {0,0,0,0};
uint8_t dat8[] = {0,0,0,0,0};
void setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);
  xbee.setSerial(Serial);
  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);

  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);

  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();

  // Initialize the SFE_TSL2561 library

  // You can pass nothing to light.begin() for the default I2C address (0x39),
  // or use one of the following presets if you have changed
  // the ADDR jumper on the board:
  
  // TSL2561_ADDR_0 address with '0' shorted on board (0x29)
  // TSL2561_ADDR   default address (0x39)
  // TSL2561_ADDR_1 address with '1' shorted on board (0x49)

  // For more information see the hookup guide at: https://learn.sparkfun.com/tutorials/getting-started-with-the-tsl2561-luminosity-sensor

  light.begin();

  // Get factory ID from sensor:
  // (Just for fun, you don't need to do this to operate the sensor)

  unsigned char ID;
  
  if (light.getID(ID))
  {
    Serial.print("Got factory ID: 0X");
    Serial.print(ID,HEX);
    Serial.println(", should be 0X5X");
  }
  // Most library commands will return true if communications was successful,
  // and false if there was a problem. You can ignore this returned value,
  // or check whether a command worked correctly and retrieve an error code:
  else
  {
    byte error = light.getError();
    printError(error);
  }

  // The light sensor has a default integration time of 402ms,
  // and a default gain of low (1X).
  
  // If you would like to change either of these, you can
  // do so using the setTiming() command.
  
  // If gain = false (0), device is set to low gain (1X)
  // If gain = high (1), device is set to high gain (16X)

  gain = 0;

  // If time = 0, integration will be 13.7ms
  // If time = 1, integration will be 101ms
  // If time = 2, integration will be 402ms
  // If time = 3, use manual start / stop to perform your own integration

  unsigned char time = 2;

  Serial.println("Welcome to Radiation Group Data!");
  delay(2000);
  // setTiming() will set the third parameter (ms) to the
  // requested integration time in ms (this will be useful later):
  
  Serial.println("Set timing...");
  light.setTiming(gain,time,ms);

  // To start taking measurements, power up the sensor:
  
  Serial.println("Powerup...");
  light.setPowerUp();
  
  // The sensor will now gather light during the integration time.
  // After the specified time, you can retrieve the result from the sensor.
  // Once a measurement occurs, another integration period will start.

 
//  Serial.println(F("           Latitude   Longitude           Time   "));
//  Serial.println(F("            (deg)      (deg)  "));
//  Serial.println(F("           -------------------------------------------"));
//  Serial.println();
}

void loop()
{  
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected"));
    while(true);
  }
}

void displayInfo()
{
  XBeeAddress64 addr64 = XBeeAddress64();
  addr64.setMsb(0x0013a200);//XXXXX -> Msb address of router/end node
  addr64.setLsb(0x40b450ee);//XXXXX -> Lsb address of router/end node 
  
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    float lat = gps.location.lat();
    int decimals;
    int digits;
    //float lat = -37.0043;
    if(lat > 0){
    digits = (int)(lat);
    decimals = (lat+1 - digits)*10000;
    }else{
      digits = (int)(lat);
      decimals = (lat - digits-1)*-10000;
    }
    
    
    sendNum5(digits, 5);
    ZBTxRequest zbTx5 = ZBTxRequest(addr64, dat5, sizeof(dat5));
    xbee.send(zbTx5);
    delay(200);
    String str = (String)decimals;
   
    int j = 0;
    int i = 1;
    while(str.charAt(i) == '0'){
     j = i;
     i++;
     Serial.println(i);
    }
  
    String newstr = str.substring(j+1); 

    int tosend = atoi(newstr.c_str());
    Serial.print("decimals: ");
    Serial.println(tosend);
    sendNum6(tosend, 6, j);
    Serial.print("numZeros: ");
    Serial.println(dat6[4]);
    ZBTxRequest zbTx6 = ZBTxRequest(addr64, dat6, sizeof(dat6));
    xbee.send(zbTx6);
    //delay(200);
    
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 8);
    float lng = gps.location.lng();
    //float lng = 120.0456;
    int decimalsl;
    int digitsl;
    if(lng > 0){
    digitsl = (int)(lng);
    decimalsl = (lng+1 - digitsl)*10000;
    }else{
      digitsl = (int)(lng);
      decimalsl = (lng - digitsl-1)*-10000;
    }
    
    sendNum7(digitsl, 7);
    ZBTxRequest zbTx7 = ZBTxRequest(addr64, dat7, sizeof(dat7));
    xbee.send(zbTx7);
    delay(200);

       String strl = (String)decimalsl;
    int jl = 0;
    int il = 1;
    while(strl.charAt(il) == '0'){
     jl = il;
     il++;
    }
  
    String newstrl = strl.substring(jl+1); 
    int tosendl = atoi(newstrl.c_str());
   
    sendNum8(tosendl, 8, jl);
   
    ZBTxRequest zbTx8 = ZBTxRequest(addr64, dat8, sizeof(dat8));
    xbee.send(zbTx8);
   // delay(200);
  }
  else
 {
  sendNum5(0, 5);
    ZBTxRequest zbTx5 = ZBTxRequest(addr64, dat5, sizeof(dat5));
    xbee.send(zbTx5);
  sendNum6(0, 6, 0);
    ZBTxRequest zbTx6 = ZBTxRequest(addr64, dat6, sizeof(dat6));
    xbee.send(zbTx6);
   sendNum7(0, 7);
    ZBTxRequest zbTx7 = ZBTxRequest(addr64, dat7, sizeof(dat7));
    xbee.send(zbTx7);
    sendNum8(0, 8, 0);
    ZBTxRequest zbTx8 = ZBTxRequest(addr64, dat8, sizeof(dat8));
    xbee.send(zbTx8);
 }

//  Serial.print(F("  Time: "));
//  if (gps.date.isValid())
//  {
//    Serial.print(gps.date.month());
//    Serial.print(F("/"));
//    Serial.print(gps.date.day());
//    Serial.print(F("/"));
//    Serial.print(gps.date.year());
//  }
//  else
//  {
//    Serial.print(F("INVALID"));
//  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());

    Serial.print(" UT");
  }
  else
  {
    Serial.print(F("INVALID"));
  }
//  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  Serial.println();
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level

  Serial.print("output: ");
  Serial.print(refLevel);

  Serial.print("ML8511 output: ");
  Serial.print(uvLevel);

  Serial.print(" / ML8511 voltage: ");
  Serial.print(outputVoltage);

  Serial.print(" / UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);
  sendNum4(uvIntensity*100, 4);
  ZBTxRequest zbTx4 = ZBTxRequest(addr64, dat4, sizeof(dat4));
  xbee.send(zbTx4);
  delay(200);
  
  Serial.println();
  
  delay(200);

  int x,y,z; //triple axis data

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  sendNum(x,0);
  sendNum1(y,1);
  sendNum2(z,2);

 
  ZBTxRequest zbTx = ZBTxRequest(addr64, dat0, sizeof(data));
  xbee.send(zbTx);
  delay(200);
  ZBTxRequest zbTx1 = ZBTxRequest(addr64, dat1, sizeof(data));
  xbee.send(zbTx1);
  delay(200);
  ZBTxRequest zbTx2 = ZBTxRequest(addr64, dat2, sizeof(data));
  xbee.send(zbTx2);
 delay(200);
 
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
 delay(200);
  Serial.println();
  // Wait between measurements before retrieving the result
  // (You can also configure the sensor to issue an interrupt
  // when measurements are complete)
  
  // This sketch uses the TSL2561's built-in integration timer.
  // You can also perform your own manual integration timing
  // by setting "time" to 3 (manual) in setTiming(),
  // then performing a manualStart() and a manualStop() as in the below
  // commented statements:
  
//   ms = 1000;
//   light.manualStart();
//   delay(ms);
//   light.manualStop();
  
  // Once integration is complete, we'll retrieve the data.
  
  // There are two light sensors on the device, one for visible light
  // and one for infrared. Both sensors are needed for lux calculations.
  
  // Retrieve the data from the device:

  unsigned int data0, data1;
  
  if (light.getData(data0,data1))
  {
    // getData() returned true, communication was successful

  
    // To calculate lux, pass all your settings and readings
    // to the getLux() function.
    
    // The getLux() function will return 1 if the calculation
    // was successful, or 0 if one or both of the sensors was
    // saturated (too much light). If this happens, you can
    // reduce the integration time and/or gain.
    // For more information see the hookup guide at: https://learn.sparkfun.com/tutorials/getting-started-with-the-tsl2561-luminosity-sensor
  
    double lux;    // Resulting lux value
    boolean good;  // True if neither sensor is saturated
    
    // Perform lux calculation:

    good = light.getLux(gain,ms,data0,data1,lux);
    
    // Print out the results:
  
    Serial.print(" lux: ");
    Serial.print(lux);
    sendNum3(lux*100,3);
  ZBTxRequest zbTx3 = ZBTxRequest(addr64, dat3, sizeof(dat3));
  xbee.send(zbTx3);
  delay(200);
    if (good) Serial.println(" (good)"); else Serial.println(" (BAD)");
  }
  else
  {
    // getData() returned false because of an I2C error, inform the user.

    byte error = light.getError();
    printError(error);
  }
  
  
  
  //delay(5000);
}
//
//static void printFloat(float val, bool valid, int len, int prec)
//{
//  if (!valid)
//  {
//    while (len-- > 1)
//      Serial.print('*');
//    Serial.print(' ');
//  }
// else
//  {
//    Serial.print(val, prec);
//    int vi = abs((int)val);
//    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
//    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
//    for (int i=flen; i<len; ++i)
//      Serial.print(' ');
//  }
//  
//}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void printError(byte error)
  // If there's an I2C error, this function will
  // print out an explanation.
{
  Serial.print("I2C error: ");
  Serial.print(error,DEC);
  Serial.print(", ");
  
  switch(error)
  {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
}

void sendNum(int num, int sensor){
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
void sendNum6(int num, int sensor, int zeros){
  dat6[0] = sensor; 
  dat6[4] = zeros; 
  if(num < 0){
    dat6[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat6[2] = 0;
    dat6[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat6[2] = num2;
    dat6[3] = num3;
 }
}
void sendNum7(int num, int sensor){
  dat7[0] = sensor;  
  if(num < 0){
    dat7[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat7[2] = 0;
    dat7[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat7[2] = num2;
    dat7[3] = num3;
 }
}
void sendNum8(int num, int sensor, int zeros){
  dat8[0] = sensor; 
  dat8[4] = zeros; 
  if(num < 0){
    dat8[1] = 1;
    num*=-1;
  }

  if(num < 255){
    dat8[2] = 0;
    dat8[3] = num;
  }else{
    num2 = num / 255;
    num3 = num % 255;
    dat8[2] = num2;
    dat8[3] = num3;
 }
}
