#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timer.h"
#include "lcd.h"
#include "usonic.h"
#include "utils.h"
#include "canModule.h"
#include "spi.h"

// Elevator Defines

#define ELEV_THRESHOLD 5  // Threshold to have arrived at a floor, in mm.

#define ELEV_1ST 50       // Distance to be at the 1st floor, in mm.
#define ELEV_2ND 100       // Distance to be at the 1st floor, in mm.
#define ELEV_3RD 150       // Distance to be at the 1st floor, in mm.
#define ELEV_4TH 200       // Distance to be at the 1st floor, in mm.

void main(void) {
  
	unsigned char txbuff[8] = "";
	word distance;
	CANMessage message = { 0x00, 0x00, 0x00, {0}};
	unsigned char floor = 0;
	unsigned char lastFloor = 0;

	timer_init();
	LCDinit();

	initCan();

	while (!(CANCTL0 & 0x10));

	CANRFLG = 0xC3;
	CANRIER = 0x01;

	//LCDprintf("Hello World");

	usonic_init();
	
	EnableInterrupts;

	for(;;) {
		LCDclear();
		distance = usonic_getDistance();
		
		
		 
	  if (distance < (ELEV_1ST + ELEV_THRESHOLD) && distance > (ELEV_1ST - ELEV_THRESHOLD))
	    //LCDprintf("1st Floor!\n %d mm", distance);
	    floor = 1;
	    
	  else if (distance < (ELEV_2ND + ELEV_THRESHOLD) && distance > (ELEV_2ND - ELEV_THRESHOLD))
	    //LCDprintf("2nd Floor!\n %d mm", distance);  
	    floor = 2;
	    
	  else if (distance < (ELEV_3RD + ELEV_THRESHOLD) && distance > (ELEV_3RD - ELEV_THRESHOLD))
	    //LCDprintf("3rd Floor!\n %d mm", distance); 
	    floor = 3; 
	    
	  else if (distance < (ELEV_4TH + ELEV_THRESHOLD) && distance > (ELEV_4TH - ELEV_THRESHOLD))
	    //LCDprintf("4th Floor!\n %d mm", distance);  
	    floor = 4;
		
		if (lastFloor != floor) {    
		    txbuff[0] = floor;
      		message.id = ELEVATOR_CAR_ID | FLOOR_1_ID | FLOOR_2_ID | FLOOR_3_ID;
      		message.priority = 0x00;
      		message.length = sizeof(txbuff) - 1;
      		message.payload = txbuff;
		    lastFloor = floor;
		} 
		
		/*
		message.id = ST_ID_100;
		message.priority = 0x00;
		message.length = sizeof(txbuff) - 1;
		message.payload = txbuff; */
		sendCanFrame(message); 
		
		if ( canRXFlag )
		{
			LCDprintf("Floor %d!\n %d mm", canRXData[0], distance);
			canRXFlag = 0;
		}
		else
			LCDprintf("Hello World!\n %d mm", distance);
		msleep(100);
  } 
}
