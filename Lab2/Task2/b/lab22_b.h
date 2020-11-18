/* * CHOU, HENG-YINg
* 1926322
* 11/5/2020
*/
#ifndef __HEADER1_H__
#define __HEADER1_H__

// configure gpio for portF
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))

#define RCGCTIMER (*((volatile uint32_t *) 0x400FE604)) //  set up for timer0
#define GPTMCTL   (*((volatile uint32_t *) 0x4003000C)) //set up for subtimerA
#define GPTMCFG   (*((volatile uint32_t *) 0x40030000)) // GPTM Configuration Register
#define GPTMTAMR  (*((volatile uint32_t *) 0x40030004)) // configure TAMR (include count down and periodic mode)
#define GPTMTAILR (*((volatile uint32_t *) 0x40030028)) // Regrister for GPTMTAILR
#define GPTMRIS   (*((volatile uint32_t *) 0x4003001C)) // Regrister for GPTMRIS
#define GPTMICR   (*((volatile uint32_t *) 0x40030024)) // Regrister for GPTMICR
#define GPTMIMR_time0 (*((volatile uint32_t *) 0x40030018)) // Configure GPTMIMR of timer0 
#define NVIC_EN_0 (*(( volatile uint32_t *) 0xE000E100 ))// configure EN0 of timerA

#define GPIODIR_F (*(( volatile uint32_t *) 0x4005D400 ))// configure direction for port F
#define GPIODEN_F (*(( volatile uint32_t *) 0x4005D51C ))// configure digital function for port F
#define GPIODATA_F (*(( volatile uint32_t *) 0x4005D3FC ))// configure input/output for port F 

#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 ))// configure direction for port N
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C )) // configure digital function for port N
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC )) // configure input/output for port N 

#define GPIODIR_J (*(( volatile uint32_t *) 0x40060400 ))// configure direction for port J
#define GPIODEN_J (*(( volatile uint32_t *) 0x4006051C ))// configure digital function for port J
#define GPIODATA_J (*(( volatile uint32_t *) 0x400603FC ))// configure input/output for port J
#define GPIOCR (*(( volatile uint32_t *) 0x40060524 )) // configure GPIOCUR for port J 
#define GPIOPUR    (*(( volatile uint32_t *) 0x40060510 ))// configure GPIOPUR for port J


#endif //__HEADER1_H__