
/**
 * EE/CSE 474: Lab3 drivers starter code
 * CHOU, HENG-YINg
 * 1926322
 * 11/20/2020
 */

#include "PLL_Header32a.h"
#include "Lab32a_Inits.h"

// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE




int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.
  // YOUR CODE HERE
  volatile unsigned short delay = 0 ;

  RCGCGPIO |= (1<<12) | (1<<5); // Enable PortF and Port N GPIO
  delay ++ ; // Delay 2 more cycles before access Timer registers
  delay ++ ; // Refer to Page. 756 of Datasheet for info
  GPIODEN_F |= 0x11; // Set PF0 and PF4 to digital port
  GPIODIR_F |= 0x11; // Set PF4 and PF0 to output
  GPIODEN_N |= 0X3; //Set PN0 and PN4 to digitial port
  GPIODIR_N |= 0x3; // Set PN0 and PF4 to output
  GPIODATA_F |= 0x0; // clean PF0 and PF4
  GPIODATA_N |= 0x0; // clean PN0 and PN4

}

void ADCReadPot_Init(void) {
  volatile unsigned short delay = 0 ;
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= (1<<0);
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  delay++;
  delay++;
  delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC = (0x1); 
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  //RCGCGPIO |= (1<<4); // Port E
  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;
  delay++;
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  //GPIOAFSEL |= (1<<0); // PE1
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  //GPIODEN_E &= ~(1<<0); // PE1
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  //GPIOAMSEL |= (1<<0); // PE1
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS &= ~(1<<3); //ss3 disable
  // 2.12: Select timer as the trigger for SS3
   ADCEMUX = (0x5<<12);
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSMUX3 = 0x2; 
  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3 = 0x6; 
  // 2.15: Set the SS3 interrupt mask
  ADCIM |= (1<<3);
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  ADCISC |= (1<<3);
  NVIC_EN_0 |= (0x1<<17);
  // 2.17 setting up ADCSSOP3 for temperature read
  ADCSSCTL3 |= (1<<3); 
  // setting up ADCSSTSH3 for Hold width
  ADCSSTSH3 = 0x6;
  // 2.17: Enable ADC0 SS3
  ADCACTSS |= (1<<3);
}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  // YOUR CODE HERE
  RCGCTIMER |= (1<<0); // configure timer
  GPTMCTL &=~(1<<0); //TAEN is set 0. Timer A is disabled.
  GPTMCFG = 0x00000000; //Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
  GPTMCFG = 0x0; //GPTM Configuration Register
  GPTMADCEV |=(1<<0); // // configure ADC Event
  GPTMTAMR |= (0x2<<0); //TAMR is set 0x2. Periodic Timer mode is used
  GPTMTAMR &= ~(1<<4); // configure TAMR          
  GPTMTAILR = 60000000; // 60MHZ
  GPTMCTL |= (1<<5); // set up for subtimerA
  GPTMCTL |=(1<<0);
}
void inti_switch(void){
   RCGCGPIO |= (1<<8); // configure GPIO
   GPIODEN_J = 0x3; // Set PJ0 and PJ1 to digital port
   GPIODIR_J &= ~0x3; // set PJ0 and PJ1 to input 
   GPIOCR |= 0x3; // configure GPIOCUR for PJ0 and PJ1
   GPIOPUR |= 0x3; // configure GPIOPUR for PJ0 and PJ1

  
}
void init_UART(int IBRD, int FBRD){

  RCGCUART |= (1<<0); // define UART regrister
  RCGCGPIO |= (1<<0); // configure GPIO port
  GPIOAFSEL_A = (1<<1)|(1<<0); // configure AFSEL for pin0 and pin1
  GPIOPCTL_A = (1<<0)|(1<<4); // GPIO Port control for 0 and 4 positions
  GPIODEN_A = (1<<0) | (1<<1); // GPIO Digital Enable 
  UART0_CTL &= ~(1<<0); // UART Control 
  UART0_IBRD = IBRD; //  Integer Baud-Rate Divisor
  UART0_FBRD = FBRD; // Fractional Baud-Rate Divisor
  UART0_LCRH = (0x3<<5); // Line Control
  UART0_CC = 0x0;  // Clock Configuration  
  UART0_DR = 0x00000; // UART Data 
  UART0_CTL = (1<<0)|(1<<8)|(1<<9); // enable UART control
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
