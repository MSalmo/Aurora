#include "DesktopManager.h"

using namespace cv;
using namespace std;
using namespace boost;

DesktopManager::DesktopManager(int nThreads, time_t seed=NULL){
	srand(time(seed));
}
Desktopmanager::DesktopManager(int nThreads, char* imgPath, time_t seed=NULL){
	DESKTOP_PATH = imgPath;
	DESKTOP_IMAGE = imread(imgPath, CV_LOAD_IMAGE_COLOR);
	srand(time(seed));
}
Desktopmanager::DesktopManager(int nThreads, Mat m, time_t seed=NULL){
	DESKTOP_IMAGE(m);
	srand(time(seed));
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

int* DesktopManager::getRandPixel(){
}

int** DesktopManager::getCurArrPixels(){
	return curArrPixels;
}
