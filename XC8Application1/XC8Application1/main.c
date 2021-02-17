/*
 * main.c
 *
 * Created: 17-Feb-21 22:17:09
 *  Author: Seetharamu
 */ 

#include <xc.h>
#define DDR_SPI DDRB
#define DD_CS      PINB2
#define DD_MOSI    PINB3
#define DD_MISO    PINB4
#define DD_SCK     PINB5


void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData)
{
	
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)))
	;
}void SPI_masterReceive(void)
{
	SPDR = 0xFF;

	// Wait for reception complete
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}

int main(void)
{
    while(1)
    {
        // drive slave select low
        DDR_SPI &= ~(1 << DD_CS);

        // transmit byte to slave 
        SPI_MasterTransmit(0x55);
        unsigned char ret = SPI_masterReceive(0xFF); // receive byte from slave

        DDR_SPI |= (1 << DD_CS); // chip select high 
    }
}