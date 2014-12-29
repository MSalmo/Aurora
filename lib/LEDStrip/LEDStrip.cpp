#include "LEDStrip.h"

/*          Class Declarations          */

LEDStrip::LEDStrip(uint16_t nLEDs, uint8_t nPin) : 
		Adafruit_NeoPixel(nLEDs, nPin, NEO_GRB + NEO_KHZ800) {
	Serial.begin(9600);
	Serial.print("Starting LEDStrip... ");
	initialize(nLEDs);

}
LEDStrip::~LEDStrip(){
}
void LEDStrip::initialize(int nLEDs){
	delay(1);
	begin();
	leds = (LEDInfo*)malloc(sizeof(LEDInfo) * nLEDs);
	for(int i = 0 ; i < numPixels(); i++){
		leds[i] = LEDInfo();
		leds[i].setTargetColor( Color(0,0,0) );
	}
	
}

bool LEDStrip::replaceInPQueue(void)
{
	uint8_t lowestCD = getLowestCD();

	LEDInfo* newHead = leds;
	while( (newHead->cooldown == lowestCD) && (newHead != NULL)){
		newHead->cooldown = rand() % 46 + 10;
		newHead++;
	}

	//We now have an array that's not sorted any more so we shall sort
	//by cooldown.

	qsort(leds, 0, numPixels());
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

void LEDStrip::qsort(LEDInfo* arr, uint8_t min, uint8_t max)
{
	//We'll implement 2/3rds quicksort here
	if(min > max) return; //already sorted

	int j = 0;
	uint8_t pivIndex = 2*(min+max) / 3, piv = arr[pivIndex].cooldown;
	swap(arr[pivIndex], arr[max-1]);

	for(int i = min; i < max ; i++){
		if(arr[i].cooldown <= piv){
			swap(arr[j], arr[i]);
			j++;
		}
	}

	swap (arr[max-1], arr[j]);

	qsort(arr, min, piv);
	qsort(arr, piv+1, max);

	
	
}

void LEDStrip::swap(LEDInfo& a, LEDInfo& b)
{
	LEDInfo temp;
	temp = a;
	a = b;
	b = temp;
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
