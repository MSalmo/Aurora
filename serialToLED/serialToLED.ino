#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, 6, NEO_GRB + NEO_KHZ800);

int pinRangeStart = 0;
int pinRangeStop = 0;
char inByte;
uint8_t* colorBytes;

void setup(){
  Serial.begin(115200);
  while(!Serial);
  
  Serial.print("Desktop LED Ambience\n");
  
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

      colorShiftTo(colorBytes, 12);  
      break;
    }
    case('r'): {
      for(int i = 0 ; i < strip.numPixels(); i++)
       strip.setPixelColor(i, strip.Color(0,0,0));
       strip.show();
       Serial.println("Reset!");
      break;
    }
  }
  }  
}
void colorShiftTo(uint8_t* colorInfo, int mSecs){
  uint32_t curColor = strip.getPixelColor(colorInfo[3]);
  
  uint8_t *oldCols = new uint8_t[3];
  uint8_t *deltas = new uint8_t[3];
  
  oldCols[2] = curColor % 256;        //Old Blue Value
  deltas[2] = abs(colorInfo[2] - oldCols[2]);
  
  oldCols[1] = (curColor >> 8) % 256; //Old Green Value
  deltas[1] = abs(colorInfo[1] - oldCols[1]);
  
  oldCols[0] = (curColor >> 16) % 256;//Old Red Value
  deltas[0] = abs(colorInfo[0] - oldCols[0]);
  Serial.print("OldRED=");
  Serial.print(oldCols[2]);
  Serial.print(" OldGREEN=");
  Serial.print(oldCols[1]);
  Serial.print(" OldBLUE=");
  Serial.println(oldCols[0]);
  
  uint8_t closest = min(min(deltas[0],deltas[1]),deltas[2]);
  
  float carryValB = (deltas[0]/closest) - 1.0;
  float carryValG = (deltas[1]/closest) - 1.0;
  float carryValR = (deltas[2]/closest) - 1.0;
  Serial.print("CarryVal(Red)=");
  Serial.print(carryValR);
  Serial.print(" CarryVal(Green)=");
  Serial.print(carryValG);
  Serial.print(" CarryVal(Blue)=");
  Serial.println(carryValB);
  
  float toSkipB = 0.0f;
  float toSkipG = 0.0f;
  float toSkipR = 0.0f;
  uint32_t targetColor = strip.Color(colorInfo[0], colorInfo[1], colorInfo[2]);
  while( targetColor != strip.getPixelColor(colorInfo[3])){
    if(colorInfo[0] != oldCols[0]){
      if(colorInfo[0] - oldCols[0] < 1)
          oldCols[0]--;
        else
          oldCols[0]++;
    
      toSkipB += carryValB;
    
      if(toSkipB > 1.0){
        if(colorInfo[0] - oldCols[0] < 1)
          oldCols[0]--;
        else
          oldCols[0]++;
        toSkipB -= 1.0;
      }
    }
    if(colorInfo[1] != oldCols[1]){
      if(colorInfo[1] - oldCols[1] < 1)
          oldCols[1]--;
        else
          oldCols[1]++;
    
      toSkipG += carryValG;
      if(toSkipG > 1.0){
        if(colorInfo[1] - oldCols[1] < 1)
          oldCols[1]--;
        else
          oldCols[1]++;
        toSkipG -= 1.0;
      }    
    }
    if(colorInfo[2] != oldCols[2]){
      if(colorInfo[2] - oldCols[2] < 1)
          oldCols[2]--;
        else
          oldCols[2]++;
    
      toSkipR += carryValR;
    
      if(toSkipR > 1.0){
        if(colorInfo[0] - oldCols[2] < 1)
          oldCols[0]--;
        else
          oldCols[2]++;
        toSkipR -= 1.0;
      }
    }
    Serial.print("NewRED=");
    Serial.print(oldCols[0]);
    Serial.print(" NewGREEN=");
    Serial.print(oldCols[1]);
    Serial.print(" NewBLUE=");
    Serial.println(oldCols[2]);
    
    uint32_t newColor = strip.Color(oldCols[0], oldCols[1], oldCols[2]);
    strip.setPixelColor(colorInfo[3], newColor);
    strip.show();
    delay(mSecs);
  } 
}


