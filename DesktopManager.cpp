#include "DesktopManager.h"

using namespace cv;

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
