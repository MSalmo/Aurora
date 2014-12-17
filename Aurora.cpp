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
		uint8_t* testWrite = (uint8_t*)malloc(6);
			for(uint8_t i = 0; i < 240; i++){
				testWrite[0] = (uint8_t)'s';
				testWrite[1] = (uint8_t)rand()%256;
				testWrite[2] = (uint8_t)rand()%256;
				testWrite[3] = (uint8_t)rand()%256;
				testWrite[4] = (uint8_t)i;
				testWrite[5] = (uint8_t)'z';
				char* outPrint = (char*)malloc(17);
				sprintf(outPrint, "R%03dG%03dB%03dL%03d\n",
					testWrite[1], testWrite[2], testWrite[3], testWrite[4]);
				fwrite(outPrint,17,1,stdout);
				//set_rts(arduinoFD, 0);
				tcdrain(arduinoFD);
				write(arduinoFD, testWrite, 6);
				usleep(17.5 * 1000);
				//set_rts(arduinoFD, 1);
			}
			free(testWrite);
	}

}
