#include <XBee.h>
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
int count = 0;
String identifier;

int ROW = 0;
int LABEL = 1;
int val = 0;
//Radiation
int x, y, z, beforeLat, afterLat, beforeLon, afterLon, lonZeroes, latZeroes;
float lux, uvIntensity;

//Weather
int COvalue, Hvalue, Mvalue;
float pressure, temperatureF, temperatureC, humidity;

boolean gotX, gotY, gotZ, gotBeforeLat, gotBeforeLon, gotAfterLat, gotAfterLon, gotLux, gotUv;
boolean gotCO, gotH, gotM, gotPressure, gotTemp, gotHumidity;
boolean gotAllData = gotX && gotY && gotZ && gotLux && gotUv && gotBeforeLat && gotBeforeLon && gotCO && gotH && gotM && gotPressure && gotTemp && gotHumidity;
  



void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, x, y, z, Lux, UV Intensity, Latitude, Longtitude, CO, Hydrogen, Methane, Pressure, Temp (C), Temp (F), Humidity");
  xbee.begin(Serial);

  
  
}
void loop() {
  int readingMSB, readingLSB, combinedNum;
  float floatNum;
  xbee.readPacket(1000); 
  xbee.getResponse().getZBRxResponse(rx);
 // Serial.println(rx.getDataLength());
  if(gotAllData == true || count == 25){
    count = 0;

    gotX = false, gotY = false, gotZ = false, gotBeforeLat = false, gotBeforeLon = false, 
    gotAfterLat = false, gotAfterLon = false, gotUv = false, gotLux = false, gotCO = false,
    gotH = false, gotM = false, gotPressure = false, gotTemp = false, gotHumidity = false;
    gotAllData = false;

    if(true){
      Serial.print("x: ");
      Serial.print(x);
      Serial.print(" y: ");
      Serial.print(y);
      Serial.print(" z: ");
      Serial.println(z);
      Serial.print("lux: ");
      Serial.println(lux);
      Serial.print("UV Intensity: ");
      Serial.println(uvIntensity);
       Serial.print("Latitude: ");
      Serial.print(beforeLat);
       Serial.print(".");
            while(latZeroes > 0){
              Serial.print("0");
              latZeroes--;
            }
            Serial.println(afterLat);
           Serial.print("Longitude: ");
      Serial.print(beforeLon);
       Serial.print(".");
            while(lonZeroes > 0){
              Serial.print("0");
              lonZeroes--;
            }
            Serial.println(afterLon);
      Serial.println();
      
      //Serial.println("---WEATHER---");
      Serial.print("CO Value: ");
      Serial.println(COvalue);
      Serial.print("H Value: ");
      Serial.println(Hvalue);
      Serial.print("M value: " );
      Serial.println(Mvalue);
        Serial.print("Pressure (kPa): ");
      Serial.println(pressure);
      Serial.print("Temp (F): ");
      Serial.println(temperatureF);
      Serial.print("Humidity: ");
      Serial.println(humidity);




//    Serial.print("DATA, TIME,");
//    Serial.print(x);
//    Serial.print(",");  
//    Serial.print(y);
//    Serial.print(",");  
//    Serial.print(z);
//    Serial.print(",");  
//    Serial.print(lux);
//    Serial.print(",");  
//    Serial.print(uvIntensity);
//    Serial.print(",");      
//    Serial.print(beforeLat);
//    Serial.print(".");
//          while(latZeroes > 0){
//            Serial.print("0");
//            latZeroes--;
//          }
//          Serial.print(afterLat);
//    Serial.print(",");     
//    Serial.print(beforeLon);
//    Serial.print(".");
//          while(lonZeroes > 0){
//            Serial.print("0");
//            lonZeroes--;
//          }
//          Serial.print(afterLon);
//           
//    Serial.print(",");  
//    Serial.print(COvalue);
//    Serial.print(",");       
//    Serial.print(Hvalue);
//    Serial.print(",");  
//    Serial.print(Mvalue);
//    Serial.print(",");       
//    Serial.print(pressure);
//    Serial.print(",");  
//    Serial.print(temperatureC);
//    Serial.print(",");       
//    Serial.print(temperatureF);
//    Serial.print(",");       
//    Serial.print(humidity);
//    
// 
//    Serial.println(ROW);
//    ROW++;
   
              }


 
  }

   if(rx.getDataLength() == 11){
    
       if(rx.getData(rx.getDataLength()-5) == 6)
          identifier = "afterlat";
      else if(rx.getData(rx.getDataLength()-5) == 8)
          identifier = "afterlon";
  
      if(identifier == "afterlat"){
          if(rx.getData(rx.getDataLength()-4) == 0 && rx.getDataLength() == 11){
           readingMSB = rx.getData(rx.getDataLength() - 3);
            readingLSB = rx.getData(rx.getDataLength() - 2);
            afterLat = (readingMSB*255+readingLSB);
          }
            latZeroes = rx.getData(rx.getDataLength() - 1);
       
//            Serial.print("latZeroes: ");
//           Serial.println(latZeroes);
//           Serial.print("afterLat: ");
//            Serial.println(afterLat);
            //Serial.println(identifier);
            gotAfterLat = true;
            count++;
      }else if(identifier == "afterlon" ){
          if(rx.getData(rx.getDataLength()-4) == 0 && rx.getDataLength() == 11){
           readingMSB = rx.getData(rx.getDataLength() - 3);
            readingLSB = rx.getData(rx.getDataLength() - 2);
            afterLon = (readingMSB*255+readingLSB);
          }
            lonZeroes = rx.getData(rx.getDataLength() - 1);
    
//           Serial.print("lonZeroes: ");
//            Serial.println(lonZeroes);
//           Serial.print("afterLon: ");
//            Serial.println(afterLon);
            gotAfterLon = true;
            count++;
          }

  }
     
        
          
 

  
  //Serial.println(rx.getDataLength());
  if(rx.getDataLength() == 10){
    if(rx.getData(rx.getDataLength()-4) == 0)
      identifier = "x";
    else if(rx.getData(rx.getDataLength()-4) == 1)
      identifier = "y";
    else if(rx.getData(rx.getDataLength()-4) == 2)
      identifier = "z";
    else if(rx.getData(rx.getDataLength()-4) == 3)
      identifier = "lux";
    else if(rx.getData(rx.getDataLength()-4) == 4)
      identifier = "UV intensity";
    else if(rx.getData(rx.getDataLength()-4) == 5)
      identifier = "beforelat";
    else if(rx.getData(rx.getDataLength()-4) == 7)
      identifier = "beforelon";
    else if(rx.getData(rx.getDataLength()-4) == 9)
      identifier = "COvalue";
    else if(rx.getData(rx.getDataLength()-4) == 10)
      identifier = "Hvalue";
    else if(rx.getData(rx.getDataLength()-4) == 11)
      identifier = "Mvalue";

    else if(rx.getData(rx.getDataLength()-4) == 12)
      identifier = "pressure";
    else if(rx.getData(rx.getDataLength()-4) == 13)
      identifier = "humidity";
    else if(rx.getData(rx.getDataLength()-4) == 14)
      identifier = "tempC";
    
    
      
  
          if(identifier == "lux"){
            if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            lux = (float)((readingMSB*255+readingLSB)/100.0);
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            lux = (float)(-(readingMSB*255+readingLSB)/100.0);
          }

           
//            Serial.print("lux: ");
//            Serial.println(lux);
            gotLux = true;
          }
          else if(identifier == "UV intensity"){
              if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            uvIntensity = (float)((readingMSB*255+readingLSB)/100.0);
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            uvIntensity = (float)(-(readingMSB*255+readingLSB)/100.0);
          }

            
//            Serial.print("UV intensity: ");
//            Serial.println(uvIntensity);
            gotUv = true;
       
          }
          else if(identifier == "tempC"){
            if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            temperatureC = (float)((readingMSB*255+readingLSB)/10.0);
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            temperatureC = (float)(-(readingMSB*255+readingLSB)/10.0);
          }

          
            temperatureF = (temperatureC*9.0/5.0) + 32.0;
