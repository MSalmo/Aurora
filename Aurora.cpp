#include "Aurora.h"

struct termios old_io, new_io;
int arduinoFD, c, res;
char *ARDUINO, *DESKTOP_PATH;

int main (int argc, char* argv[]) {
	if(argc != 4){
		printf("USAGE %s ARDUINO_PATH IMAGE_PATH nLEDs\n", argv[0]);
	}
	int nLEDs = atoi(argv[3]);
	ARDUINO = argv[1];
	DESKTOP_PATH = argv[2];
	DesktopManager dm(ARDUINO, DESKTOP_PATH, nLEDs);	

	while(true){
		//TODO: add a loop here to manage the pixel-picking via the DM.
	}

}
