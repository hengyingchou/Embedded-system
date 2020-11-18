/* * CHOU, HENG-YINg
* 1926322
* 10/23/2020
*/

#include <stdint.h>// uint32_t, etc
#include "lab1a.h"

void D4_open(){  
  GPIODATA_F = 0x11 ; // Set PF0 to 1 which means turn D4 on and keep 0.3 seconds
  for (int j = 0 ; j < 1000000 ; j++) {};
}
void D3_open(){
  GPIODATA_F = 0x10; // Set PF4 to 1 which means turn D3 on and keep 0.3 seconds
  for (int j = 0 ; j < 1000000 ; j++) {};
}
void D2_open(){
  GPIODATA_N = 0x3; // Set PN0 to 1 which means turn D2 on and keep 0.3 seconds 
  for (int j = 0 ; j < 1000000 ; j++) {};  
}
void D1_open(){
  GPIODATA_N = 0x2;// Set PN1 to 1 which means turn D1 on and keep 0.3 seconds 
  for (int j = 0 ; j < 1000000 ; j++) {};
}
void D4_close(){
  GPIODATA_F = 0x0 ; // Set PF0 to 0, which means turn off D4, and keep 0.3 seconds
  for (int j = 0 ; j < 1000000 ; j++) {};
}
void D3_close(){
  GPIODATA_F = 0x01; // Set PF4 to 0, which means turn off D3 but keep turning D4, and keep 0.3 seconds
  for (int j = 0 ; j < 1000000 ; j++) {};
}
void D2_close(){
  GPIODATA_N = 0x0; // Set PN0 to 0 which means turn off D2 and keep 0.3 seconds
  for (int j = 0 ; j < 1000000 ; j++) {};  
}
void D1_close(){
  GPIODATA_N = 0x1;// Set PN1 to 0 which means turn off D1 but keep turning D2, and keep 0.3 seconds  
  for (int j = 0 ; j < 1000000 ; j++) {};
}

int main(void){
  volatile unsigned short delay = 0 ;

  RCGCGPIO |= 0x1020; // Enable PortF and Port N GPIO

  delay ++ ; // Delay 2 more cycles before access Timer registers
  delay ++ ; // Refer to Page. 756 of Datasheet for info

  GPIODEN_F = 0x11; // Set PF0 and PF4 to digital port
  GPIODEN_N = 0X3; //Set PN0 and PN4 to digitial port
  //GPIODEN_F4 = 0x10;
  GPIODIR_F = 0x11; // Set PF4 and PF0 to output
  GPIODIR_N = 0x3; // Set PN0 and PF4 to output
  
  while(1){
    D1_open();
    D2_open();
    D3_open();
    D4_open();
    D1_close();
    D2_close();
    D3_close();
    D4_close();
   
  } ;
return 0;
}
