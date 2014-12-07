#include "LEDStrip.h"
#include "Adafruit_NeoPixel.h"

/*          Class Declarations          */

LEDStrip::LEDStrip(char* loc, int nLEDs){
	strip = Adafruit_NeoPixel(nLEDs, 6, NEO_GRB + NEO_KHZ800);

	initialize(nLEDs);

	if((arduino_fd = open(loc, O_RDWR | O_NOCTTY)) < 0) {
		perror(loc); 
		exit(EXIT_FAILURE);
	}

	new_io.c_cflag = BAUD | CRTSCTS | CS8 | CLOCAL | CREAD;
	new_io.c_iflag = IGNPAR | ICANL;
	new_io.c_oflag = 0;
	new_io.c_lflag = ICANON;
	cfsetospeed(&new_io, BAUD);
	cfsetispeed(&new_io, BAUD);
	tcflush(arduino_fd, TCOFLUSH);

	//I only need 1 byte in order to acknowledge that the arduino needs
	//another set of colors for the next light
	new_io.c_cc[VMIN] = 1;
	new_io.c_cc[VTIME] = 0;

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
void setLEDtoColor(LEDInfo* led, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t* testWrite = (uint8_t*)malloc(4);
	//TODO: Flesh this out. I think we'll need to make a thread per LED.
	free(testWrite);
}
