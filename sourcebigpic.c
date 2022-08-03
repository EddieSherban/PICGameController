/*
 * File:   source.c
 * Author: Myles, Eddie
 *
 * Created on July 22, 2022, 2:10 PM
 */


#include <xc.h>

#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

#define BIT0 0x1
#define BIT1 0x2
#define BIT2 0x4
#define BIT3 0x8
#define BIT4 0x10
#define BIT10 0x400

void main(void) {
    TRISB = TRISB & ~BIT2; //set RB2 as output (1 as input)
    PORTB = PORTB | BIT2;  //honestly not sure what this does
    LATB = LATB | BIT2;    //set output of RB2 as high
    
    __builtin_enable_interrupts(); //enable global interrupts
    
    //want to enable interrupts 
    
}

