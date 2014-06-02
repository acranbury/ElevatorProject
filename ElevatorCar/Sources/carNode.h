#ifndef __CARNODE__
#define __CARNODE__

#include "utils.h"

#define FLOOR1  0x01
#define FLOOR2  0x02
#define FLOOR3  0x04
#define DRCLOSE   0x08
#define DROPEN    0x10
#define ESTOP     0x20

void initCarLoop (void);

void runCarLoop (void);


#endif