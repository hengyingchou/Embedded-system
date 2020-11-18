/* * CHOU, HENG-YINg
* 1926322
* 10/23/2020
*/

//For LED connect to port C
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))
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


