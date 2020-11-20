/*
 * CHOU, HENG-YINg
 * 1926322
 * 11/20/2020
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab32b_Inits.h"
#include "PLL_Header32b.h"
void ADC0SS3_Handler(void);

uint32_t ADC_value = 0;
void printChar(char c){
 
  //print the char from UART2 << 5
  while((UART2_FR &(1<<5)) != 0);
  UART2_DR =  c;

  
}

void printString(char* string)
{
  // Print the string
  while(*string)
  {
    printChar(*(string++));
  }
  
  
}
char readChar(void){
  // read the word I type from UART2 <<4
  char c;
  while((UART2_FR & (1<<4)) != 0);
  c = UART2_DR;
  return c;
}

int main()
{
  enum frequency freq = PRESET1;
  char str[20];
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  char c; 
  while(1){
    
       PLL_Init(freq);
       init_UART();
       printString("Type a charter here:\n\r");
       c = readChar(); // read the word
       printString("The charater you type is: ");
       printChar(c);
       printString("\n\r");
       
  
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

