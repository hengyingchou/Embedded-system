/* * CHOU, HENG-YINg
* 1926322
* 10/23/2020
*/

#include <stdint.h> // uint32_t, etc
#include "lab1b.h"
// Turnning on D2 and keep 0.3 second. After that, turn off
void D2(){
  GPIODATA_N = 0x1; // Set PN0 to 1 
  for (int j = 0 ; j < 1000000 ; j++) {}; // keep 0.3 seconds
  GPIODATA_N = 0x0; // Set PN0 to 0
  
}
// Turnning on D1 and keep 0.3 second. After that, turn off
void D1(){
  GPIODATA_N = 0x2; // Set PN1 to 1 
  for (int j = 0 ; j < 1000000 ; j++) {}; // keep 0.3 seconds
  GPIODATA_N = 0x0; // Set PN1 to 0
}

int main ( void )
{
  volatile unsigned short delay = 0 ;

  RCGCGPIO |= 0x1100; // Enable GPIO of Port N and Port J

  delay ++ ; // Delay 2 more cycles before access Timer registers
  delay ++ ; // Refer to Page. 756 of Datasheet for info

  GPIODEN_N = 0x3; //Set PN0 and PN4 to digitial port
  GPIODEN_J = 0x3; // Set PJ0 and PJ1 to digital port
  GPIODIR_N =  0x3; // Set PN0 and PF4 to output
  GPIODIR_J &= ~0x3;// set PJ0 and PJ1 to input 
  
  // special setting for SW1 and SW2 on board
  GPIOCR |= 0x3; // configure for PJ0 and PJ1
  GPIOPUR |= 0x3;// configure for PJ0 and PJ1
  
  while(1){
    //int j = GPIODATA & 0x1
    //if( j > 0 ) D1();
    if ((GPIODATA_J & 0x1) == 0) D1(); // Turn on D1
    if ((GPIODATA_J & 0x2) == 0) D2(); // Turn on D2 
    
  } ;
return 0 ;
}
