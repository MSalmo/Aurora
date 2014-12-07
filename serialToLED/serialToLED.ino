#include "LEDStrip.h"

LEDStrip ledStrip = LEDStrip(240);

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
          //for(int i = 0 ; i < strip.numPixels(); i++)
          //  strip.setPixelColor(i, strip.Color(0,0,0));
          //strip.show();
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
          //uint32_t newColor = strip.Color(colorBytes[0], colorBytes[1], colorBytes[2]);
          //strip.setPixelColor(colorBytes[3], newColor);
          free(colorBytes);
          break;
        }
        case('z'): { //Update the LEDs with any new values in the buffer.
          //strip.show();
          Serial.println("Updating Lights");
          Serial.flush();
          delay(1);
          break;
        }
      }
    }
  }  
}

//Color shift algorithm that calculates the slope and processes the step.
//TODO: Deprecate and remove this function after the LEDStrip counterpart works.
void colorShiftTo(uint8_t* colorInfo, int mSecs){
  ledStrip.setTargetColor((uint32_t)colorInfo);
  ledStrip.setStepValues();

  if(debug){  
    //TODO: Add new debug info here for old/new/delta/step 
  }
  
  if(debug){
    //TODO: Add new debug info here for current step/carry
  }
  //uint32_t targetColor = strip.Color(colorInfo[0], colorInfo[1], colorInfo[2]);
  while( /*activeLED.tgtColorAsUINT32 != strip.getPixelColor(colorInfo[3])*/true){
    /*activeLED.processStep();*/
    if(debug){
      //TODO: Add new debug code here for new values after step change.
    } 
    //uint32_t newColor = strip.Color(activeLED.curColor[0], activeLED.curColor[1], activeLED.curColor[2]);
    //strip.setPixelColor(colorInfo[3], newColor);
    //strip.show();
    delay(mSecs);
  } 
  Serial.println("Done!");
  Serial.flush();
}


