#include "derivative.h"
#include "spi.h"
#include "utils.h"
#define SPICR1_INIT 0b01010000
#define SPI1MBAUD	0b00000010

// initialize SPI module
void SPIinit(void){
	//configure SPI port for:
	// SPI on, no intr, master, CPOL-0, CPHA=0, MSB 1st
	SPICR1 = SPICR1_INIT;
	SPIBR = SPI1MBAUD;
}

// put a command to the SPI module
void SPIcmd(char cmd, char data){
// undefined utility macros
	CLR_BITS(SPICR1, SPICR1_SSOE_MASK);
	
	SPIputc(LO_NYBBLE(cmd) | HI_NYBBLE(data));
	SPIputc(LO_NYBBLE(data));
	
	SET_BITS(SPICR1, SPICR1_SSOE_MASK);

	
}

// put a byte on the SPI bus
void SPIputc( unsigned char cx ){
	unsigned char temp;			/* dummy variable to take read data */
     	
	while(!(SPISR & SPISR_SPTEF_MASK)); 	/* wait until write is permissible */
     	SPIDR = cx;              			/* output the byte to the SPI */
     	
	while(!(SPISR & SPISR_SPIF_MASK));  	/* wait until write operation is complete */
	temp = SPIDR;			/* clear the SPIF flag */
}

