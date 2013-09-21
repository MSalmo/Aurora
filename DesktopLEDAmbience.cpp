#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>

#define BAUD B9600
#define ARDUINO "/dev/ttyACM0"

using namespace std;

struct termios old_io, new_io;
int arduinoFD, c, res;
char* rVal;
char* bVal;
char* gVal;
char* ledAddr;
char* delim;

int main (int argc, char* argv[]) {
	
	arduinoFD = open(ARDUINO, O_RDWR | O_NOCTTY);
	if (arduinoFD < 0){perror(ARDUINO); exit(EXIT_FAILURE);}
	rVal = (char*)malloc(4);
	gVal = (char*)malloc(4);
	bVal = (char*)malloc(4);
	ledAddr = (char*)malloc(4);
	delim = (char*)malloc(1);
	delim[0] = ',';
	new_io.c_cflag = BAUD | CRTSCTS | CS8 | CLOCAL | CREAD;
	new_io.c_iflag = IGNPAR | ICRNL;
	new_io.c_oflag = 0;
	new_io.c_lflag = ICANON;
	cfsetospeed(&new_io, BAUD);
	cfsetispeed(&new_io, BAUD);
	tcflush(arduinoFD, TCOFLUSH);
	//DesktopManager dm = new DesktopManager(nLEDs, argv[2]);	
	while(true){
		/*
		printf("Enter LED String t[LED_ADDR][R][G][B]: \n");
		printf("Enter LED Number: ");
		fread(ledAddr, 4, 1, stdin);	//read LED #
		fflush(stdin);
		printf("Enter desired red value: ");
		fread(rVal, 4, 1, stdin);		//read red value
		fflush(stdin);
		printf("Enter desired green value: ");
		fread(gVal, 4, 1, stdin);		//read green value
		fflush(stdin);
		printf("Enter desired blue value: ");
		fread(bVal, 4, 1, stdin);		//read blue value
		fflush(stdin);
		*/
		for(int i = 0 ; i < 240; i++) {
			char* testWrite = (char*)malloc(17);
			sprintf(testWrite, "s255,000,000,%03d\n", i);
			fwrite(testWrite,17,1,stdout);
			//write(arduinoFD, testWrite, 17);
			sleep(1);
			free(testWrite);
			testWrite = (char*)malloc(2);
			sprintf(testWrite,"z\n",NULL);
			fwrite(testWrite,2,1,stdout);
			//write(arduinoFD, testWrite, 2);
			free(testWrite);
		}
		//string reset = "r\n";
		//write(arduinoFD, reset.c_str(), 2);
		/*testWrite[0]='t';
		strncpy(testWrite+1,rVal, 3);
		strncpy(testWrite+4,delim, 1);
		strncpy(testWrite+5,gVal, 3);
		strncpy(testWrite+8,delim, 1);
		strncpy(testWrite+9,bVal, 3);
		strncpy(testWrite+12,delim, 1);
		strncpy(testWrite+13, ledAddr, 3);
		testWrite[16]='\n';
		fflush(stdout);
		fwrite(testWrite,17,1,stdout);
		fflush(stdout);
		write(arduinoFD, testWrite, 17);*/
		//free(testWrite);
	}

}
