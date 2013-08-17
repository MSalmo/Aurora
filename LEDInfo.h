#ifndef LEDINFO_H
#define LEDINFO_H
struct LEDInfo {
	short ledNum;
	short delay;
	short remDelay;
	short* curColor;
};
struct ActiveLEDInfo : LEDInfo {
	float* step;
	float* carryOver;
	short* tgtColor;
};
#endif
