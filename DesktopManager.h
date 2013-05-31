#include <iostream>
#include <string>
#ifndef __WIN32__
#endif
#ifndef __UNIX__
	#include <cv.h>
	#include <highgui.h>
	#include <boost/asio.hpp>
#endif
using namespace std;
using namespace cv;

class DesktopManager {
	private:
		extern string DESKTOP_PATH;
		Mat DESKTOP_IMAGE;
	public:
		DesktopManager();
		DesktopManager(string);
		DesktopManager(Mat);
		string getDesktopImagePath();
		int getNumChannels();
		int getNumRows();
		int getNumCols();
};
