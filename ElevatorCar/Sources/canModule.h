#ifndef __CANMODULE__
#define __CANMODULE__

#include "derivative.h"      /* derivative-specific definitions */

#define NO_ERR 1
#define CAN_MSG_LENGTH 8  
#define NUM_FLOORS 3

#define MASK_CODE(id) ((~(id)) >> 16)       
#define ACC_CODE(id) (((id)&0xFFFF0000) >> 16)

/* Acceptance Code Definitions */
#define ACC_CODE_ID100 0x2000   // Hex 0x100 message ID
#define ACC_CODE_ID100_HIGH ((ACC_CODE_ID100 & 0xFF00) >> 8)
#define ACC_CODE_ID100_LOW (ACC_CODE_ID100 & 0x00FF)

/* Mask Code Definitions */
#define MASK_CODE_ST_ID 0x0007
#define MASK_CODE_ST_ID_HIGH ((MASK_CODE_ST_ID & 0xFF00) >> 8)
#define MASK_CODE_ST_ID_LOW (MASK_CODE_ST_ID & 0xFF)

/*
#define MASK_CODE_CONTROLLER_ID 0xFFDF
#define MASK_CODE_ELEVATOR_CAR_ID 0xFFBF
#define MASK_CODE_FLOOR_1_ID 0xFF7F
#define MASK_CODE_FLOOR_2_ID 0xFEFF
#define MASK_CODE_FLOOR_3_ID 0xFDFF
*/

//Node ID Definitions
#define ST_ID_100 0x20000000    //test id

#define CONTROLLER_ID (0x00010000 << 5)   //shifting by 5 bits to fit in 11 bit CAN address
#define ELEVATOR_CAR_ID (0x00020000 << 5)
#define FLOOR_1_ID (0x00040000 << 5)
#define FLOOR_2_ID (0x00080000 << 5)
#define FLOOR_3_ID (0x00100000 << 5)
#define BROADCAST_ID (0xFFE00000)

//Messsage IDs
#define ELEV_LOCATION 0x00
#define CALL_BTN_PRESS 0x01
#define PANEL_BTN_PRESS 0x02
#define APPEND_DISPLAY_CHAR 0x03
#define ERROR_MSG 0xFF

//Elevator directions
#define DIR_UP 1
#define DIR_DOWN 2
#define DIR_STOPPED 3

// Message Contents
#define FLOOR_NUM_1	0x01
#define FLOOR_NUM_2 0x02
#define FLOOR_NUM_3 0x03
#define CALL_BTN_UP 0x01
#define CALL_BTN_DN 0x02

//Elevator panel buttons
#define PANEL_FLOOR_1 0x01
#define PANEL_FLOOR_2 0x02
#define PANEL_FLOOR_3 0x03
#define DOOR_OPEN 0x10
#define DOOR_CLOSE 0x11
#define EMERG_STOP 0xEE

typedef struct {
	unsigned long id;
	unsigned char priority;
	unsigned char length;
	unsigned char *payload;
} CANMessage;

extern unsigned char canRXData[8];
extern char canRXFlag;


void initCan (void);
void sendCanFrame (CANMessage message);

#endif