//            Serial.print("tempC: ");
//            Serial.println(temperatureC);
            gotTemp = true;
            
          }
         else  if(identifier == "humidity"){
            if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            humidity = (float)((readingMSB*255+readingLSB)/10.0);
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            humidity = (float)(-(readingMSB*255+readingLSB)/10.0);
          }

           
//            Serial.print("humidity: ");
//            Serial.println(humidity);
            gotHumidity = true;
          }
          else if(identifier == "pressure"){
               if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            pressure = (float)((readingMSB*255+readingLSB)/10.0);
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            pressure = (float)(-(readingMSB*255+readingLSB)/10.0);
          }

           
//            Serial.print("pressure: ");
//            Serial.println(pressure);
            gotPressure = true;
          }
         else  if(identifier == "COvalue"){
          if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
           COvalue = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            COvalue = -(readingMSB*255+readingLSB);
          }

           
//            Serial.print("CO value");
//            Serial.println(COvalue);
            gotCO = true;
          }
          else if(identifier == "Hvalue"){
            if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            Hvalue = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            Hvalue = -(readingMSB*255+readingLSB);
          }

   
//            Serial.print("Hvalue");
//            Serial.println(Hvalue);
            gotH = true;
          }
         else if(identifier == "Mvalue"){if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            Mvalue = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            Mvalue = -(readingMSB*255+readingLSB);
          }

          
