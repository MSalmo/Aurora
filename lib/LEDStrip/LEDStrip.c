#include "LEDStrip.h"
/*
 * Class Declarations
 */

LEDStrip::LEDStrip(char* loc, int nLEDs){
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
	/* Initialize the inactive and active LED arrays here */
	uint8_t* STARTCMD = (uint8_t*)malloc(1);
	STARTCMD[0] = 0x30;
	write(arduino_fd, STARTCMD, 1);

	inactiveLEDs = (LEDInfo*)malloc(nLEDs * sizeof(LEDInfo));
}
/*
 * Private Methods
 */
ActiveLEDInfo* LEDStrip::searchActive(int index, int search)
{
	return activeLEDs;
}
LEDInfo* LEDStrip::searchInactive(int search){

}
int LEDStrip::moveToActive(int LEDNum)
{
	int returnVal; 
	if ( searchInactive(LEDNum) != (LEDInfo *)0){
		ActiveLEDInfo* newActive;
		newActive = (ActiveLEDInfo*)searchInactive(LEDNum);
	}
	return LEDNum;
}
int LEDStrip::moveToInactive(int LEDNum)
{
	return 0;
}
ActiveLEDInfo* LEDStrip::getActiveLEDs()
{
	return activeLEDs;
}
LEDInfo* LEDStrip::getInactiveLEDs()
{
	return inactiveLEDs;
}

int LEDStrip::getActiveLEDIndex(int ledNum)
{
	//returns the iterator position for the ActiveLEDInfo struct
     //with the corresponding LED Number (ledNum). -1 if it doesn't exist.

	return -1; //Either LED isn't active or it doesn't exist.
}

void LEDStrip::processStep()
{
	// Here we will iterate through each LED on the active list
	// and process each step with respect to their individual slopes.
		ActiveLEDInfo *iter;
}

/*
 * Public Methods
 */
void setLEDtoColor(LEDInfo* led, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t* testWrite = (uint8_t*)malloc(6);
	//Do Stuff
	free(testWrite);
}
