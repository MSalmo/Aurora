#ifndef ACTIVELEDINFO_H
#include "LEDInfo.h"
#define ACTIVELEDINFO_H
class ActiveLEDInfo : public LEDInfo {
	public:
		float* step;
		float* deltas;
		float* carryOver;
		uint8_t* tgtColor;
		uint32_t tgtColorAsUINT32;

		ActiveLEDInfo();
		~ActiveLEDInfo();
		void setTargetColor(uint32_t);
		void setStepValues();
};
#endif