//            Serial.print("mvalue");
//            Serial.println(Mvalue);
            gotM = true;
          }
          

           //count++;
          }
          
      //  if(identifier == "x" || identifier == "y" || identifier == "z" || identifier == "beforelat"
        //        || identifier == "afterlat"    || identifier == "beforelon" || identifier == "afterlon") 
        //  Serial.println(identifier  + ": " + combinedNum);

          if(identifier == "x"){
           if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            x = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            x = -(readingMSB*255+readingLSB);
          }
            gotX = true;
                count++;
          }else if(identifier == "y"){
            if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            y = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            y = -(readingMSB*255+readingLSB);
          }
            gotY = true;
                count++;
          }else if(identifier == "z"){   
            if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            z = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            z = -(readingMSB*255+readingLSB);
          }
            gotZ = true;
                 count++;
          }else if(identifier == "beforelat"){
            if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            beforeLat = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            beforeLat = -(readingMSB*255+readingLSB);
          }
           // Serial.println(beforeLat);
            gotBeforeLat = true;
            count++;
          }else if(identifier == "beforelon"){
           if(rx.getData(rx.getDataLength()-3) == 0 && rx.getDataLength() == 10){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            beforeLon = readingMSB*255+readingLSB;
          }
        else if(rx.getData(rx.getDataLength()-3) == 1 && rx.getDataLength() == 10){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            beforeLon = -(readingMSB*255+readingLSB);
          }
           // Serial.println(beforeLon);
            gotBeforeLon = true;
            count++;
  }

 
      
 gotAllData = gotX && gotY && gotZ && gotLux && gotUv && gotBeforeLat && gotBeforeLon && gotCO && gotH && gotM && gotPressure && gotTemp && gotHumidity;
//  Serial.println(gotAfterLon);
//  Serial.println(gotAfterLat);
//  Serial.println(gotBeforeLon);
//  Serial.println(gotBeforeLat);
//  Serial.println(gotX);
//  Serial.println(gotY);
//  Serial.println(gotZ);
//  Serial.println(gotUv);
//  Serial.println(gotLux);
//  Serial.println(gotCO);
//   Serial.println(gotH);
//  Serial.println(gotM);
//  Serial.println(gotPressure);
//  Serial.println(gotTemp);
//  Serial.println(gotHumidity);
//  Serial.println();
  count++;
  
  }     
    



