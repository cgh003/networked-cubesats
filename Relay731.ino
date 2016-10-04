#include <XBee.h>
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
int count = 0;
uint8_t data[] = {0,0,0,0};
uint8_t datal[] = {0,0,0,0,0};
int num, num2, num3;
boolean flag, flagl;

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
 
  
}
void loop() {
 
  flag = true;
  flagl = true;
  
  int readingMSB, readingLSB, combinedNum;
  xbee.readPacket(); 
  xbee.getResponse().getZBRxResponse(rx);
    XBeeAddress64 addr64 = XBeeAddress64();
      addr64.setMsb(0x0013a200);
      addr64.setLsb(0x40b450eb);
 
//Serial.println(rx.getDataLength());
 /*if(rx.getDataLength() == 4){
         if(rx.getData(rx.getDataLength()-3) == 0){
            readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            combinedNum = readingMSB*255+readingLSB;
          }
          if(rx.getData(rx.getDataLength()-3) == 1){
           readingMSB = rx.getData(rx.getDataLength() - 2);
            readingLSB = rx.getData(rx.getDataLength() - 1);
            combinedNum = -(readingMSB*255+readingLSB);
          }
          Serial.println(combinedNum);
         
      }*/
     // if(count == 8)
if(rx.getDataLength() == 4 && flag && flagl){
    
        for(int i = 0; i<rx.getDataLength(); i++){
                data[i] = rx.getData(i);
         
         
        }
            ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));
      xbee.send(zbTx);
     }
     else if(rx.getDataLength() == 5){
      for(int i = 0; i<rx.getDataLength(); i++){
                datal[i] = rx.getData(i);
      }
        if(rx.getData(rx.getDataLength()-5) == 6 || rx.getData(rx.getDataLength()-5) == 8){
      ZBTxRequest zbTxl = ZBTxRequest(addr64, datal, sizeof(datal));
      xbee.send(zbTxl);
      }
      if(rx.getData(rx.getDataLength()-1) == 6)
        flag = true;
      if(rx.getData(rx.getDataLength()-1) == 8)
        flagl = true;
     }
      
     

   
   
  
}



