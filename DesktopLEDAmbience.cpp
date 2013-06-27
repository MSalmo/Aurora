#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <avr/io.h>

#define FOSC 16000000
#define BAUD 115200
#define MYUBRR (((((FOSC * 10) / (16L * BAUD)) + 5)/10))

using namespace std;

char* rVal;
char* bVal;
char* gVal;
char* ledAddr;
void ioinit(void){
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}
int main (int argc, char* argv[]) {
	
	int arduinoFD;
	if(argc != 3){
		fflush(stderr);
		printf(stderr, "USAGE: ./" + argv[0] + " [#LEDs] [IMAGE_PATH]\n");
		exit(EXIT_FAILURE);
	}
	int nLEDs = atoi(argv[1]);
	//DesktopManager dm = new DesktopManager(nLEDs, argv[2]);	
	while(true){
		printf(stdout, "Enter LED String t[LED_ADDR][R][G][B]: ");
		read(stdin,&ledAddr, 3);	//read LED #
		read(stdin,&rVal, 3);		//read red value
		read(stdin,&gVal, 3);		//read green value
		read(stdin,&bVal, 3);		//read blue value
	}

}
