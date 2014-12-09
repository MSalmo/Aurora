#include "LEDStrip.h"

/*          Class Declarations          */

LEDStrip::LEDStrip(uint16_t nLEDs, uint8_t nPin) : 
		Adafruit_NeoPixel(nLEDs, nPin, NEO_GRB + NEO_KHZ800) {
	initialize(nLEDs);

}
LEDStrip::~LEDStrip(){
}
void LEDStrip::initialize(int nLEDs){
	begin();
	leds = (LEDInfo*)malloc(sizeof(LEDInfo) * nLEDs);
	for(int i = 0 ; i < numPixels(); i++){
		leds[i] = LEDInfo();
		leds[i].setTargetColor( Color(0,0,0) );
	}
	
}

/*          Private Methods          */
void LEDStrip::processStep()
{
	// Here we will iterate through each LED on the active list
	// and process each step with respect to their individual slopes.

	for(int i = 0 ; i < numPixels(); i++){
		leds[i].processStep();
		uint32_t newColor = Color(leds[i].curColor[0],
					leds[i].curColor[1],
					leds[i].curColor[2]);
		setPixelColor(i, newColor);
	}

	show();
}

/*          Public Methods          */
void LEDStrip::setLEDtoColor(uint8_t led, uint32_t tgtColor)
{
	leds[led].setTargetColor(tgtColor);
}

void LEDStrip::setLEDtoColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b){
	setLEDtoColor(led, Color(r, g, b));
}
