#include"lab22_b.h"
#include<stdint.h>
#include <stdbool.h> 
/* * CHOU, HENG-YING
* 1926322
* 11/5/2020
*/
#define FLAG_NONE 0x00000000 // pull down flag
#define FLAG_TOGGLE_LED 0x00000001 // raise flag
bool x = false;
volatile uint32_t flags = FLAG_NONE; // define and initialize flag

void Timer0A_Handler( void )
{
            flags = FLAG_TOGGLE_LED; // raise flag
            GPTMICR |= (1<<0); //Set 1 to TATOCINT. Writing a 1 to this bit clears the TATORIS bit in the GPTMRIS register and the TATOMIS bit in the GPTMMIS register. 
}

void Init(){
  volatile unsigned short delay = 0 ;
  RCGCGPIO |= 0x1120;; // Enable PortF, Port N, port J GPIO
  delay ++ ; // Delay 2 more cycles before access Timer registers
  delay ++ ; // Refer to Page. 756 of Datasheet for info
  GPIODEN_F |= 0x11; // Set PF0 and PF4 to digital port
  GPIODIR_F |= 0x11; // Set PF4 and PF0 to output
  
  GPIODEN_N |= 0X3; //Set PN0 and PN4 to digitial port
  GPIODIR_N |= 0x3; // Set PN0 and PF4 to output
  GPIODATA_F |= 0x0; // clear GPIODATA_F
  GPIODATA_N |= 0x0; // clear GPIODATA_N 
}


void inti_timer(){
  
  RCGCTIMER |= (1<<0); // configure timer0
  GPTMCTL &=~(1<<0); //TAEN is set 0. Timer A is disabled.
  GPTMCFG = 0x00000000; //Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
  GPTMTAMR |= (0x2<<0); //TAMR is set 0x2. Periodic Timer mode is used
  GPTMTAMR &= ~(1<<4); // configure the ​TACDIR​ bit of the ​GPTMTAMR​ register to count down
  GPTMTAILR = 0x00F42400 ; // Load the value 16,000,00 
  GPTMIMR_time0 |= (1<<0); // configure GPTMIMR for timer0 
  NVIC_EN_0 |= (1<<19); //Enable Timer0A in EN0 
  GPTMCTL |=(1<<0); //Enable the timer using the ​GPTMCTL​ register.GPTM Polling
}
void init_switch(){
   GPIODEN_J = 0x3; // Set PJ0 and PJ1 to digital port
   GPIODIR_J &= ~0x3;// set PJ0 and PJ1 to input 
   GPIOCR |= 0x3; // configure GPIOCR for PJ0 and PJ1
   GPIOPUR |= 0x3; // configure GPIOPUR for PJ0 and PJ1
}

enum LA_States { LA_SMStart, A, B} LA_State;
void TickFct_Latch()
{
  switch(LA_State) {   // Transitions
     case LA_SMStart:  // Initial transition
        LA_State = A; // Transit to A
        break;
     case A:
       if((GPIODATA_J & 0x1) == 0){ // if switch 1 is pressed
         GPIODATA_N = 0x0; // turn off LED
         LA_State = B; // transit to state B
         GPTMCTL &=~(1<<0); // disable timer
         x = true; // set true to x for maintianing program
       }; // transit to B
        break;
     case B:
       if((GPIODATA_J & 0x2) == 0){ // if switch 2 is pressed
          GPIODATA_N = 0x0; // turn off LED
         LA_State = A; // transit to A
         GPTMCTL |=(1<<0); // enable timer
         x = false; // set false to x because we do not need it now.
       } // transit to C
        break;
        
  } // Transitions

  switch(LA_State) {   // State actions
     case A:
       GPIODATA_N ^= (1<<1); // turn on D1
        break;
     case B:
      GPIODATA_N = 0x1; // turn on D2
        break;
    
   } // State actions
}

int main()
{
  Init();
  inti_timer();
  init_switch();
  LA_State = LA_SMStart;
  while(1){
    if(flags == FLAG_TOGGLE_LED || x == true){ // wait for the raise of flag 
    TickFct_Latch();
    flags = FLAG_NONE ;// put down flag
    }
    
  }
  return 0;
}
