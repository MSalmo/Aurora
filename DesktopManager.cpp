#include "DesktopManager.h"

using namespace cv;

DesktopManager::DesktopManager(){
}
Desktopmanager::DesktopManager(string s){
	DESKTOP_PATH = s;
}
Desktopmanager::DesktopManager(Mat m){
	//To be fixed later
	DESKTOP_IMAGE(2, 2, CV_8UC3, Scalar(0,0,255));
}
string DesktopManager::getDesktopImagePath(){
	return DESKTOP_PATH;
}
