#ifndef DESKTOPMANAGER_H
	#define BAUD B115200

	#ifdef __WIN32__
	#endif

	#ifdef __WIN64__
	#endif

	#ifdef __linux__
		#include <time.h>
		#include <pthread.h>
		#include <string.h>
		#include <stdlib.h>
		#include <CImg.h>
		#include <termios.h>
	#endif


	class DesktopManager {
		private:
			int arduino_fd;
			struct termios new_io, old_io;
			char* DESKTOP_PATH;
			std::thread **threadPool;
			cimg_library::CImg<unsigned char> DESKTOP_IMAGE;
		public:
			DesktopManager(char*, char*, int);
			char* getDesktopImagePath();
			int** getCurArrPixels();
	};
#endif
