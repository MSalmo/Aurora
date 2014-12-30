#include <LEDStrip.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, 6, NEO_KHZ800 + NEO_RGB);
LEDStrip ledStrip;

int pinRangeStart = 0;
int pinRangeStop = 0;
char inByte;
byte* colorBytes;
boolean debug = false;

void setup(){
 	strip.begin();
	strip.show();

	ledStrip = LEDStrip(240, 6, &strip);
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
						while(!Serial.available()) 
							ledStrip.processStep();

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
						ledStrip.Color(colorBytes[0], 
								colorBytes[1], 
								colorBytes[2]));
			 		delay(1);
			 		free(colorBytes);
			 		break;
				}

        			case('r'): { //Reset all LEDs to (R,G,B)=(0,0,0)
          				for(int i = 0 ; i < ledStrip.numPixels(); i++){
	  					ledStrip.setLEDtoColor((uint8_t)i,
									ledStrip.Color(0, 0, 0));
	  					delay(1);
					}

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


