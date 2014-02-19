#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#include "LEDInfo.h"
#include "ActiveLEDInfo.h"
using namespace std;
class LEDStrip {
	private:
		LEDInfo* inactiveLEDs;
		ActiveLEDInfo* activeLEDs;
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
		ActiveLEDInfo* getActiveLEDs();
		LEDInfo* getInactiveLEDs();
		void processStep();
};
#endif
