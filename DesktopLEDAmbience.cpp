#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <inttypes.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include "LEDStrip.h"
#include <vector>
#define BAUD B115200
#define ARDUINO "/dev/ttyACM0"

using namespace std;

struct termios old_io, new_io;
int arduinoFD, c, res;

int main (int argc, char* argv[]) {
	srand(time(NULL));

	arduinoFD = open(ARDUINO, O_RDWR | O_NOCTTY);
	if (arduinoFD < 0){perror(ARDUINO); exit(EXIT_FAILURE);}

	new_io.c_cflag = BAUD | CRTSCTS | CS8 | CLOCAL | CREAD;
	new_io.c_iflag = IGNPAR | ICRNL;
	new_io.c_oflag = 0;
	new_io.c_lflag = ICANON;
	cfsetospeed(&new_io, BAUD);
	cfsetispeed(&new_io, BAUD);
	tcflush(arduinoFD, TCOFLUSH);

	//I only need 1 byte in order to acknowledge that the arduino needs
   //another set of colors for the next light.
	new_io.c_cc[VMIN] = 1;
	new_io.c_cc[VTIME] = 0;

	//DesktopManager dm = new DesktopManager(nLEDs, argv[2]);	
	uint8_t* STARTCMD = (uint8_t*)malloc(1);
	STARTCMD[0]=0x30;
	write(arduinoFD, STARTCMD, 1);
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
