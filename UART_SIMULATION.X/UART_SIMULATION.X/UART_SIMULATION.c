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

char *str;                          //Global variable used for interrupt

void tx_str(char *a)
{
    PIE1bits.TXIE = 1;                       //Enable transmission interrupt
    str = a;                        //pointing str pointer to data to send
    PIR1bits.TXIF = 1;                       //Manually enabling interrupt
    while(*(str-1));                //Wait for transmission of complete string
    PIE1bits.TXIE = 0;                       //Disable transmission interrupt
    //tx_char(0x0D);                  //New Line
}
__interrupt() void ISR(void)
{
    char a;
    
    if(PIR1bits.TXIF==1)                     //Polling for transmission interrupt
    {
        TXREG=*str;                 //Load data to TXREG register
        str++;                      //increment pointer to next data
    }
}
char rx_char(void)
{
    while(!PIR1bits.RCIF);                   //Wait till RCREG is full
    return RCREG;                   //Return value in received data
}

void tx_char(char a)
{
    TXREG=a;                        //Load TXREG register with data to be sent
    while(!TXSTAbits.TRMT);                   //Wait till transmission is complete
}

void main()
{ 
    INTCONbits.GIE=1;//global interrupt
    INTCONbits.PEIE=1;
    PIR1bits.RCIF=0;
    PIE1bits.RCIE=1;//enable received interrupt 
    while(1){
        char out;
        char rc_data[100];
        unsigned int i; 
        USART_Init();    //out = USART_ReceiveChar();
        for(i=0;;i++)
        {
            while(!PIR1bits.RCIF);
            rc_data[i]=RCREG;
            if(rc_data[i]=='\r') //character is received until end of the string received 
            {
                rc_data[i]='\0';
                break;
            }
        } 
        for(i=0;i<100;i++)
        {
            tx_char(rc_data[i]);
        }
    }   
}