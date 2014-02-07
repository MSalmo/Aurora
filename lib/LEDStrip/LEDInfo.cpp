#include "LEDInfo.h"

uint8_t* LEDInfo::extractColorInfo(){
	
}
void ActiveLEDInfo::setTargetColor(uint8_t* colorInfo) {
		if(tgtColor != NULL)
			free(tgtColor);
		tgtColor=new uint8_t[3];

		tgtColor[0] = (colorInfo%256);			//Blue
		tgtColor[1] = (colorInfo >> 8) % 256;	//Green
		tgtColor[2] = (colorInfo >> 16) % 256;	//Red

}

void ActiveLEDInfo::setStepValues(uint8_t* colorInfo) {
  		uint32_t curColor = strip.getPixelColor(colorInfo[3]);
  		carryOver = (float*)malloc(3);
  		tgtColor  = new uint8_t[3];
  		int *deltas = new int[3];
		float *step = new float[3];
  
  		oldCols[2] = curColor % 256;        //Old Blue Value
  		deltas[2] = (int)colorInfo[2] - (int)oldCols[2];
  
  		oldCols[1] = (curColor >> 8) % 256; //Old Green Value
  		deltas[1] = (int)colorInfo[1] - (int)oldCols[1];
  
  		oldCols[0] = (curColor >> 16) % 256;//Old Red Value
  		deltas[0] = (int)colorInfo[0] - (int)oldCols[0];

		int absDelta0 = abs(deltas[0]);
		int absDelta1 = abs(deltas[1]);
  		int absDelta2 = abs(deltas[2]);
  		int farthest = max(max(absDelta0,absDelta1),absDelta2);
  
  		//Flip the denom and the num, use modf to extract carryover.
  		float carryValR = (1.0f*deltas[0]/farthest);
  		float carryValG = (1.0f*deltas[1]/farthest); 
  		float carryValB = (1.0f*deltas[2]/farthest);
  
  
  		carryValR = modf(carryValR, step[0]);
  		carryValG = modf(carryValG, step[1]);
  		carryValB = modf(carryValB, step[2]);

		if(carryValR < 0)
    		stepR = 0 - stepR;
  		if(carryValG < 0)
    		stepG = 0 - stepG;
  		if(carryValB < 0)
    		stepB = 0 - stepB; 
}
