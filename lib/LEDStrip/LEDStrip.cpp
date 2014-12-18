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

bool LEDStrip::replaceInPQueue(void)
{
}

/*          Private Methods          */

uint8_t LEDStrip::getLowestCD(void)
{
	if(leds != NULL)
		return leds->cooldown;
}

uint8_t LEDStrip::getNumLowestCD(void)
{
	LEDInfo* ledptr;
	uint8_t lowestCD = getLowestCD();
	uint8_t i = 0;

	if(leds != NULL){
		ledptr = leds;
		while(ledptr->cooldown == lowestCD){
			i++;
			ledptr++;
		}

		return i;
	}
	return -1;
}

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
	delay(1);
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

void LEDStrip::sendLEDStatus()
{
	uint8_t* status = (uint8_t*)malloc(2);
	status[0] = getLowestCD();
	status[1] = getNumLowestCD();
}
