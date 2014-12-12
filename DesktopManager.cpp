#include "DesktopManager.h"


DesktopManager::DesktopManager(char* loc, char* imgloc, int nLEDs, time_t seed=NULL){
	srand(time(seed));
	image(imgloc);
	
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

	uint8_t* STARTCMD = (uint8_t*)malloc(1);
	STARTCMD[0] = 0x30;
	write(arduino_fd, STARTCMD, 1);
	free(STARTCMD);
}

string DesktopManager::getDesktopImagePath(){
	return DESKTOP_PATH;
}

int DesktopManager::getNumChannels(){
	DESKTOP_IMAGE.channels();
}

int DesktopManager::getNumRows(){
	DESKTOP_IMAGE.rows;
}

int DesktopManager::getNumCols(){
	DESKTOP_IMAGE.cols * DESKTOP_IMAGE.channels();
}

int* DesktopManager::getRandPixel(){
}

int** DesktopManager::getCurArrPixels(){
	return curArrPixels;
}
