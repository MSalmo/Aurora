#ifndef DESKTOPMANAGER_H
#define DESKTOPMANAGER_H

	#define BAUD B115200

	#include <time.h>
	#include <string.h>
	#include <stdlib.h>
	#include <CImg.h>
	#include <termios.h>


	class DesktopManager {
		private:
			int arduino_fd;
			struct termios new_io, old_io;
			char* DESKTOP_PATH;
			cimg_library::CImg<unsigned char> DESKTOP_IMAGE;
		public:
			DesktopManager(char* , char* , int);
	};
#endif
