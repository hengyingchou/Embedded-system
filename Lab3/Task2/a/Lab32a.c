/*
 * CHOU, HENG-YINg
 * 1926322
 * 11/20/2020
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab3_Inits.h"
#include "PLL_Header.h"
void ADC0SS3_Handler(void);

uint32_t ADC_value = 0;
void printChar(char c){
  // print out each character
  while((UART0_FR &(1<<5)) != 0);
  UART0_DR =  c;

  
}

void printString(char* string)
{
   // print out the string
  while(*string)
  {
    printChar(*(string++));
  }
  
  
}
int main()
{
  enum frequency freq ;
  char str[20];
  inti_switch();
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  //for(int i = 0 ; i < 5 ; i++)printString("good\n\r");
  float c; 
  while(1){
    
    if((GPIODATA_J & 0x1) == 0){

       freq = PRESET3;
       PLL_Init(freq); //120 MHZ
       init_UART(78,8); // Calculate IBRD and FBRD in 12 MHz
       printString("The frequency is 12 MHZ\n\r");
    }  
    if((GPIODATA_J & 0x2) == 0){
       
       freq = PRESET1;
       PLL_Init(freq); //120MHz
       init_UART(781,16); // Calculate IBRD and FBRD in 120 MHz
       printString("The frequency is 120 MHZ\n\r");
    }
    if(freq){
      c = 147.5 - (ADC_value/4096.0)*247.5;
      printf("%lf\n",c);
      sprintf(str,"%f",c);
      printString("temperture is ");
      printString(str);
      printString("\n\r");
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

