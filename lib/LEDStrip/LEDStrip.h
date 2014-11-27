#ifndef LEDSTRIP_H
#define LEDSTRIP_H
	#ifdef __linux
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <termios.h>
		#include <fcntl.h>
	#endif
#include "LEDInfo.h"
#include "ActiveLEDInfo.h"

#define BAUD B115200

class LEDStrip {
	private:
		int nLEDs, nActive, nInactive, arduino_fd;
		LEDInfo* inactiveLEDs;
		ActiveLEDInfo* activeLEDs;
		ActiveLEDInfo* searchActive(int, int);
		LEDInfo* searchInactive(int);
		int getActiveLEDIndex(int);
		void initialize(int);
		int moveToActive(int);
		int moveToInactive(int);
		struct termios old_io, new_io;
		void processStep();
	public:
		LEDStrip(int);
		~LEDStrip();
		ActiveLEDInfo* getActiveLEDs();
		LEDInfo* getInactiveLEDs();
		void setLEDtoColor(LEDInfo*, uint8_t, uint8_t, uint8_t);
};
#endif
