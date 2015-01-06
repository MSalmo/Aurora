#ifndef DESKTOPMANAGER_H
#define DESKTOPMANAGER_H

	#define BAUD B115200

	#include <time.h>
	#include <string.h>
	#include <stdlib.h>
	#include <CImg.h>
	#include <termios.h>
	#include <inttypes.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>


	class DesktopManager {
		private:
			int arduino_fd, image_width, image_height;
			struct termios new_io, old_io;
			char* DESKTOP_PATH;
			cimg_library::CImg<unsigned char> DESKTOP_IMAGE;
			bool sendNewestPixels(void);
		public:
			DesktopManager(char* , char* , int);
			bool loadNewImage(char*);
			bool mainLoop(void);

	};
#endif
