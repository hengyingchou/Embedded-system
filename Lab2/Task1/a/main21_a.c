/* * CHOU, HENG-YING
* 1926322
* 11/5/2020
*/
#include "lab21_a.h"
#include<stdint.h>

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
  GPTMCTL |=(1<<0); //Enable the timer using the ​GPTMCTL​ register.GPTM Polling 
}
void delay()
{
 while(1){
    
        if((GPTMRIS & 0x00000001) == 0x1) // when the timer has counted down and reached 0.
        {
            GPTMICR |= (1<<0); //Set 1 to TATOCINT. Writing a 1 to this bit clears the TATORIS bit in the GPTMRIS register and the TATOMIS bit in the GPTMMIS register. 
            break;
        }
  }
}



void D4_open(){
  GPIODATA_F = 0x11 ; // Set PF0 to 1
 delay();
}
void D3_open(){
  GPIODATA_F = 0x10; // Set PF4 to 1 
   delay();
}
void D2_open(){
  GPIODATA_N = 0x3; // Set PN0 to 1 
   delay();
}
void D1_open(){
  GPIODATA_N = 0x2;// Set PN1 to 1 
   delay();
}
void D4_close(){
  GPIODATA_F = 0x0 ; // Set PF0 to 1
   delay();
}
void D3_close(){
  GPIODATA_F = 0x01; // Set PF4 to 1 
   delay();
}
void D2_close(){
  GPIODATA_N = 0x0; // Set PN0 to 1
   delay();
}
void D1_close(){
  GPIODATA_N = 0x1;// Set PN1 to 1 
   delay();
}

int main()
{
  
  Init();
  inti_timer();
  while(1){
    
   D1_open();
    D2_open();
    D3_open();
    D4_open();
    D1_close();
    D2_close();
    D3_close();
    D4_close();
  }
  return 0;
}
