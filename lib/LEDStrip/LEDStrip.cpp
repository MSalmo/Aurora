#include "LEDStrip.h"
/*
 * Class Declarations
 */
using namespace std;
LEDStrip::LEDStrip(int nLEDs){
	initialize(nLEDs);
}
LEDStrip::~LEDStrip(){
}
void LEDStrip::initialize(int nLEDs){
	/* Initialize the inactive and active LED arrays here */
	fadeAllToBlack();
	reColorize();
}
/*
 * Private Methods
 */
ActiveLEDInfo* LEDStrip::searchActive(int index, int search){
	return activeLEDs;
}
LEDInfo* LEDStrip::searchInactive(int search){

}
int LEDStrip::moveToActive(int LEDNum){
	int returnVal; 
	if ( searchInactive(LEDNum) != (LEDInfo *)0){
		ActiveLEDInfo* newActive;
		newActive = (ActiveLEDInfo*)searchInactive(LEDNum);
	}
	return LEDNum;
}
int LEDStrip::moveToInactive(int LEDNum){
	return 0;
}
ActiveLEDInfo* LEDStrip::getActiveLEDs(){
	return activeLEDs;
}
LEDInfo* LEDStrip::getInactiveLEDs(){
	return inactiveLEDs;
}
int LEDStrip::getActiveLEDIndex(int ledNum){
	/*returns the iterator position for the ActiveLEDInfo struct
     with the corresponding LED Number (ledNum). -1 if it doesn't exist.*/
	return -1; //Either LED isn't active or it doesn't exist.
}
void LEDStrip::processStep(){
		// Here we will iterate through each LED on the active list
      // and process each step with respect to their individual slopes.
		ActiveLEDInfo *iter;
}
void LEDStrip::fadeAllToBlack(){
}
void LEDStrip::reColorize(){
}
