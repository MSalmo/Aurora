#include "LEDStrip.h"
LEDStrip::LEDStrip(){
	inactiveLEDs = new vector<LEDInfo>();
	activeLEDs = new vector<ActiveLEDInfo>();
}
LEDStrip::~LEDStrip(){
}
ActiveLEDInfo* LEDStrip::searchActive(int index, int search){
	if(activeLEDs[index].ledNum == search);
}
LEDInfo LEDStrip::searchInactive(int index, int search){

}
int LEDStrip::moveToActive(int LEDNum){
	int returnVal = (inactiveLEDs.size() == 0) ? -1: 
}
int LEDStrip::moveToInactive(int LEDNum){
}
LEDStrip::getActiveLEDs(){
}

