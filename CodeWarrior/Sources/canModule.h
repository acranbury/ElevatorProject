#ifndef __CANMODULE__
#define __CANMODULE__

#include "derivative.h"      /* derivative-specific definitions */

#define NO_ERR 1

/* Acceptance Code Definitions */
#define ACC_CODE_ID100 0x2000
#define ACC_CODE_ID100_HIGH ((ACC_CODE_ID100 & 0xFF00) >> 8)
#define ACC_CODE_ID100_LOW (ACC_CODE_ID100 & 0x00FF)

/* Mask Code Definitions */
#define MASK_CODE_ST_ID 0x0007
#define MASK_CODE_ST_ID_HIGH ((MASK_CODE_ST_ID & 0xFF00) >> 8)
#define MASK_CODE_ST_ID_LOW (MASK_CODE_ST_ID & 0xFF)

// ID Definition
#define ST_ID_100 0x20000000

typedef struct {
	unsigned char id;
	unsigned char priority;
	unsigned char length;
	unsigned char *payload;
} CANMessage;

extern unsigned char canRXData[8];
extern char canRXFlag;


void initCan (void);
void sendCanFrame (CANMessage message);

#endif