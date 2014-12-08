#include "LEDStrip.h"

/*          Class Declarations          */

LEDStrip::LEDStrip(char* loc, int nLEDs){
	strip = Adafruit_NeoPixel(nLEDs, 6, NEO_GRB + NEO_KHZ800);

	initialize(nLEDs);

}
LEDStrip::~LEDStrip(){
}
void LEDStrip::initialize(int nLEDs){
	strip.begin();
	leds = (LEDInfo*)malloc(sizeof(LEDInfo) * nLEDs);
	for(int i = 0 ; i < nLEDs; i++){
		leds[i] = LEDInfo()
		leds[i].setTargetColor( strip.Color(0,0,0) );
	}
	
	uint8_t* STARTCMD = (uint8_t*)malloc(1);
	STARTCMD[0] = 0x30;
	write(arduino_fd, STARTCMD, 1);

}

/*          Private Methods          */
void LEDStrip::processStep()
{
	// Here we will iterate through each LED on the active list
	// and process each step with respect to their individual slopes.

	for(int i = 0 ; i < nLEDs; i++){
		leds[i].processStep();
		uint32_t newColor = strip.Color(leds[i].curColor[0],
					leds[i].curColor[1],
					leds[i].curColor[2]);
		strip.setPixelColor(i, newColor);
	}

	strip.show();
}

/*          Public Methods          */
void setLEDtoColor(uint8_t led, uint32_t tgtColor)
{
	uint8_t* testWrite = (uint8_t*)malloc(4);
	//TODO: Flesh this out. I think we'll need to make a thread per LED.
	free(testWrite);
}
