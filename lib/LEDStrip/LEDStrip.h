#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#include <stdint.h>
#include "LEDInfo.h"
#include "Adafruit_NeoPixel.h"
#define BAUD B115200

class LEDStrip {
	private:
		LEDInfo* leds;
		void initialize(int);
		void processStep();
		Adafruit_NeoPixel strip;
	public:
		int nLEDs;

		LEDStrip(int);
		~LEDStrip();
		void setLEDtoColor(uint8_t, uint32_t);
};
#endif
