/*
 * File:   uart.c
 * Author: Myles
 *
 * Created on August 2, 2022, 3:08 PM
 */


#include "uart.h"


void initUART(){
    U1MODEbits.UARTEN= 0; //disable UART
    U1MODEbits.USIDL=0; //ensure operations continues in idle mode
    U1MODEbits.ALTIO=1; //use alternate I/O (pin 15 & 16 for TX & RX, respectively)
    U1MODEbits.LPBACK= 0; //disable loop-back mode
    U1MODEbits.PDSEL= 0;
    U1MODEbits.WAKE= 0;
    U1MODEbits.ABAUD= 1;
    U1MODEbits.STSEL=0;
    
    U1BRG= 49; //set baud rate as 9600
    
    
    
    
    U1MODEbits.UARTEN= 1; //enable UART
    U1STAbits.UTXEN=1;
}

void uartTXByte(unsigned char byte){
    while(U1STAbits.TRMT == 0);
    U1TXREG= byte;
   }


void uartTXString(unsigned char *line){
    unsigned int i= 0;
    
    
    while(*(line+i) != '\0'){
    uartTXByte(*(line+i));
    i++;
    }
    
}
