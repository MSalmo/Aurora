#ifndef DESKTOPMANAGER_H
	#include <iostream>
	#include <string>
	#ifdef __WIN32
	#endif
	#ifdef __linux
		#include <cv.h>
		#include <highgui.h>
		#include <boost/asio.hpp>
		#include <thread>
	#endif
	using namespace std;
	using namespace cv;
	using namespace boost;

	class DesktopManager {
		private:
			extern string DESKTOP_PATH;
			Mat DESKTOP_IMAGE;
			thread **threadPool;
		public:
			DesktopManager();
			DesktopManager(string);
			DesktopManager(Mat);
			string getDesktopImagePath();
			int getNumChannels();
			int getNumRows();
			int getNumCols();
	};
#endif
