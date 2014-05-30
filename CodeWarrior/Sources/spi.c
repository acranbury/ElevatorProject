#include "derivative.h"
#include "spi.h"
#include "utils.h"
#define SPICR1_INIT 0b01010000
#define SPI1MBAUD	0b00000010

// initialize SPI module
void SPIinit(void){
	// baud rate divisor for 1Mbps with 8 MHz E-clock
	//SPIBD = 0x02; should be SPIBR = 0x02, which is already done later

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
void SPIputc( char cx ){
	char temp;			/* dummy variable to take read data */
     	
	while(!(SPISR & SPISR_SPTEF_MASK)); 	/* wait until write is permissible */
     	SPIDR = cx;              			/* output the byte to the SPI */
     	
	while(!(SPISR & SPISR_SPIF_MASK));  	/* wait until write operation is complete */
	temp = SPIDR;			/* clear the SPIF flag */
}

