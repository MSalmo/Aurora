#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, 6, NEO_GRB + NEO_KHZ800);

int pinRangeStart = 0;
int pinRangeStop = 0;
char inByte;
uint8_t ledAddr;
uint16_t *colorInfo;

void setup(){
  Serial.begin(115200);
  while(!Serial);
  
  Serial.print("Desktop LED Ambience");
  
  strip.begin();
  strip.show();
  
  

}
void loop(){
while(Serial.available() > 0){
    inByte = Serial.read();
    switch(inByte){
      case 'a': //Set start pin
        pinRangeStart = Serial.read();
        break;
      case 'b': //Set stop pin
        pinRangeStop = Serial.read();
        if(pinRangeStart && pinRangeStop){
          if(pinRangeStop < pinRangeStart){
            int temp = pinRangeStop;
            pinRangeStop = pinRangeStart;
            pinRangeStart = temp;
          }
          break;
        }
      case 't': //Test case (light a single LED on the strip with a certain color)
        colorInfo = new uint16_t[3];
        ledAddr = Serial.read();
        
        colorInfo[0] = Serial.read(); //Red
        colorInfo[1] = Serial.read(); //Green
        colorInfo[2] = Serial.read(); //Blue
        
        strip.setColorAtPixel(ledAddr, strip.Color(colorInfo[0], colorInfo[1], colorInfo[2]));
        
        break;
    }
  }  
}
