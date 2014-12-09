#include "LEDInfo.h"
/* LEDInfo Declarations */

LEDInfo::LEDInfo(void){
	step = (double*)malloc(3*sizeof(double));
	deltas = (int*)malloc(3*sizeof(double));
	carryOver = (double*)malloc(3*sizeof(double));

	isActive = false;
}

LEDInfo::~LEDInfo(void){
	free(curColor);
	free(step);
	free(deltas);
	free(carryOver);
}

/*          Private Methods          */


void LEDInfo::setStepValues(void) {
  
  		//curColor[2] = curColor % 256;        //Old Blue Value
  		deltas[2] = (int)tgtColor[2] - (int)curColor[2];
  
  		//curColor[1] = (curColor >> 8) % 256; //Old Green Value
  		deltas[1] = (int)tgtColor[1] - (int)curColor[1];
  
  		//curColor[0] = (curColor >> 16) % 256;//Old Red Value
  		deltas[0] = (int)tgtColor[0] - (int)curColor[0];

		int absDelta0 = abs(deltas[0]);
		int absDelta1 = abs(deltas[1]);
  		int absDelta2 = abs(deltas[2]);
  		int farthest; 
		if(absDelta0 >= absDelta1){
			if(absDelta0 >= absDelta2)
				farthest = absDelta0;
			else
				farthest = absDelta2;
		}
		else{
			if(absDelta1 >= absDelta2)
				farthest = absDelta1;
			else
				farthest = absDelta2;
		}
  
  		//Flip the denom and the num, use modf to extract carryover.
  		double carryValR = (1.0f*deltas[0]/farthest);
  		double carryValG = (1.0f*deltas[1]/farthest); 
  		double carryValB = (1.0f*deltas[2]/farthest);
  
  
  		carryOver[0] = modf(carryValR, &(step[0]));
  		carryOver[1] = modf(carryValG, &(step[1]));
  		carryOver[2] = modf(carryValB, &(step[2]));

		if(carryValR < 0)
    		step[0] = 0 - step[0];
  		if(carryValG < 0)
    		step[1] = 0 - step[1];
  		if(carryValB < 0)
    		step[2] = 0 - step[2]; 
}

/*         Public Methods          */
void LEDInfo::setTargetColor(uint32_t colorInfo) {
		if(tgtColor != NULL)
			free(tgtColor);
		tgtColor=new uint8_t[3];

		tgtColor[0] = (colorInfo%256);			//Blue
		tgtColor[1] = (colorInfo >> 8) % 256;	//Green
		tgtColor[2] = (colorInfo >> 16) % 256;	//Red

		tgtColorAsUINT32 = colorInfo;
		
		if((curColor[0] != tgtColor[0]) &&
		   (curColor[1] != tgtColor[1]) &&
		   (curColor[2] != tgtColor[2])){
			isActive = true;
			setStepValues();
		}

}

void LEDInfo::processStep(void){
	if((curColor[0] == tgtColor[0]) &&
	   (curColor[1] == tgtColor[1]) &&
	   (curColor[2] == tgtColor[2]))
		isActive = false;

	if(isActive){
		for(int i = 0 ; i < 3; i++){
			if(tgtColor[i] != curColor[i]){
				curColor[i] += step[i];
				carryOver[i] += step[i];
				
				if(carryOver[i] >= 1.0){
					curColor[i]++;
					carryOver[i]--;
				}
			
				if(carryOver[i] <= -1.0){
					curColor[i]--;
					carryOver[i]++;
				}
			}
		}
	}
}
