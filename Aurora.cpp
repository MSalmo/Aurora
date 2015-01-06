#include "Aurora.h"

char *DESKTOP_PATH, *ARDUINO;

int main (int argc, char* argv[]) {
	if(argc != 4){
		printf("USAGE %s ARDUINO_PATH IMAGE_PATH nLEDs\n", 
			argv[0]);
		exit(EXIT_FAILURE);
	}

	ARDUINO = argv[1];
	DESKTOP_PATH = argv[2];
	int nLEDs = atoi(argv[3]);

	DesktopManager dm(ARDUINO, DESKTOP_PATH, nLEDs);	

	dm.mainLoop();
}
