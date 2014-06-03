#include <hidef.h>      /* common defines and macros */
#include <string.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "spi.h"
#include "timer.h"
#include "canModule.h"

#define BUTF3UP	0b10000000
#define BUTF3DN	0b01000000
#define BUTF2UP	0b00100000
#define BUTF2DN	0b00010000
#define BUTF1UP	0b00000100
#define BUTF1DN	0b00000001

#define LEDF3UP 0b00000010
#define LEDF3DN	0b00001000
#define LEDF2UP	0b00100000
#define LEDF2DN	0b10000000
#define LEDF1UP	0b00010000
#define LEDF1DN	0b01000000

#define NUM0 0b01111101
#define NUM1 0b00000101
#define NUM2 0b00111110
#define NUM3 0b01111010
#define NUM4 0b01100011
#define NUM5 0b01011011
#define NUM6 0b01011111
#define NUM7 0b01110000
#define NUM8 0b01111111
#define NUM9 0b01110011
#define NUMA 0b01110111
#define NUMB 0b01001111
#define NUMC 0b00011101
#define NUMD 0b01101110
#define NUME 0b00011111
#define NUMF 0b00010111

void main(void) {

	CANMessage txMessage;
	unsigned char txBuffer[CAN_MSG_LENGTH];
	unsigned char rxBuffer[CAN_MSG_LENGTH];
	int i;
	
	txMessage.id = BROADCAST_ID;
	txMessage.priority = 0;
	txMessage.length = CAN_MSG_LENGTH;
	txMessage.payload = txBuffer;
	
	timer_init();
	
	SPIinit();
	
	initCan();
	
	for(i = 0; i < 8; i++)
	{
		txBuffer[i] = 0;
		rxBuffer[i] = 0;
	}
	
	EnableInterrupts;
	
	DDRA = 0xFF;
	DDRB = 0x00;
	//DDRP = 0x00;
	
	//PTP = 0xff;
	SPIputc(0x00);


	
	while(1)
	{
		if(canRXFlag)
		{
			// grab the command from the buffer
		//	DisableInterrupts;
			for(i=0; i<8; i++){
			    rxBuffer[i]=canRXData[i];
			}
		//	EnableInterrupts;
			
			if(rxBuffer[0] == 0x00)
				switch(rxBuffer[1])
				{
					case FLOOR_NUM_1:
						SPIputc(NUM1);
						switch(rxBuffer[2])
						{
							case CALL_BTN_UP:
								CLR_BITS(PORTA,LEDF1UP); 
								break;
							case CALL_BTN_DN:
								CLR_BITS(PORTA,LEDF1DN);
								break;
						}
						break;
					case FLOOR_NUM_2:
						SPIputc(NUM2);
						switch(rxBuffer[2])
						{
							case CALL_BTN_UP:
								CLR_BITS(PORTA,LEDF2UP);
								break;
							case CALL_BTN_DN:
								CLR_BITS(PORTA,LEDF2DN);
								break;
						}
						break;
					case FLOOR_NUM_3:
						SPIputc(NUM3);
						switch(rxBuffer[2])
						{
							case CALL_BTN_UP:
								CLR_BITS(PORTA,LEDF3UP);
								break;
							case CALL_BTN_DN:
								CLR_BITS(PORTA,LEDF3DN);
								break;
						}
						break;
				}
			
			canRXFlag = 0;
		}
	
		if (PORTB & BUTF1UP)
		{
			PORTA |= LEDF1UP;
			txBuffer[0] = CALL_BTN_PRESS;
			txBuffer[1] = FLOOR_NUM_1;
			txBuffer[2] = CALL_BTN_UP;
			sendCanFrame(txMessage);
		}
		if (PORTB & BUTF1DN)
		{
			PORTA |= LEDF1DN;
			txBuffer[0] = CALL_BTN_PRESS;
			txBuffer[1] = FLOOR_NUM_1;
			txBuffer[2] = CALL_BTN_DN;
			sendCanFrame(txMessage);
		}
		if (PORTB & BUTF2UP)
		{
			PORTA |= LEDF2UP;
			txBuffer[0] = CALL_BTN_PRESS;
			txBuffer[1] = FLOOR_NUM_2;
			txBuffer[2] = CALL_BTN_UP;
			sendCanFrame(txMessage);
		}
		if (PORTB & BUTF2DN)
		{
			PORTA |= LEDF2DN;
			txBuffer[0] = CALL_BTN_PRESS;
			txBuffer[1] = FLOOR_NUM_2;
			txBuffer[2] = CALL_BTN_DN;
			sendCanFrame(txMessage);
		}
		if (PORTB & BUTF3UP)
		{
			PORTA |= LEDF3UP;
			txBuffer[0] = CALL_BTN_PRESS;
			txBuffer[1] = FLOOR_NUM_3;
			txBuffer[2] = CALL_BTN_UP;
			sendCanFrame(txMessage);
		}
		if (PORTB & BUTF3DN)
		{
			PORTA |= LEDF3DN;
			txBuffer[0] = CALL_BTN_PRESS;
			txBuffer[1] = FLOOR_NUM_3;
			txBuffer[2] = CALL_BTN_DN;
			sendCanFrame(txMessage);
		}
	}
}
