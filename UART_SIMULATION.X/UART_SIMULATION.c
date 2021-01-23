#include "config2.h"
#include <xc.h>
#define F_OSC 20000000/64


void USART_Init(long baud_rate)
{
    float temp;
    TRISC6=0;		/* Make Tx pin as output*/
    TRISC7=1;  		/* Make Rx pin as input*/

    /* Baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    temp= (( (float) (F_OSC) / (float) baud_rate ) - 1);     
    SPBRG = (unsigned char) temp;	

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

while(RCIF==0);       /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        CREN = 0;
        NOP();
        CREN=1;
    }
    return(RCREG);   /*receive data is stored in RCREG register and return */
}
void receive_string()
{
char rc_data[10];
unsigned int i; /*array index variable */

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
}

void main(){
    while(1) //Infinite loop
    {
      char get_value = USART_RxChar(); 
        
        if (get_value == '1') //If the user sends "1"
        {
            
             
            USART_RxChar(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
        
        if (get_value == '0') //If the user sends "0"
        {
           
                
           USART_TxChar(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
    }
    
}
