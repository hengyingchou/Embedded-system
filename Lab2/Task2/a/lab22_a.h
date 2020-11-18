#ifndef __HEADER1_H__
#define __HEADER1_H__
/* * CHOU, HENG-YING
* 1926322
* 11/5/2020
*/

//define GPIO 
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))

#define RCGCTIMER (*((volatile uint32_t *) 0x400FE604)) //  set up for timer0
#define GPTMCTL   (*((volatile uint32_t *) 0x4003000C)) //set up for subtimerA
#define GPTMCFG   (*((volatile uint32_t *) 0x40030000)) // GPTM Configuration Register
#define GPTMTAMR  (*((volatile uint32_t *) 0x40030004)) // configure TAMR (include count down and periodic mode) 
#define GPTMTAILR (*((volatile uint32_t *) 0x40030028)) // Regrister for GPTMTAILR
#define GPTMRIS   (*((volatile uint32_t *) 0x4003001C)) // Regrister for GPTMRIS
#define GPTMICR   (*((volatile uint32_t *) 0x40030024)) // Regrister for GPTMICR
#define GPTMIMR_time0 (*((volatile uint32_t *) 0x40030018)) // Regrister for timer0 in GPTMTIR
#define NVIC_EN_0 (*(( volatile uint32_t *) 0xE000E100 )) // Regrister for timerA in EN0

#define GPIODIR_F (*(( volatile uint32_t *) 0x4005D400 )) // configure direction for port F
#define GPIODEN_F (*(( volatile uint32_t *) 0x4005D51C )) // configure digital function for port F
#define GPIODATA_F (*(( volatile uint32_t *) 0x4005D3FC )) // configure input/output for port F 

#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 )) // configure direction for port N
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C )) // configure digital function for port N
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC )) // configure input/output for port N 

#endif //__HEADER1_H__