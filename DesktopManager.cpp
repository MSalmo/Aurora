#include "DesktopManager.h"

/* Constructor / Destructor */
DesktopManager::DesktopManager(char *loc, char *imgloc, int nLEDs)
{
	DESKTOP_IMAGE(*imgloc);
	srand(time(NULL));
	
	if((arduino_fd = open(loc, O_RDWR | O_NOCTTY)) < 0) {
		perror(loc);
		exit(EXIT_FAILURE);
	}

	new_io.c_cflag = BAUD | CRTSCTS | CS8 | CLOCAL | CREAD;
	new_io.c_iflag = IGNPAR | ICRNL;
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

/* Private Methods */
bool DesktopManager::sendNewestPixels(void)
{
	int img_width = DESKTOP_IMAGE.width(), 
		img_height = DESKTOP_IMAGE.height();

	printf("Received image dimensions: %d x %d\n", img_width, img_height);
	char* numUpdatePixels = (char*)malloc(2);
	if( read(arduino_fd, numUpdatePixels, 1) < 0) return false;

	sleep(numUpdatePixels[1]);
	char* newColorBuf = (char*)malloc(3*numUpdatePixels[0]);
	
	for(int i = 0 ; i < numUpdatePixels[0]; i += 3){
		int rand_x = rand() % img_width, rand_y = rand() % img_height;
		numUpdatePixels[i] = DESKTOP_IMAGE(rand_x, rand_y, 0, 0);
		numUpdatePixels[i+1] = DESKTOP_IMAGE(rand_x, rand_y, 0, 1);
		numUpdatePixels[i+2] = DESKTOP_IMAGE(rand_x, rand_y, 0, 2);

	}

	write(arduino_fd, newColorBuf, 3*numUpdatePixels[0]);
	free(newColorBuf);
	free(numUpdatePixels);

	return true;  //This is a stub for now.
}

bool DesktopManager::update(void)
{
	/* TODO: Make this a procedure which pulls from the image and then
	 * updates the LED Strip accordingly
	 */

	return false; //This is a stub for now.
}

/* Public Methods */
bool DesktopManager::loadNewImage(char* imgloc)
{
	return false; //This is a stub for now.
}
