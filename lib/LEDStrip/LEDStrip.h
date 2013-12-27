#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#endif
#include <vector>
#include "LEDInfo.h"
using namespace std;
class LEDStrip {
	private:
		vector< LEDInfo* > inactiveLEDs;
		vector< ActiveLEDInfo* > activeLEDs;
		ActiveLEDInfo* searchActive(int, int);
		LEDInfo* searchInactive(int);
		int getActiveLEDIndex(int);
		void initialize();
		void fadeAllToBlack();
		void reColorize();
		int moveToActive(int);
		int moveToInactive(int);
	public:
		LEDStrip();
		~LEDStrip();
		vector<ActiveLEDInfo*>* getActiveLEDs();
		void processStep();
};
