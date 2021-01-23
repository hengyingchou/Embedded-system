/*
* CHOU, HENG-YINg
 * 1926322
 * 12/9/2020
*/

#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 )) // RCGCGPIO regrister
#define RCGCTIMER (*((volatile uint32_t *) 0x400FE604)) // define Timer A
#define GPTMCTL   (*((volatile uint32_t *) 0x4003000C)) //timer zero
#define GPTMCFG   (*((volatile uint32_t *) 0x40030000)) // define CFG to default value
#define GPTMTAMR  (*((volatile uint32_t *) 0x40030004)) //  Timer A mode
#define GPTMTAILR (*((volatile uint32_t *) 0x40030028)) // Timer A interval load
#define GPTMRIS   (*((volatile uint32_t *) 0x4003001C)) // raise flag
#define GPTMICR   (*((volatile uint32_t *) 0x40030024)) // clear flag

 