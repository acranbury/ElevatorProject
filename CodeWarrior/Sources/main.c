#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timer.h"
#include "lcd.h"
#include "usonic.h"
#include "utils.h"
#include "canModule.h"
#include "spi.h"

void main(void) {
  
	unsigned char txbuff[] = "DEADBEEF";
	word distance;
	CANMessage message;

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
		
		message.id = ST_ID_100;
		message.priority = 0x00;
		message.length = sizeof(txbuff) - 1;
		message.payload = txbuff;
		
		sendCanFrame(message);
		if ( canRXFlag )
		{
			LCDprintf("%s!\n %d mm", canRXData, distance);
			canRXFlag = 0;
		}
		else
			LCDprintf("Hello World!\n %d mm", distance);
		msleep(100);
  } 
}
