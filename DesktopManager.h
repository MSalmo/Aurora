#ifndef DESKTOPMANAGER_H
	#include "LEDStrip.h"
	#include <CImg.h>
	#ifdef __WIN32__
	#endif
	#ifdef __WIN64__
	#endif
	#ifdef __linux__
		#include <ctime.h>
		#include <pthread.h>
		#include <stdlib.h>
	#endif

	class DesktopManager {
		private:
			string DESKTOP_PATH;
			Mat DESKTOP_IMAGE;
			thread** threadPool;
		public:
			DesktopManager(int, time_t);
			DesktopManager(int, char*, time_t);
			DesktopManager(int, Mat, time_t);
			char* getDesktopImagePath();
			int** getCurArrPixels();
	};
#endif
