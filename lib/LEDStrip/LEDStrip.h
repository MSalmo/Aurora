#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include "Adafruit_NeoPixel.h"
#include <stdint.h>
#include "LEDInfo.h"

class LEDStrip : public Adafruit_NeoPixel {
	private:
		LEDInfo* leds;
		void initialize(int);
		bool replaceInPQueue(void);
		uint8_t getLowestCD(void);
		uint8_t getNumLowestCD(void);
		void qsort(LEDInfo*, uint8_t, uint8_t);
	public:
		LEDStrip(uint16_t, uint8_t);
		~LEDStrip();
		void setLEDtoColor(uint8_t, uint32_t);
		void setLEDtoColor(uint8_t, uint8_t, uint8_t, uint8_t);
		void processStep();
		void sendLEDStatus();

};
#endif
