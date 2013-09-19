#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#endif
#include <vector.h>
#include "LEDInfo.h"

class LEDStrip {
	private:
		vector<LEDInfo> inactiveLEDs;
		vector<LEDInfo> activeLEDs;
		activeLEDInfo searchActive(int, int);
		LEDInfo searchInactive(int, int);
	public:
		LEDStrip();
		~LEDStrip();
		char* getActiveLEDs();
		int moveToActive(int);
		int moveToInactive(int);
};
