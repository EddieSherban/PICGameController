/*
 * File:   source.c
 * Author: Myles
 *
 * Created on July 9, 2022, 9:08 PM
 */

//-----------CONFIG-----------------------
// FOSC
#pragma config FOSFPR = FRC             // Oscillator (Internal Fast RC (No change to Primary Osc Mode bits))
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

#include <xc.h>
#include "txTimer.h"
#include "uart.h"

#define BIT0 0x1
#define BIT1 0x2
#define BIT2 0x4
#define BIT3 0x8
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40

//switches
#define SW0 BIT1
#define SW1 BIT0
#define SW2 BIT6

//LEDS
#define LED0 BIT1
#define LED1 BIT2



//macros
#define SW0_PRESSED (PORTF&SW0) == SW0
#define SW1_PRESSED (PORTF&SW1) == SW1
#define SW2_PRESSED (PORTF&SW2) == SW2

unsigned char sendDataFlag= 0;

void initIO();

void main(void) {
    
    initIO();  //initialize IO
    initTxTimer(); //initialize TIMER1
    initUART();
    __builtin_enable_interrupts(); //enable global interrupts
    
    char commandLine[3] = "000";
    
  
    
    while(1){
        
        
        //polling switches
        
        if(SW0_PRESSED){
          commandLine[0]= '1';  
        } else {
          commandLine[0]= '0';   
        }
        
        if(SW1_PRESSED){
          commandLine[1]= '1';  
        } else {
          commandLine[1]= '0';  
        }
        
        if(SW2_PRESSED){
           commandLine[2]= '1';   
        } else {
           commandLine[2]= '0';    
        }
        
        
        
        
        if((SW0_PRESSED) || (SW1_PRESSED) || (SW2_PRESSED)){
             LATB|=LED0;
        } else {
             LATB&=~LED0;
        }
        
        if(sendDataFlag){
            LATB^=LED1;
            uartTXString(commandLine);
            uartTXByte('\r');
            uartTXByte('\n');
            sendDataFlag=0;
        }
        
    }
    return;
}

void initIO(){
    ADPCFG=0xFFFF;      //set all IO as digital
    
    //-----outputs-----
    TRISB&=~(LED0|LED1);
    LATB&=~LED1;
    //-----inputs------
    TRISF|=(SW0|SW1|SW2);
   
}

