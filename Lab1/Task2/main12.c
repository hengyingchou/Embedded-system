#include "lab12.h"
#include <stdint.h>// uint32_t, etc
#include <stdbool.h>// boolean 
/* * CHOU, HENG-YINg
* 1926322
* 10/23/2020
*/

bool x = false; // This bool is for jumping out of while loop when switch 1 is pressed. 

void LED_init ( void ){
  volatile unsigned short delay = 0 ;
  RCGCGPIO |= 0x1004 ; // activate clock for Port C and Port N
  delay ++ ;
  delay ++ ;
  GPIOAMSEL_C &= ~ 0x70 ; // disable analog function of PC4, PC5 and PC6
  GPIODIR_C |= 0x70 ; // set PC4, PC5 and PC6 to output
  GPIOAFSEL_C &= ~ 0x70 ; // set PC4, PC5 and PC6 as regular port function
  GPIODEN_C |= 0x70 ; // enable digital output on PC4, PC5 and PC6
}
// turn on LED connected to PC4
void LED_on_pc4 ( void ){
  GPIODATA_C |= 0x10 ;
}
// turn off LED connected to PC4
void LED_off_pc4 ( void ){
  GPIODATA_C &= ~ 0x10 ;
}
// turn on LED connected to PC5
void LED_on_pc5 ( void ){
  GPIODATA_C |= 0x20 ;
}
// turn off LED connected to PC5
void LED_off_pc5 ( void ){
  GPIODATA_C &= ~ 0x20 ;
}
// turn on LED connected to PC6
void LED_on_pc6 ( void ){
  GPIODATA_C |= 0x40 ;
}
// turn off LED connected to PC6
void LED_off_pc6 ( void )
{
  GPIODATA_C &= ~ 0x40 ;
}
// Inititalize the switch 
void extern_switch_init ( void ){
  GPIOAMSEL_N &= ~ 0x0c ; // Disable PN2 and PN3 analog function
  GPIOAFSEL_N &= ~ 0x0c ; // Select PN2 and PN3 regular port function
  GPIODIR_N &= ~ 0x0c ; // Set PN2 and PN3 to input direction
  GPIODEN_N |= 0x0c ; // Enable digital function of PN2 and PN3
}


unsigned long switch_input_A ( void ){
  return ( GPIODATA_N & 0x04 ) ; // 0x4 (pressed) or 0 (not pressed)
}
unsigned long switch_input_B ( void ){
  return ( GPIODATA_N & 0x08 ) ; // 0x8 (pressed) or 0 (not pressed)
}

// Turn of all LED 
void turn_off_all( void ){
  LED_off_pc4();
  LED_off_pc5();
  LED_off_pc6();
}



enum LA_States { LA_SMStart, go, stop, warn , LA_end } LA_State;
void TickFct_Latch()
{
  switch(LA_State) {   // Transitions
     case LA_SMStart:  // Initial transition
        LA_State = go; // Transit to go
        break;

     case go:
       LA_State = stop; // transit to stop
       LED_off_pc5(); // Turn off LED connect to pc5
       LED_off_pc6(); // Turn off LED connect to pc6
       LED_on_pc4();  // Turn on LED connect to pc4
       for(int i = 0 ; i <1000000; i++){ // keep 0.3 seconds
         if(switch_input_B()){ // see whether switch B is pressed  
           
           LA_State = warn; // transit to warn
           
         }
         
         
         if(switch_input_A()){ // see whether switch A is pressed
           
           turn_off_all(); 
           LA_State = LA_end; // transit to end
           x = true; // change x from false to true
           
           
         }
         
       }
        break;

     case warn:
        LA_State = stop; // transit to stop
        break;
        
     case stop:
         LA_State = go; // transit to go
         break;
     case LA_end: // if the state is LA_end then just break 
         break; 
        
     default:
        LA_State = LA_SMStart;
        break;
  } // Transitions

  switch(LA_State) {   // State actions
     case go:
        break;

     case warn:
       LED_off_pc4();// Turn off LED connect to pc4
       LED_off_pc6();// Turn off LED connect to pc6
       LED_on_pc5();// Turn on LED connect to pc5
       for(int i = 0 ; i <1000000; i++){ // keep 0.3 seconds
       
       if(switch_input_A()){ // see whether switch A is pressed
           
           turn_off_all();
           LA_State = LA_end; // transit to LA_end
           x = true; // change x from false to true
           
         }
       
       }
        break;
     case stop:
       LED_off_pc4(); // Turn off LED connect to pc4
       LED_off_pc5(); // Turn off LED connect to pc5
       LED_on_pc6(); // Turn off LED connect to pc6
       for(int i = 0 ; i <1000000; i++){ // keep 0.3 seconds
       
         if(switch_input_A()){
           
           turn_off_all();
           LA_State = LA_end;
           x = true; // change x from false to true
         }
       
       }
       break;
       
       case LA_end:
         break; 
      
       
     default:
        break;
   } // State actions
}

 int main(){
  LED_init();
  extern_switch_init();
  //LA_State = LA_SMStart;
  while(1) {
    if(switch_input_A()){ // see whether switch A is pressed for start system
      for(int i = 0 ; i <500000; i++)
      LA_State = LA_SMStart;
      while(x == false){ // if x is not false, then break the loop
        TickFct_Latch();
        }
       x = false; // after break the loop reset x to false
    }
  }
 
  
  
  return 0;
}
