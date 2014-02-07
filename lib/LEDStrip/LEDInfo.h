#ifndef LEDINFO_H
	#include <Adafruit_NeoPixel.h>
	#include "Timer.h"
#define LEDINFO_H
struct LEDInfo {
	short ledNum;
	Timer remDelay;
	bool notifyReady;
	uint32_t* curColor;
	LEDInfo* next;
};
struct ActiveLEDInfo : LEDInfo {
	float* step;
	float* deltas;
	float* carryOver;
	uint8_t* tgtColor;
	void setTargetColor(uint8_t* colorInfo) {
		if(tgtColor != NULL)
			free(tgtColor);
		tgtColor=new uint8_t[3];

		tgtColor[0] = (colorInfo%256);			//Blue
		tgtColor[1] = (colorInfo >> 8) % 256;	//Green
		tgtColor[2] = (colorInfo >> 16) % 256;	//Red

	};
};
#endif
