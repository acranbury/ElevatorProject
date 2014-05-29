#include "canModule.h"

unsigned char canRXData[8];
char canRXFlag;

void initCan (){
	CANCTL0 = 0x01;                 /* Enter Initialization Mode */
	while (! (CANCTL1&0x01)) {};    /* Wait for Initialization Mode
											               acknowledge (INITRQ bit = 1) */
											
	CANCTL1 = 0xA0; 
	CANBTR0 = 0xC7;
	CANBTR1 = 0x3A;

	/* Acceptance Filters */
	CANIDAC = 0x10;                     // Set four 16-bit Filters
	
	CANIDAR0 = ACC_CODE_ID100_HIGH; 	  //|\ 16-bit Filter 0
	CANIDMR0 = MASK_CODE_ST_ID_HIGH; 	  //| \__ Accepts Standard Data Frame CANMessage
	CANIDAR1 = ACC_CODE_ID100_LOW; 	    //| / with ID 0x100
	CANIDMR1 = MASK_CODE_ST_ID_LOW; 	  //|/
	
	/* Acceptance Filters */
	CANIDAC = 0x10;                     // Set four 16-bit Filters
	
	CANIDAR2 = 0x00; 					          //|\ 16-bit Filter 1
	CANIDMR2 = MASK_CODE_ST_ID_HIGH; 	  //| \__ Accepts Standard Data Frame CANMessage
	CANIDAR3 = 0x00; 					          //| / with ID 0x100
	CANIDMR3 = MASK_CODE_ST_ID_LOW; 	  //|/
	
	CANIDAR4 = 0x00; 					          //|\ 16-bit Filter 2
	CANIDMR4 = MASK_CODE_ST_ID_HIGH; 	  //| \__ Accepts Standard Data Frame CANMessage
	CANIDAR5 = 0x00; 					          //| / with ID 0x100
	CANIDMR5 = MASK_CODE_ST_ID_LOW; 	  //|/
	
	CANIDAR6 = 0x00; 					          //|\ 16-bit Filter 3
	CANIDMR6 = MASK_CODE_ST_ID_HIGH; 	  //| \__ Accepts Standard Data Frame CANMessage
	CANIDAR7 = 0x00; 					          //| / with ID 0x100
	CANIDMR7 = MASK_CODE_ST_ID_LOW; 	  //|/
	
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
	*((unsigned long *) ((unsigned long)(&CANTXIDR0))) = message.id;
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
	for (index = 0; index < length; index++)
		canRXData[index] = *(unsigned char *)(CANRXDSR0 + index); // Get received data
	
	CANRFLG = 0x01;		// Clear RXF
	canRXFlag = 1;
}