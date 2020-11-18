/* * CHOU, HENG-YINg
* 1926322
* 10/23/2020
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))// Configure RCGCGPIO 
// configure direction
#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 ))// Configure GPIODIR for Port N
#define GPIODIR_J (*(( volatile uint32_t *) 0x40060400 ))// Configure GPIODIR for Port J
// configure digital function
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C ))// Configure GPIODEN for Port N
#define GPIODEN_J (*(( volatile uint32_t *) 0x4006051C ))// Configure GPIODEN for Port J
// configure input/output 
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC ))// Configure GPIODATA for Port N
#define GPIODATA_J (*(( volatile uint32_t *) 0x400603FC ))// Configure GPIODATA for Port J

// special setting for SW1 and SW2 on board
#define GPIOCR  (*(( volatile uint32_t *) 0x40060524 ))
#define GPIOPUR (*(( volatile uint32_t *) 0x40060510 ))


#endif //__HEADER1_H__