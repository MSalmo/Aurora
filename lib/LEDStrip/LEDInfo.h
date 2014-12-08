#ifndef LEDINFO_H
#define LEDINFO_H
class LEDInfo {
	private:
		double* step;
		float* deltas;
		float* carryOver;
		void setStepValues();

	public:
		LEDInfo();
		~LEDInfo();
		void setTargetColor(uint32_t);
		void processStep();
		

		uint8_t ledNum;
		uint8_t* curColor;
		uint8_t* tgtColor;
		uint32_t tgtColorAsUINT32;
		bool isActive;
};
#endif
