#ifndef LEDINFO_H
#define LEDINFO_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

class LEDInfo {
	private:
		double* step;
		int* deltas;
		double* carryOver;
		void setStepValues(void);

	public:
		LEDInfo(void);
		~LEDInfo(void);
		void setTargetColor(uint32_t);
		void processStep(void);
		

		uint8_t ledNum;
		uint8_t* curColor;
		uint8_t* tgtColor;
		uint32_t tgtColorAsUINT32;
		bool isActive;
};
#endif
