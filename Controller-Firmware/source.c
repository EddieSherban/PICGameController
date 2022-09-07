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

#define CMD_ARR_SZ 15

//switches
#define SW_UP BIT1
#define SW_LEFT BIT0
#define SW_RIGHT BIT6
#define SW_DOWN BIT2
#define SW_A BIT3
#define SW_B BIT4
#define SW_X BIT5
#define SW_Y BIT0
#define SW_LT BIT1
#define SW_RT BIT2
#define SW_START BIT3
#define SW_SEL BIT4
//LEDS
#define LED0 BIT1
#define LED1 BIT2



//macros
#define SW_UP_PRESSED (PORTF&SW_UP) == SW_UP
#define SW_LEFT_PRESSED (PORTF&SW_LEFT) == SW_LEFT
#define SW_RIGHT_PRESSED (PORTF&SW_RIGHT) == SW_RIGHT
#define SW_DOWN_PRESSED (PORTF&SW_DOWN) == SW_DOWN
#define SW_A_PRESSED (PORTF&SW_A) == SW_A
#define SW_B_PRESSED (PORTF&SW_B) == SW_B
#define SW_X_PRESSED (PORTF&SW_X) == SW_X
#define SW_Y_PRESSED (PORTE&SW_Y) == SW_Y
#define SW_LT_PRESSED (PORTE&SW_LT) == SW_LT
#define SW_RT_PRESSED (PORTE&SW_RT) == SW_RT
#define SW_START_PRESSED (PORTE&SW_START) == SW_START
#define SW_SEL_PRESSED (PORTE&SW_SEL) == SW_SEL

unsigned char sendDataFlag= 0;

void initIO();

void main(void) {
    
    initIO();  //initialize IO
    initTxTimer(); //initialize TIMER1
    initUART();
    __builtin_enable_interrupts(); //enable global interrupts
    
    char commandLine[] = "000000000000\r\n";
    
  
    
    while(1){
        
        
        //polling switches
        
        if(SW_UP_PRESSED){
          commandLine[0]= '1';  
        } else {
          commandLine[0]= '0';   
        }
        
        if(SW_LEFT_PRESSED){
          commandLine[1]= '1';  
        } else {
          commandLine[1]= '0';  
        }
        
        if(SW_RIGHT_PRESSED){
           commandLine[2]= '1';   
        } else {
           commandLine[2]= '0';    
        }
        
        if(SW_DOWN_PRESSED){
           commandLine[3]= '1';  
        } else {
           commandLine[3]= '0';   
        }
        
        if(SW_A_PRESSED){
           commandLine[4]= '1';  
        } else {
           commandLine[4]= '0';   
        }
        
        if(SW_B_PRESSED){
           commandLine[5]= '1';  
        } else {
           commandLine[5]= '0';   
        }
        
        if(SW_X_PRESSED){
           commandLine[6]= '1';  
        } else {
           commandLine[6]= '0';   
        }
        
        if(SW_Y_PRESSED){
           commandLine[7]= '1';  
        } else {
           commandLine[7]= '0';   
        }
        
        if(SW_LT_PRESSED){
           commandLine[8]= '1';  
        } else {
           commandLine[8]= '0';   
        }
                
        if(SW_RT_PRESSED){
           commandLine[9]= '1';  
        } else {
           commandLine[9]= '0';   
        }
        
        if(SW_START_PRESSED){
           commandLine[10]= '1';  
        } else {
           commandLine[10]= '0';   
        }
        
        if(SW_SEL_PRESSED){
           commandLine[11]= '1';  
        } else {
           commandLine[11]= '0';   
        }
                
        if((SW_UP_PRESSED) || (SW_LEFT_PRESSED) || (SW_RIGHT_PRESSED)){
             LATB|=LED0;
        } else {
             LATB&=~LED0;
        }
        
        
        if(sendDataFlag){
            LATB^=LED1;
            uartTXString(commandLine);
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
    TRISF|=(SW_UP|SW_LEFT|SW_RIGHT|SW_DOWN|SW_A|SW_B|SW_X);
    TRISE|= (SW_Y|SW_LT|SW_RT|SW_START|SW_SEL);
}

