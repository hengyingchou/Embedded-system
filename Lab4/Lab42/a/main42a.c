#include "lab42_a.h"
#include <stdint.h>// uint32_t, etc
#include <stdbool.h>// boolean 
#include "Lab42a_Inits.h"
#include "PLL_Header42a.h"
#include "SSD2119_Display_42a.h"
#include "SSD2119_Touch_42a.h"
#include "tm4c1294ncpdt.h"
#include <stdio.h>
int X,Y;

/* * CHOU, HENG-YINg
* 1926322
* 11/5/2020
*/

bool x = false; // This bool is for jumping out of while loop when switch 1 is pressed. 
enum LA_States { LA_SMStart, go, stop, warn , LA_end } LA_State; // states of state machine
void turn_off_all( void );
unsigned long switch_input_A ( void );// switch A
unsigned long switch_input_B ( void );// switch B

void LED_init2 ( void ){
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1004 ; // activate clock for Port C and Port N
  delay ++ ;
  delay ++ ;
  GPIOAMSEL_C &= ~ 0x70 ; // disable analog function of PC4, PC5 and PC6
  GPIODIR_C |= 0x70 ; // set PC4, PC5 and PC6 to output
  GPIOAFSEL_C &= ~ 0x70 ; // set PC4, PC5 and PC6 as regular port function
  GPIODEN_C |= 0x70 ; // enable digital output on PC4, PC5 and PC6
  GPIODATA_C |= 0x0; // clean output
}
// Inititalize the switch
void extern_switch_init ( void ){
  GPIOAMSEL_N &= ~0x0c ; // Disable PN2 and PN3 analog function
  GPIOAFSEL_N &= ~0x0c ; // Select PN2 and PN3 regular port function
  GPIODIR_N &= ~0x0c ; // Set PN2 and PN3 to input direction
  GPIODEN_N |= 0x0c ; // Enable digital function of PN2 and PN3
}
void inti_timer(){
  
  RCGCTIMER |= (1<<0); // configure timer0 
  GPTMCTL &=~(1<<0); //TAEN is set 0. Timer A is disabled.
  GPTMCFG = 0x00000000; //Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
  GPTMTAMR |= (0x2<<0); //TAMR is set 0x2. Periodic Timer mode is used
  GPTMTAMR &= ~(1<<4); // configure the ?TACDIR? bit of the ?GPTMTAMR? register to count down
  GPTMTAILR = 0x3938700 ; // Load the value 16,000,00 
  
  GPTMCTL |=(1<<0); //Enable the timer using the ?GPTMCTL? register.
}
void delay(){
 while(1){
        if((GPTMRIS & 0x00000001) == 0x1)// when the timer has counted down and reached 0.
        {
            GPTMICR |= (1<<0); //Set 1 to TATOCINT. Writing a 1 to this bit clears the TATORIS bit in the GPTMRIS register and the TATOMIS bit in the GPTMMIS register. 
            break;
        }
  }

}
void system_off(){
  if(switch_input_A()){ // see whether switch A is pressed
           
           turn_off_all(); 
           LA_State = LA_end; // transit to end
           x = true; // change x from false to true 
         
  }
}
// turn on LED connected to PC4
void LED_on_pc4 ( void ){
  LCD_DrawFilledRect(160,20,40,40,Color4[10]);
  for(int i = 0 ; i <5; i++){ // keep 0.3 seconds
          delay();
         if(switch_input_B()){ // see whether switch B is pressed  
           LA_State = warn; // transit to warn 
           break;
         }
         system_off();
       }
}
// turn off LED connected to PC4
void LED_off_pc4 ( void ){
  LCD_DrawFilledRect(160,20,40,40,Color4[0]);  // light up green
}
// turn on LED connected to PC5
void LED_on_pc5 ( void ){
  LCD_DrawFilledRect(160,20,40,40,Color4[0]); // off green
  LCD_DrawFilledRect(100,20,40,40,Color4[14]); // turn yellow
   for(int i = 0 ; i <5; i++){ // keep 5 seconds
      delay();
      system_off();
       }
}
// turn off LED connected to PC5
void LED_off_pc5 ( void ){
  LCD_DrawFilledRect(100,20,40,40,Color4[0]); // off yellow
}
// turn on LED connected to PC6
void LED_on_pc6 ( void ){
  LCD_DrawFilledRect(40,20,40,40,Color4[12]); // on red
   for(int i = 0 ; i <5; i++){ // keep 5 seconds
        delay();
        system_off();
       }
}
// turn off LED connected to PC6
void LED_off_pc6 ( void ) // off red
{
  LCD_DrawFilledRect(40,20,40,40,Color4[0]);
  
}

unsigned long switch_input_A ( void ){
  int count = 0;
  //detect switch on/off 
  while( 655 < Touch_ReadX() && Touch_ReadX() < 1312 && 818 < Touch_ReadY() && Touch_ReadY() < 1392 ){ // keep 2 seconds
    count++;
    delay();
    if(count == 2) return 1 ; // 0x4 (pressed) or 0 (not pressed)
  }

  return 0x0;
}
unsigned long switch_input_B ( void ){
  int count = 0; 
  // detect switch pedesrtian
  while( 1513 < Touch_ReadX() && Touch_ReadX() < 1900 && 822 < Touch_ReadY() && Touch_ReadY() < 1349){ // keep 2 seconds
    count++;
    delay();
    LED_on_pc5();
    if(count == 2) return 1 ; // 0x8 (pressed) or 0 (not pressed)
  }
  return 0x0;
  
} 
void turn_off_all( void ){ // turn off all lights
  LED_off_pc4();
  LED_off_pc5();
  LED_off_pc6();
}
// State machine
void TickFct_Latch()
{
  switch(LA_State) {   // Transitions
     case LA_SMStart:  // Initial transition
        LA_State = stop; // Transit to go
        break;

     case go:
       LA_State = stop; // transit to stop
       LED_off_pc6(); // Turn off LED connect to pc6
       LED_on_pc4();  // Turn on LED connect to pc4
       
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
       LED_on_pc5();// Turn on LED connect to pc5
      
        break;
     case stop:
       LED_off_pc4(); // Turn off LED connect to pc4
       LED_off_pc5(); // Turn off LED connect to pc5
       LED_on_pc6(); // Turn off LED connect to pc6
       break;
       
       case LA_end:
         break; 
           
     default:
        break;
   } // State actions
}

 int main(){

  LCD_Init();            // Initialize LCD
  LCD_DrawFilledRect(20,100,100,100,Color4[13]); // Draw square on LCD for on/off
  LCD_SetCursor(50, 140); // set cursor on sentence
  LCD_PrintString("On/off"); 
  LCD_DrawFilledRect(180,100,100,100,Color4[13]); // Draw square on LCD for pedestrain
  LCD_SetCursor(205, 140); // set cursor on sentence
  LCD_PrintString("Pedistrain");
  Touch_Init();
  enum frequency freq = PRESET2; //frquency 60 HZ
  PLL_Init(freq); // initialize frequency
  
  inti_timer();
   
  while(1) {
    if(switch_input_A()){ // see whether switch A is pressed for start system
      while(switch_input_A()){};
      LA_State = LA_SMStart;
      while(x == false){ // if x is not false, then break the loop
        TickFct_Latch();
        }
       x = false; // after break the loop reset x to false
    }
  }


  return 0;
}
