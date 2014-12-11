#include "LEDStrip.h"

LEDStrip ledStrip = LEDStrip(240, 6);

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
      while(!Serial.available())ledStrip.processStep();
      inByte = Serial.read();
      delay(1);
      switch(inByte){
        case('t'): { //Invoke the blend algorithm on a LED
          colorBytes = new byte[4];
          
          for(int i = 0 ; i < 4; i++){
            while(!Serial.available()) ledStrip.processStep();
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
	  ledStrip.setLEDtoColor((uint8_t)colorBytes[3],
				ledStrip.Color(colorBytes[0], colorBytes[1], colorBytes[2]));
			 delay(1);
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
  Serial.println("Done!");
  Serial.flush();
}


