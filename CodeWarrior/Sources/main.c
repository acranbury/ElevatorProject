#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timer.h"
#include "lcd.h"
#include "usonic.h"
#include "utils.h"
#include "canModule.h"



void main(void) {
  
	unsigned char txbuff[] = "DEADBEEF";
	word distance;

	timer_init();
	LCDinit();

	initCan();

	while (!(CANCTL0 & 0x10));

	CANRFLG = 0xC3;

	CANRIER = 0x01;

	LCDprintf("Hello World");

	usonic_init();
	
	EnableInterrupts;

	for(;;) {
		LCDclear();
		distance = usonic_getDistance();
		MSG message = {(ST_ID_100), 0x00, sizeof(txbuff) - 1, txbuff};
		sendCanFrame(message);
		LCDprintf("Hello World!\n %d mm", distance);
		msleep(100);
  } 
}
