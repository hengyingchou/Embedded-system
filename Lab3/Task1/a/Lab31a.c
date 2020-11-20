/*
* CHOU, HENG-YINg
* 1926322
* 11/20/2020
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab31a_Inits.h"
#include "PLL_Header31a.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

void ADC0SS3_Handler(void);

uint32_t ADC_value = 0;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    resistance = (ADC_value/4095.0)*10.0;
    printf("%f\n",resistance);
    //printf("resistance: %f\n",resistance);
    //printf("good2");
    // 5.2: Change the pattern of LEDs based on the resistance
    if (resistance < 2.5) {
      GPIODATA_N = (1<<1); // Ligth LED1
      GPIODATA_F = 0x0;
      
    } else if (resistance < 5.0) {
      GPIODATA_N = 0x3; // Light up LED 2
      GPIODATA_F = 0x0;
    } else if (resistance < 7.5) {
      GPIODATA_N = 0x3; // Light up LED 3
      GPIODATA_F = (1<<4) ;
    } else {
      GPIODATA_N = 0x3; // Light up LED 4
      GPIODATA_F = 0x11;
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