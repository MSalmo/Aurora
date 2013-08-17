#ifndef DESKTOPMANAGER_H
	#include <iostream>
	#include <string>
	#include <cv.h>
	#include <thread.h>
	#include <time.h>
	#include <vector.h>
	#include "LEDInfo.h"
	#ifdef __WIN32
	#endif
	#ifdef __linux
		#include <highgui.h>
		#include <boost/asio.hpp>
		#include <stdlib.h>
	#endif
	using namespace std;
	using namespace cv;
	using namespace boost;

	class DesktopManager {
		private:
			string DESKTOP_PATH;
			Mat DESKTOP_IMAGE;
			thread** threadPool;
			int** curArrPixels;
			vector<LEDInfo> ledVector;
		public:
			DesktopManager(int, time_t);
			DesktopManager(int, char*, time_t);
			DesktopManager(int, Mat, time_t);
			char* getDesktopImagePath();
			int getNumChannels();
			int getNumRows();
			int getNumCols();
			int* getRandPixel();
			int** getCurArrPixels();
	};
#endif
