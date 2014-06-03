#include <string.h>
#include "canModule.h"

unsigned char canRXData[8];
char canRXFlag;

void initCan (){
	CANCTL0 = 0x01;                 /* Enter Initialization Mode */
	while (! (CANCTL1&0x01)) {};    /* Wait for Initialization Mode
									   acknowledge (INITRQ bit = 1) */
											
	CANCTL1 = 0b11000000;
	CANBTR0 = 0b01000000;     //sjw 0b01, prescaler = 1
	CANBTR1 = 0b00010100;     //use tseg2 = 2, tseg1 = 5

	/* Acceptance Filters */
	CANIDAC = 0x10;                     // Set four 16-bit Filters
	
	CANIDAR0 = 0xFF;    //ACC_CODE_ID100_HIGH; 	//|\ 16-bit Filter 0
	CANIDMR0 = 0x00; 	//| \__ Accepts Standard Data Frame CANMessage
	CANIDAR1 = 0xFF;    //ACC_CODE_ID100_LOW;		//| / with ID 0x100
	CANIDMR1 = 0x00; 	//|/
	
    CANIDAR2 = (ACC_CODE(FLOOR_1_ID) >> 8) & 0xFF;	   	//|\ 16-bit Filter 1
	CANIDMR2 = (MASK_CODE(FLOOR_1_ID) >> 8) & 0xFF;		//| \__ Accepts Standard Data Frame CANMessage
	CANIDAR3 = ACC_CODE(FLOOR_1_ID) &0xFF;				//| / with ID 0x100
	CANIDMR3 = MASK_CODE(FLOOR_1_ID) & 0xFF;		    //|/
	
	CANIDAR4 = (ACC_CODE(FLOOR_2_ID) >> 8) & 0xFF;	   	//|\ 16-bit Filter 2
	CANIDMR4 = (MASK_CODE(FLOOR_2_ID) >> 8) & 0xFF;	    //| \__ Accepts Standard Data Frame CANMessage
	CANIDAR5 = ACC_CODE(FLOOR_2_ID) &0xFF;			    //| / with ID 0x100
	CANIDMR5 = MASK_CODE(FLOOR_2_ID) & 0xFF;		 	//|/
	
	CANIDAR6 = (ACC_CODE(FLOOR_3_ID) >> 8) & 0xFF;	    //|\ 16-bit Filter 3
	CANIDMR6 = (MASK_CODE(FLOOR_3_ID) >> 8) & 0xFF;	 	//| \__ Accepts Standard Data Frame CANMessage
	CANIDAR7 = ACC_CODE(FLOOR_3_ID) &0xFF;				//| / with ID 0x100
	CANIDMR7 = MASK_CODE(FLOOR_3_ID) & 0xFF;		 	//|/      
	
	CANCTL0 = 0x00;                   /* Exit Initialization Mode Request */
	while ((CANCTL1 & 0x00) != 0) {}  /* Wait for Normal Mode */
}

void sendCanFrame (CANMessage message){
  int index;
	unsigned char txbuffer;
	if (!CANTFLG)                     /* Is Transmit Buffer full?? */
		return;// ERR_BUFFER_FULL;
		
	CANTBSEL = CANTFLG;               /* Select lowest empty buffer */
	txbuffer = CANTBSEL;              /* Backup selected buffer */
	
	/* Load Id to IDR Register */
	CANTXIDR0 = (unsigned char)((message.id & 0xFF000000) >> 24);
	CANTXIDR1 = (unsigned char)((message.id & 0xFF0000) >> 16);
	CANTXIDR2 = (unsigned char)((message.id & 0xFF00) >> 8);
	CANTXIDR3 = (unsigned char)(message.id & 0xFF);
	//*((unsigned long *) ((unsigned long)(&CANTXIDR0))) = message.id;
	
	for (index = 0; index < message.length; index++) {
	   /* Load data to Tx buffer Data Segment Registers */
	  *(&CANTXDSR0 + index) = message.payload[index];
	} 
	
	CANTXDLR = message.length;            /* Set Data Length Code */
	CANTXTBPR = message.priority;         /* Set Priority */
	CANTFLG = txbuffer;               /* Start transmission */
	
	/* Wait for Transmission completion */
	while ( (CANTFLG & txbuffer) != txbuffer); 
}

interrupt VectorNumber_Vcanrx void can_ISR(void)
{
	unsigned char length, index;
	
	length = (CANRXDLR & 0x0F);
	//strncpy(canRXData, (char*)CANRXDSR0, length);
	for (index = 0; index < length; index++)
		canRXData[index] = *(&CANRXDSR0 + index); // Get received data
	
	CANRFLG = 0x01;		// Clear RXF
	canRXFlag = 1;
}