#include <iostream>
#include <string>
#ifndef __WIN32__
#endif
#ifndef __UNIX__
	#include <cv.h>
	#include <highgui.h>
#endif

class DesktopManager {
	private:
		extern string DESKTOP_PATH;
		Mat DESKTOP_IMAGE;
	public:
		DesktopManager();
		DesktopManager(string);
		DesktopManager(Mat);
		string getDesktopImagePath();
};
