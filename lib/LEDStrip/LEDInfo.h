#ifndef LEDINFO_H
	#include <Adafruit_NeoPixel.h>
	#include "Timer.h"
	#include <inttypes.h>
#define LEDINFO_H
class LEDInfo {
	public:
		LEDInfo();
		~LEDInfo();
		uint8_t ledNum;
		Timer remDelay;
		bool notifyReady;
		uint8_t* curColor;
		LEDInfo* next;
};

#endif
