#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#include "LEDInfo.h"

#define BAUD B115200

class LEDStrip {
	private:
		int nLEDs, arduino_fd;
		LEDInfo* leds;
		void initialize(int);
		struct termios old_io, new_io;
		void processStep();
		Adafruit_NeoPixel strip;
	public:
		LEDStrip(int);
		~LEDStrip();
		void setLEDtoColor(LEDInfo*, uint8_t, uint8_t, uint8_t);
};
#endif
