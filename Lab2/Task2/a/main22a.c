#include"lab22_a.h"
#include<stdint.h>
/* * CHOU, HENG-YING
* 1926322
* 11/5/2020
*/
#define FLAG_NONE 0x00000000 // pull down flag
#define FLAG_TOGGLE_LED 0x00000001 // raise flag
volatile uint32_t flags = FLAG_NONE; // define and initialize flag

void Timer0A_Handler( void ) 
{
            flags = FLAG_TOGGLE_LED; //raise the flag
            GPTMICR |= (1<<0); //Set 1 to TATOCINT. Writing a 1 to this bit clears the TATORIS bit in the GPTMRIS register and the TATOMIS bit in the GPTMMIS register. 
}

void Init(){
  volatile unsigned short delay = 0 ;

  RCGCGPIO |= 0x1020;; // Enable PortF and Port N GPIO
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

enum LA_States { LA_SMStart, A, B, C, D, E, F, G, H} LA_State;
void TickFct_Latch()
{
  switch(LA_State) {   // Transitions
     case LA_SMStart:  // Initial transition
        LA_State = A; // Transit to A
        break;
     case A:
       LA_State = B; // transit to B
        break;
     case B:
        LA_State = C; // transit to C
        break;
     case C:
         LA_State = D; // transit to D
         break;
     case D: 
         LA_State = E; // transit to E
         break; 
     case E:
       LA_State = F; // transit to F
        break;
     case F:
        LA_State = G; // transit to G
        break;
     case G:
         LA_State = H; // transit to H
         break;
     case H: 
         LA_State = A; // transit to A (start new period)
         break;
        
  } // Transitions

  switch(LA_State) {   // State actions
     case A:
       GPIODATA_N = 0x2; // turn on D1
        break;
     case B:
      GPIODATA_N = 0x3; // turn on D2
        break;
     case C:
      GPIODATA_F = 0x10; // turn on D3
       break;
     case D:
        GPIODATA_F = 0x11; // turn on D4
         break;   
     case E:
       GPIODATA_N = 0x1; // turn off D1
        break;
     case F:
      GPIODATA_N = 0x0; // turn off D2
        break;
     case G:
      GPIODATA_F = 0x01; // turn off D3
        break;
     case H:
        GPIODATA_F = 0x0 ; // // turn on D4
       break;
   } // State actions
}

int main()
{
  Init();
  inti_timer();
  LA_State = LA_SMStart;
  while(1){
    if(flags == FLAG_TOGGLE_LED){ // wait for the raise of flag 
    TickFct_Latch();
    flags = FLAG_NONE  ; // put down flag
    }
    
  }
  return 0;
}
