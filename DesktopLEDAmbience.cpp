#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define BAUD B115200
using namespace std;

struct termios old_io, new_io;
int arduinoFD, c, res;
char* rVal;
char* bVal;
char* gVal;
char* ledAddr;

int main (int argc, char* argv[]) {
	
	arduinoFD = open(argv[1], O_RDWR | O_NOCTTY);
	if (arduinoFD < 0){perror(argv[1]); exit(EXIT_FAILURE);}

	new_io.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	new_io.c_iflag = IGNPAR | ICRNL;
	new_io.c_oflag = 0;
	new_io.c_lflag = ICANON

	tcflush(arduinoFD, TCOFLUSH);
	//DesktopManager dm = new DesktopManager(nLEDs, argv[2]);	
	while(true){
		printf(stdout, "Enter LED String t[LED_ADDR][R][G][B]: ");
		read(stdin,&ledAddr, 3);	//read LED #
		read(stdin,&rVal, 3);		//read red value
		read(stdin,&gVal, 3);		//read green value
		read(stdin,&bVal, 3);		//read blue value
	}

}
