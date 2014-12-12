#ifndef DESKTOPMANAGER_H
	#define BAUD B115200

	#ifdef __WIN32__
	#endif

	#ifdef __WIN64__
	#endif

	#ifdef __linux__
		#include <ctime.h>
		#include <pthread.h>
		#include <stdlib.h>
		#include <CImg.h>
		#include <termios.h>
	#endif

	class DesktopManager {
		private:
			int arduino_fd;
			struct termios new_io, old_io;
			string DESKTOP_PATH;
			thread** threadPool;
		public:
			DesktopManager(int, time_t);
			DesktopManager(int, char*, time_t);
			DesktopManager(int, Mat, time_t);
			char* getDesktopImagePath();
			int** getCurArrPixels();
	};
#endif
