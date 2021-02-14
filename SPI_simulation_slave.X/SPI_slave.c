#include "xc.h"
#include "newxc8_header.h"


#define CS LATA5
#define LED LATD

void SPI_Write(unsigned char);
void SPI_Init_Slave();
unsigned char SPI_Read();
void MSdelay(unsigned int);


void main() 
{
    int i;
    
    TRISD =0;			/* PORT initialize as output */
    OSCCON = 0x72;		/* Use internal osc. frequency 8 MHz */    
    INTCON2bits.RBPU=0;		/* Enable internal Pull-up of PORTB */
             
    
    while(1)
    {
     LED = SPI_Read();       
    }
}

void SPI_Init_Slave()
{
    /* PORT definition for SPI pins*/    
    TRISBbits.TRISB0 = 1;	/* RB0 as input(SDI) */
    TRISBbits.TRISB1 = 1;	/* RB1 as output(SCK) */
    TRISAbits.TRISA5 = 1;	/* RA5 as a output(SS') */
    TRISCbits.TRISC7 = 0;	/* RC7 as output(SDO) */

    /* To initialize SPI Communication configure following Register*/
    CS = 1;
    SSPSTAT=0x40;		/* Data change on rising edge of clk , BF=0*/
    SSPCON1=0x24;		/* Slave mode,Serial enable, idle state
				high for clk */ 
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
    data_flush=SSPBUF;		/* Flush received data */
}

unsigned char SPI_Read()
{    
    SSPBUF=0xff;		/* Copy flush data in SSBUF */
    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;		/* Clear SSPIF flag */
    return(SSPBUF);		/* Return received data.*/   
}

void MSdelay(unsigned int val)	
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);
}