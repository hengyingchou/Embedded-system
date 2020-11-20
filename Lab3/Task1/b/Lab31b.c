
/*
* CHOU, HENG-YINg
* 1926322
* 11/20/2020
*/
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
#include <stdint.h>
#include <stdio.h>
#include "Lab31b_Inits.h"
#include "PLL_Header31b.h"

void ADC0SS3_Handler(void);

uint32_t ADC_value = 0;

void inti_switch(){
   RCGCGPIO |= (1<<8); // set RCGCGPIO
   GPIODEN_J = 0x3; // Set PJ0 and PJ1 to digital port
   GPIODIR_J &= ~0x3;// set PJ0 and PJ1 to input 
   GPIOCR |= 0x3; // set CR for PJ0 and PJ1
   GPIOPUR |= 0x3; // set PUR for PJ0 and PJ1

  
}
int main(void) {
  // Select system clock frequency preset
  enum frequency freq ;//= PRESET3; // 60 MHz
  //PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  inti_switch();
  float resistance;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    if((GPIODATA_J & 0x1) == 0){
       printf("The frequency is 12 MHZ\n"); // frequency is 12 MHz
       freq = PRESET3;
       PLL_Init(freq);
    }  
    if((GPIODATA_J & 0x2) == 0){
       printf("The frequency is 120 MHZ\n"); // frequency is 120MHz
       freq = PRESET1;
       PLL_Init(freq);
    }
    if(freq){
      resistance = 147.5 - (ADC_value/4096.0)*247.5;
      printf("Temperature is : %f\n",resistance);
    }
    
    
    
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag;
  ADCISC = (1<<3);
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3; 
}