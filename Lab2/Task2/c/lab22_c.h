/* * CHOU, HENG-YINg
* 1926322
* 11/5/2020
*/

//For LED connect to port C
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))// configure gpio for port C and port N
#define GPIOAMSEL_C (*(( volatile uint32_t *) 0x4005A528 )) //confiugre analog function on port C 
#define GPIODIR_C (*(( volatile uint32_t *) 0x4005A400 ))//configure direction for port C
#define GPIODEN_C (*(( volatile uint32_t *) 0x4005A51C ))// configure digital function of port C
#define GPIOAFSEL_C (*(( volatile uint32_t *) 0x4005A420 ))// configure regular port function of port C
#define GPIODATA_C (*(( volatile uint32_t *) 0x4005A3FC ))// configure input/output function of port C

// For switch connect to port N
#define GPIOAMSEL_N (*(( volatile uint32_t *) 0x40064528 )) //confiugre analog function on port N
#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 )) //configure direction for port N
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C )) //configure digital function for port N
#define GPIOAFSEL_N (*(( volatile uint32_t *) 0x40064420 )) // configure regular port function of port N
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC )) // configure input/output function of port N 

#define RCGCTIMER (*((volatile uint32_t *) 0x400FE604)) //  set up for timer0
#define GPTMCTL   (*((volatile uint32_t *) 0x4003000C)) //set up for subtimerA
#define GPTMCFG   (*((volatile uint32_t *) 0x40030000)) // GPTM Configuration Register
#define GPTMTAMR  (*((volatile uint32_t *) 0x40030004)) // configure TAMR (include count down and periodic mode)
#define GPTMTAILR (*((volatile uint32_t *) 0x40030028)) // Regrister for GPTMTAILR
#define GPTMRIS   (*((volatile uint32_t *) 0x4003001C)) // Regrister for GPTMRIS
#define GPTMICR   (*((volatile uint32_t *) 0x40030024)) // Regrister for GPTMICR
#define GPTMIMR_time0 (*((volatile uint32_t *) 0x40030018)) // Configure GPTMIMR of timer0 
#define NVIC_EN_0 (*(( volatile uint32_t *) 0xE000E100 ))// configure EN0 of timerA
