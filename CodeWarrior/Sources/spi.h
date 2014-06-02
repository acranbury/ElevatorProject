#ifndef _SPIDAC_H
#define _SPIDAC_H

void SPIinit(void);
void SPIcmd(char cmd, char data);
void SPIputc(char cx);

#endif