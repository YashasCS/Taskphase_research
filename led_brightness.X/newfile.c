#include <xc.h>
#include "config.h"
#define REPEAT_COUNT 10000 

void PIC_Init( void )
{ 
    INTCON = 1; /* Disable all interrupts */
    INTCON3 = 1;
    PIE1 = 1;
    PIE2 = 1;

    
    //ADCON1 = 0x02; 
    ADCON1 = 0x0F; /* set all ADC inputs for digital I/O */
    ADCON0 = 0x00; /* Turn off ADC */

    /* Initialize the interrupt system */
    RCONbits.IPEN = 1; 
    INTCONbits.PEIE = 1; /* Disable peripheral interrupt sources */
    INTCONbits.GIE = 1; /* Disable interrupts */
}


void main ( void )
{
   
 TRISA = 0; // make all of PORTA inputs 
 TRISB = 0x00;

 PORTBbits.RB7=0;
 PORTAbits.RA1=0;

while(1)

    {
 
 PORTAbits.RA1^=PORTAbits.RA1;//Toggle the pin1 of port A

 PORTBbits.RB7=1;// for checking the timer

 }
}

void T0Delay()

 {

 T0CON=0x01;//timer 0,16bit mode,1:4 pre-scalar

 T0CONbits.T08BIT=0; //O FOR 16 BIT 

 TMR0H=0x85; //load TH0(1001 1100)
 TMR0L=0xEE; //LOAD TL0 ()

 T0CONbits.TMR0ON=1; //START TIMER

while(INTCONbits.TMR0IF==0); 

 PORTBbits.RB7=0;// FOR CHECKING TIMER
 T0CONbits.TMR0ON=0;//TURN OFF TIMER
 INTCONbits.TMR0IF=0;// CLEAR TF0

    }