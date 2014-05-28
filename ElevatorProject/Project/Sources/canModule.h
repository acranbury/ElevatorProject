#ifndef __CANMODULE__
#define __CANMODULE__

#include "derivative.h"      /* derivative-specific definitions */

/* Mask Code Definitions */
#define MASK_CODE_ST_ID 0x0007
#define MASK_CODE_ST_ID_HIGH ((MASK_CODE_ST_ID & 0xFF00) >> 8)
#define MASK_CODE_ST_ID_LOW (MASK_CODE_ST_ID & 0xFF)

typedef struct {
	unsigned char id;
	unsigned char priority;
	unsigned char length;
	unsigned char *payload;
} MSG;


void initCan (void);
void sendCanFrame (MSG message);

#endif