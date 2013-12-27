#include "LEDStrip.h"
/*
 * Class Declarations
 */
using namespace std;
LEDStrip::LEDStrip(){
	inactiveLEDs = vector< LEDInfo* >();
	activeLEDs = vector< ActiveLEDInfo* >();
	initialize();
}
LEDStrip::~LEDStrip(){
}
void LEDStrip::initialize(){
	fadeAllToBlack();
	reColorize();
}
/*
 * Private Methods
 */
ActiveLEDInfo* LEDStrip::searchActive(int index, int search){
	if(activeLEDs[index]->ledNum == search);
}
LEDInfo* LEDStrip::searchInactive(int search){

}
int LEDStrip::moveToActive(int LEDNum){
	int returnVal; 
	if (inactiveLEDs.size() == 0) return -1 ;
	if ( searchInactive(LEDNum) != (LEDInfo *)0){
		ActiveLEDInfo* newActive;
		newActive = (ActiveLEDInfo*)searchInactive(LEDNum);
		activeLEDs.push_back(newActive);
	}
	return LEDNum;
}
int LEDStrip::moveToInactive(int LEDNum){
	vector<ActiveLEDInfo*>::iterator iter;
	iter = activeLEDs.begin() + getActiveLEDIndex(LEDNum);

	inactiveLEDs.push_back((LEDInfo)*iter);
	activeLEDs.clear(*iter);
}
vector<ActiveLEDInfo *>* LEDStrip::getActiveLEDs(){
	return &activeLEDs;
}
int LEDStrip::getActiveLEDIndex(int ledNum){
	/*returns the iterator position for the ActiveLEDInfo struct
     with the corresponding LED Number (ledNum). -1 if it doesn't exist.*/
	for ( int i = 0 ; i < activeLEDs.size(); i++ )
		if( activeLEDs.at(i)->ledNum == ledNum )
			return i;

	return -1; //Either LED isn't active or it doesn't exist.
}
void LEDStrip::processStep(){
	for( vector<ActiveLEDInfo*>::iterator iter = activeLEDs.begin();
        iter < activeLEDs.end();
        iter++){
		// Here we will iterate through each LED on the active list
      // and process each step with respect to their individual slopes.
		incrementLED(&iter);
	}
}
