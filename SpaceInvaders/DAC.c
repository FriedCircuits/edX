// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// March 13, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "..//tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000032; // activate port B
  delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_LOCK_R = 0x4C4F434B; 
  GPIO_PORTB_CR_R = 0x3F;           // allow changes to PB0-3
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog on PB
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PB1-3
  GPIO_PORTB_DIR_R = 0x3F;          // 5) PB01-3 Out
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) disable alt funct on PB7-0
  //GPIO_PORTA_PUR_R = 0x08;        //    enable pull-up on PB
  GPIO_PORTB_DEN_R = 0x3F;          // 7) enable digital I/O on PB0-3
	GPIO_PORTB_DR8R_R |= 0x3F; // supposedly for 8mA drive capability
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R &~ 0x0F) | (data & 0x0F);
}
