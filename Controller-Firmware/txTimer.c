/*
 * File:   txTimer.c
 * Author: Myles
 *
 * Created on August 2, 2022, 12:21 PM
 */

#include "txTimer.h"


void initTxTimer(){
    T1CONbits.TON=0;   //shut off timer for configuration
    T1CONbits.TSIDL=0; //ensure timer runs during idle mode
    T1CONbits.TGATE=0; //disable gated accumulation mode
    T1CONbits.TCKPS= DIV_0; //divide system clock by 1 (no prescaling)
    T1CONbits.TSYNC= 0; //disable external clock synchronization
    T1CONbits.TCS= 0;
    
    PR1= 0x75C2;
    
    IFS0bits.T1IF= 0; //clear any pending interrupts before enabling interrupts
    IEC0bits.T1IE= 1; //enable interrupts on timer 1
    T1CONbits.TON=1; //turn on timer
}


void __attribute__((interrupt(auto_psv))) _T1Interrupt(void){
  sendDataFlag= 1;
  IFS0bits.T1IF= 0;
}
