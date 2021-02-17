/*
 * main.c
 *
 * Created: 18-Feb-21 00:04:47
 *  Author: Seetharamu
 */ 

#include <xc.h>
#define DDR_SPI DDRB
#define DD_CS      PINB2
#define DD_MOSI    PINB3
#define DD_MISO    PINB4
#define DD_SCK     PINB5



void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return Data Register */
	return SPDR;
}
unsigned char spi_TxRx (unsigned char cdata)
{
	// Load data into the buffer
	SPDR = cdata;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF)));   // Return received data

	return(SPDR);
}
int main(void)
{
    while(1)
    {
       DDR_SPI &= ~(1 << DD_CS);

       // receive byte from master
       SPI_SlaveReceive(0x55);

       // receive byte from master
       unsigned char ret = spi_TxRx(0xFF);

       // return slave select to high
       DDR_SPI |= (1 << DD_CS);
    }
}