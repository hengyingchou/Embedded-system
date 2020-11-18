/* * CHOU, HENG-YINg
* 1926322
* 10/23/2020
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

// configure gpio for portF  
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))

// configure direction for port F and port N
#define GPIODIR_F (*(( volatile uint32_t *) 0x4005D400 ))
#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 ))

// configure digital function for port F and N
#define GPIODEN_F (*(( volatile uint32_t *) 0x4005D51C ))
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C ))

// configure input/output for port F and N
#define GPIODATA_F (*(( volatile uint32_t *) 0x4005D3FC ))
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC ))

#endif //__HEADER1_H__