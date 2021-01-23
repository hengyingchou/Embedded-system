#include "SSD2119_Display_41b.h"
#include "SSD2119_Touch_41b.h"
#include "tm4c1294ncpdt.h"
#include <stdint.h>
#include <stdio.h>
#include "Lab41b_Inits.h"
#include "PLL_Header41b.h"
/*
* CHOU, HENG-YINg
 * 1926322
 * 12/9/2020
*/


void ADC0SS3_Handler(void);

uint32_t ADC_value = 0;

void inti_switch(){
   RCGCGPIO |= (1<<8); // set RCGCGPIO
   GPIODEN_J = 0x3; // Set PJ0 and PJ1 to digital port
   GPIODIR_J &= ~0x3;// set PJ0 and PJ1 to input 
   GPIOCR |= 0x3; // set CR for PJ0 and PJ1
   GPIOPUR |= 0x3; // set PUR for PJ0 and PJ1

  
}


int main()
{
  enum frequency freq ;//= PRESET3; // 60 MHz
  //PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LCD_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  inti_switch();         // Initialize switchs 
  float temp;            // record temperature in celcius 
  float temp2;           // record temperature in fahrenheit
  
  
  while(1){
    if((GPIODATA_J & 0x1) == 0){
       //LCD_PrintString("The frequency is 12 MHZ\n"); // frequency is 12 MHz
       freq = PRESET3;
       PLL_Init(freq); // change frquency
    }  
    if((GPIODATA_J & 0x2) == 0){
       //LCD_PrintString("The frequency is 120 MHZ\n"); // frequency is 120MHz
       freq = PRESET1;
       PLL_Init(freq); // change frquency
    }

    if(freq){
      LCD_SetCursor(0, 0); // lacate sentecne in (0,0)
      temp = 147.5 - (ADC_value/4096.0)*247.5; // compute temperature
      LCD_PrintString("The current temperature is "); // print out sentence
      LCD_PrintFloat(temp); // print out temperature
      LCD_PrintString("C, ");  
      
      temp2 = temp*1.8 + 32; // change from C to F

      LCD_PrintFloat(temp2); // print temperature
      LCD_PrintString("F."); 
      LCD_PrintString("\n"); // change line
      if(freq == PRESET1){ // print out system frequency 120 HZ
        LCD_PrintString("The current clock frequency is ");
        LCD_PrintInteger(120);
        LCD_PrintString("MHz \n");1
      }
      if(freq == PRESET3){// print out system frequency 12 HZ
        LCD_PrintString("The current clock frequency is ");
        LCD_PrintInteger(12);
        LCD_PrintString("MHz \n");
      }
      
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