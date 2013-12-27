#ifndef LEDINFO_H
	#include "Timer.h"
#define LEDINFO_H
struct LEDInfo {
	short ledNum;
	Timer remDelay;
	bool notifyReady;
	short* curColor;
};
struct ActiveLEDInfo : LEDInfo {
	float* step;
	float* carryOver;
	short* tgtColor;
};
#endif
