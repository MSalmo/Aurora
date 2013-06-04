#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_Neopixel(240, 6, NEO_GRB + NEO_KHZ800);

int pinRangeStart = 0;
int pinRangeStop = 0;
int inByte;

void setup(){
  Serial.begin(9600);
  while(!Serial);
  
  while(Serial.available() > 0){
    inByte = analogRead(A0);
    if(inByte == 'a')
      pinRangeStart = analogRead(A0);
    else if(inByte == 'b')
      pinRangeStop = analogRead(A0);
    if(pinRangeStart && pinRangeStop){
      if(pinRangeStop < pinRangeStart){
        int temp = pinRangeStop;
        pinRangeStop = pinRangeStart;
        pinRangeStart = temp;
      }
      break;
    }
  }
  
  strip.begin();
  strip.show();
}
void loop(){
  
}
