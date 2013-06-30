#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, 6, NEO_GRB + NEO_KHZ800);

int pinRangeStart = 0;
int pinRangeStop = 0;
char inByte;
uint8_t* colorBytes;

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
    case('t'): {
        colorBytes = new uint8_t[4];
        colorBytes[0] = Serial.parseInt(); //Red
        Serial.print("R=");
        Serial.println(colorBytes[0]);
        Serial.read();
        colorBytes[1] = Serial.parseInt(); //Green
        Serial.print("G=");
        Serial.println(colorBytes[1]);
        Serial.read();
        colorBytes[2] = Serial.parseInt(); //Blue
        Serial.print("B=");
        Serial.println(colorBytes[2]);   
        Serial.read();
        colorBytes[3] = Serial.parseInt();
        Serial.print("LED=");
        Serial.println(colorBytes[3]);

      uint32_t color = strip.Color(colorBytes[0],colorBytes[1],colorBytes[2]);  
      strip.setPixelColor(colorBytes[3], color);
      strip.show();
      break;
    }
  }
  }  
}
