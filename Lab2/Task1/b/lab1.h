#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))
#define GPIOAMSEL_C (*(( volatile uint32_t *) 0x4005A528 ))
#define GPIODIR_C (*(( volatile uint32_t *) 0x4005A400 ))
#define GPIODEN_C (*(( volatile uint32_t *) 0x4005A51C ))
#define GPIOAFSEL_C (*(( volatile uint32_t *) 0x4005A420 ))
#define GPIODATA_C (*(( volatile uint32_t *) 0x4005A3FC ))

#define GPIOAMSEL_N (*(( volatile uint32_t *) 0x40064528 ))
#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 ))
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C ))
#define GPIOAFSEL_N (*(( volatile uint32_t *) 0x40064420 ))
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC ))

#define RCGCTIMER (*((volatile uint32_t *) 0x400FE604))
#define GPTMCTL   (*((volatile uint32_t *) 0x4003000C)) //timer zero
#define GPTMCFG   (*((volatile uint32_t *) 0x40030000))
#define GPTMTAMR  (*((volatile uint32_t *) 0x40030004))  
#define GPTMTAILR (*((volatile uint32_t *) 0x40030028))
#define GPTMRIS   (*((volatile uint32_t *) 0x4003001C))
#define GPTMICR   (*((volatile uint32_t *) 0x40030024))

 