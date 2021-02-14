#include "xc.h"
#include "newxc8_header.h"

#define CS LATA5

void SPI_Write(unsigned char);
void SPI_Init_Master();
unsigned char SPI_Read();
void MSdelay(unsigned int);

void main() 
{
    int i;
    OSCCON = 0x72;		/* Use internal frequency 8 MHz */    
    INTCON2bits.RBPU=0;		/* Enable internal Pull-up of PORTB */
    SPI_Init_Master();		/* Initialize SPI communication */
    MSdelay(10);
    
    while(1)
    {
        CS = 0;
        for(i=0;i<=15;i++)	/* Start counter */
        {
            SPI_Write(i);	/* Send counter value to Slave */
            MSdelay(1000);
        }
        CS = 1;
        i=0;
    
    }
}

void SPI_Init_Master()
{
    /* PORT definition for SPI pins*/    
    TRISBbits.TRISB0 = 1;	/* RB0 as input(SDI) */
    TRISBbits.TRISB1 = 0;	/* RB1 as output(SCK) */
    TRISAbits.TRISA5 = 0;	/* RA5 as a output(SS') */
    TRISCbits.TRISC7 = 0;	/* RC7 as output(SDO) */

    /* To initialize SPI Communication configure following Register*/
    CS = 1;
    SSPSTAT=0x40;		/* Data change on rising edge of clk,BF=0*/
    SSPCON1=0x22;		/* Master mode,Serial enable,
				idle state low for clk, fosc/64 */ 
    PIR1bits.SSPIF=0;

    /* Disable the ADC channel which are on for multiplexed pin
    when used as an input */    
    ADCON0=0;			/* This is for de-multiplexed the SCL
				and SDI from analog pins*/
    ADCON1=0x0F;		/* This makes all pins as digital I/O */    
}

void SPI_Write(unsigned char x)
{
    unsigned char data_flush;
    SSPBUF=x;			/* Copy data in SSBUF to transmit */

    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;		/* Clear SSPIF flag */
    data_flush=SSPBUF;		/* Flush the data */
}

unsigned char SPI_Read()
{    
    SSPBUF=0xff;		/* Copy flush data in SSBUF */
    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;
    return(SSPBUF);		/* Return received data.*/   
}

/*************************Delay Function****************************/
void MSdelay(unsigned int val)	/* Delay of 1 ms for 8MHz Freq. */
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);
}