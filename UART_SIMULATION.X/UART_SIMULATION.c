#include "config2.h"
#include <xc.h>
#define F_OSC 20000000/64


void USART_Init()
{
    //float temp;
    TRISCbits.TRISC6=0;		/* Make Tx pin as output*/
    TRISCbits.TRISC7=1;  		/* Make Rx pin as input*/

    /* Baud rate=9600, SPBRG = (F_OSC /(64*9600))-1*/
    //temp= (( (float) (F_OSC) / (float) baud_rate ) - 1);     
    SPBRG = 32;	

    TXSTA = 0x20;  	/* Enable Transmit(TX) */ 
    RCSTA = 0x90;  	/* Enable Receive(RX) & Serial */
}
void USART_TxChar(char out)
{        
        while(TXIF==0);            /*wait for transmit interrupt flag*/
        TXREG=out;                 /*transmit data via TXREG register*/    
}
char USART_RxChar()
{

while(RCIF==0)
    ;       /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        RCSTA1bits.CREN = 0;
        NOP();
        RCSTA1bits.CREN=1;
    }
    return(RCREG);   /*receive data is stored in RCREG register and return */
}

void main()
{
    
char out;
char rc_data[100];
unsigned int i; /*array index variable */
USART_Init();
//out = USART_ReceiveChar();
for(i=0;;i++)
{
    while(!RCIF);
    rc_data[i]=RCREG; 
    if(rc_data[i]=='\r') /*character is received until end of the string received */
    {
        rc_data[i]='\0';
        break;
    }
} 
for(i=0;i<100;i++)
{
    USART_TxChar(rc_data[i]);
}
    
}