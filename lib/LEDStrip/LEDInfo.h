#ifndef LEDINFO_H
	#ifdef __linux__
		#include <sys/types.h>
		#include <inttypes.h>
	#endif
	#include <Adafruit_NeoPixel.h>
#define LEDINFO_H
class ActiveLEDInfo : public LEDInfo {
	private:
		double* step;
		float* deltas;
		float* carryOver;

	public:
		ActiveLEDInfo();
		~ActiveLEDInfo();
		void setTargetColor(uint32_t);
		void setStepValues();
		void processStep();

		uint8_t ledNum;
		uint8_t* curColor;
		uint8_t* tgtColor;
		uint32_t tgtColorAsUINT32;
		bool isActive;
};
#endif
