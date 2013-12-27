#include <Adafruit_NeoPixel.h>
#include "Timer.h"

jjjAdafruit_NeoPixel strip = Adafruit_NeoPixel(240, 6, NEO_GRB + NEO_KHZ800);

int pinRangeStart = 0;
int pinRangeStop = 0;
char inByte;
byte* colorBytes;
boolean debug = false;

void setup(){
  Serial.begin(115200);
  while(!Serial);
  
  Serial.print("Desktop LED Ambience\n");
  Serial.setTimeout(1000);
  strip.begin();
  strip.show();
}

void loop(){  
  while(Serial.available() > 0){
    while(Serial.read() != 0x30);
    Serial.print("Start Byte read!");
    
    while(true){
      while(!Serial.available());
      inByte = Serial.read();
      delay(1);
      switch(inByte){
        case('t'): { //Invoke the blend algorithm on a LED
          colorBytes = new byte[4];
          
          for(int i = 0 ; i < 4; i++){
            while(!Serial.available());
            colorBytes[0] = Serial.read();
            delay(1);
            Serial.flush();
          }
          if(debug){
            Serial.print("R=");
            Serial.println(colorBytes[0]);
            Serial.print("G=");
            Serial.println(colorBytes[1]);
            Serial.print("B=");
            Serial.println(colorBytes[2]);
            Serial.print("LED=");
            Serial.println(colorBytes[3]);
          }
          colorShiftTo(colorBytes, 12);  
          free(colorBytes);
          break;
        }
        case('r'): { //Reset all LEDs to (R,G,B)=(0,0,0)
          for(int i = 0 ; i < strip.numPixels(); i++)
            strip.setPixelColor(i, strip.Color(0,0,0));
          strip.show();
          Serial.println("Reset!");
          Serial.flush();
          break;
        }
        case('d'): { //Enable or disable debug flag.
          Serial.print("Debugging ");
          debug =! debug;
          if(!debug)  
            Serial.println("DISABLED");
          else
            Serial.println("ENABLED");
          break;
        }
        case('s'): { //Update the colors of an LED in the buffer.
          colorBytes = new byte[4];
          for (int i = 0 ; i < 4 ; i++){
            while(!Serial.available());
            colorBytes[i]= Serial.read();
            delay(1);
            
        }

          if(debug){
            Serial.println("Set lights without updating.");
            Serial.print("R=");
            Serial.println(colorBytes[0]);
            Serial.print("G=");
            Serial.println(colorBytes[1]);
            Serial.print("B=");
            Serial.println(colorBytes[2]);
            Serial.print("LED=");
            Serial.println(colorBytes[3]);
          }
          uint32_t newColor = strip.Color(colorBytes[0], colorBytes[1], colorBytes[2]);
          strip.setPixelColor(colorBytes[3], newColor);
          free(colorBytes);
          break;
        }
        case('z'): { //Update the LEDs with any new values in the buffer.
          strip.show();
          Serial.println("Updating Lights");
          Serial.flush();
          delay(1);
          break;
        }
      }
    }
  }  
}
void colorShiftTo(uint8_t* colorInfo, int mSecs){
  uint32_t curColor = strip.getPixelColor(colorInfo[3]);
  
  uint8_t *oldCols = new uint8_t[3];
  int *deltas = new int[3];
  
  oldCols[2] = curColor % 256;        //Old Blue Value
  deltas[2] = (int)colorInfo[2] - (int)oldCols[2];
  
  oldCols[1] = (curColor >> 8) % 256; //Old Green Value
  deltas[1] = (int)colorInfo[1] - (int)oldCols[1];
  
  oldCols[0] = (curColor >> 16) % 256;//Old Red Value
  deltas[0] = (int)colorInfo[0] - (int)oldCols[0];

  if(debug){  
    Serial.print("OldRED=");
    Serial.print(oldCols[0]);
    Serial.print(" OldGREEN=");
    Serial.print(oldCols[1]);
    Serial.print(" OldBLUE=");
    Serial.println(oldCols[2]);
 
    Serial.print("Target RED=");
    Serial.print(colorInfo[0]);
    Serial.print(" Target GREEN=");
    Serial.print(colorInfo[1]);
    Serial.print(" Target BLUE=");
    Serial.println(colorInfo[2]); 
  
    Serial.print("Delta RED=");
    Serial.print(deltas[0]);
    Serial.print(" Delta GREEN=");
    Serial.print(deltas[1]);
    Serial.print(" Delta BLUE=");
    Serial.println(deltas[2]); 
  }
  int absDelta0 = abs(deltas[0]);
  int absDelta1 = abs(deltas[1]);
  int absDelta2 = abs(deltas[2]);
  int farthest = max(max(absDelta0,absDelta1),absDelta2);
  
  Serial.print("Farthest delta=");
  Serial.println(farthest);
  
  //Flip the denom and the num, use modf to extract carryover.
  float carryValR = (1.0f*deltas[0]/farthest);
  float carryValG = (1.0f*deltas[1]/farthest); 
  float carryValB = (1.0f*deltas[2]/farthest);
  
  double stepR, stepG, stepB;
  
  carryValR = modf(carryValR, &stepR);
  carryValG = modf(carryValG, &stepG);
  carryValB = modf(carryValB, &stepB);
  if(carryValR < 0)
    stepR = 0 - stepR;
  if(carryValG < 0)
    stepG = 0 - stepG;
  if(carryValB < 0)
    stepB = 0 - stepB;
  if(debug){
    Serial.print("StepVal(Red)=");
    Serial.print(stepR);
    Serial.print(" StepVal(Green)=");
    Serial.print(stepG);
    Serial.print(" StepVal(Blue)=");
    Serial.println(stepB);
  
    Serial.print("CarryVal(Red)=");
    Serial.print(carryValR);
    Serial.print(" CarryVal(Green)=");
    Serial.print(carryValG);
    Serial.print(" CarryVal(Blue)=");
    Serial.println(carryValB);
  }
  double toSkipB = 0.0f;
  double toSkipG = 0.0f;
  double toSkipR = 0.0f;
  uint32_t targetColor = strip.Color(colorInfo[0], colorInfo[1], colorInfo[2]);
  while( targetColor != strip.getPixelColor(colorInfo[3])){
    if(colorInfo[0] != oldCols[0]){
      oldCols[0] = oldCols[0] + stepR;
      
      toSkipR += carryValR;
      if(toSkipR >= 1.0){
        oldCols[0]++;
        toSkipR--;
      }
      if(toSkipR <= -1.0){
        oldCols[0]--;
        toSkipR++;
      }
    }
    if(colorInfo[1] != oldCols[1]){
      oldCols[1] = oldCols[1] + stepG;
      toSkipG += carryValG;
      
      if(toSkipG >= 1.0){
        oldCols[1]++;
        toSkipG--;
      }
      if(toSkipG <= -1.0){
        oldCols[1]--;
        toSkipG++;
      }    
    }
    if(colorInfo[2] != oldCols[2]){
      oldCols[2] = oldCols[2] + stepB;
      
      toSkipB += carryValB;
    
      if(toSkipB >= 1.0){
        oldCols[2]++;
        toSkipB--;
      }
      if(toSkipB <= -1.0){
        oldCols[2]--;
        toSkipB++;
      }
    }
    if(debug){
      Serial.print("NewRED=");
      Serial.print(oldCols[0]);
      Serial.print(" NewGREEN=");
      Serial.print(oldCols[1]);
      Serial.print(" NewBLUE=");
      Serial.println(oldCols[2]);
    } 
    uint32_t newColor = strip.Color(oldCols[0], oldCols[1], oldCols[2]);
    strip.setPixelColor(colorInfo[3], newColor);
    strip.show();
    delay(mSecs);
  } 
  Serial.println("Done!");
  Serial.flush();
}


