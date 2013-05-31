#include "DesktopManager.h"

using namespace cv;
using namespace std;

DesktopManager::DesktopManager(){
}
Desktopmanager::DesktopManager(char* imgPath){
	DESKTOP_PATH = imgPath;
	DESKTOP_IMAGE = imread(imgPath, CV_LOAD_IMAGE_COLOR);
}
Desktopmanager::DesktopManager(Mat m){
	DESKTOP_IMAGE(m);
}
string DesktopManager::getDesktopImagePath(){
	return DESKTOP_PATH;
}

int DesktopManager::getNumChannels(){
	DESKTOP_IMAGE.channels();
}

int DesktopManager::getNumRows(){
	DESKTOP_IMAGE.rows;
}

int DesktopManager::getNumCols(){
	DESKTOP_IMAGE.cols * DESKTOP_IMAGE.channels();
}
