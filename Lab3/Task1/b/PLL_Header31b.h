/**
 * EE/CSE 474: Lab3 header file
 * CHOU, HENG-YINg
 * 1926322
 * 11/20/2020
 */

#ifndef _PLL_HEADER_H_
#define _PLL_HEADER_H_

#include <stdint.h>

// ******************** CLOCK CONTROL REGISTERS ********************** //
#define MOSCCTL                 (*(volatile uint32_t *) 0x400FE07C) // main oscillator control
#define RIS                     (*(volatile uint32_t *) 0x400FE050) // regristration for RIS in MOSCCTL
#define RSCLKCFG                (*(volatile uint32_t *) 0x400FE0B0) // Run and Sleep Mode Configuration Register
#define PLLFREQ0                (*(volatile uint32_t *) 0x400FE160) // PLL frequency 0
#define PLLFREQ1                (*(volatile uint32_t *) 0x400FE164) // PLL frequency 1
#define PLLSTAT                 (*(volatile uint32_t *) 0x400FE168) // PLL status
#define MEMTIM0                 (*(volatile uint32_t *) 0x400FE0C0) // Memory Timing Parameter Register 0 for Main Flash and EEPROM (MEMTIM0)

#define GPIODIR_F 				(*(( volatile uint32_t *) 0x4005D400 )) // configure direction for port F
#define GPIODEN_F 				(*(( volatile uint32_t *) 0x4005D51C )) // configure digital function for port F
#define GPIODATA_F 				(*(( volatile uint32_t *) 0x4005D3FC )) // configure input/output for port F 
#define GPIODIR_N 				(*(( volatile uint32_t *) 0x40064400 )) // configure direction for port N
#define GPIODEN_N 				(*(( volatile uint32_t *) 0x4006451C )) // configure digital function for port N
#define GPIODATA_N 				(*(( volatile uint32_t *) 0x400643FC )) // configure input/output for port N 

#define GPIODIR_J 				(*(( volatile uint32_t *) 0x40060400 )) // configure direction for port J
#define GPIODEN_J 				(*(( volatile uint32_t *) 0x4006051C )) // configure digital function for port J
#define GPIODATA_J 				(*(( volatile uint32_t *) 0x400603FC )) // configure input/output for port J
#define GPIOCR 					(*(( volatile uint32_t *) 0x40060524 )) // configure GPIOCUR for port J 
#define GPIOPUR    				(*(( volatile uint32_t *) 0x40060510 )) // configure GPIOPUR for port J


#define RCGCADC                 (*(volatile uint32_t *) 0x400FE638) // configure RCGC ADC0 
#define ADCCC                   (*(volatile uint32_t *) 0x40038FC8) // ADC clock configuration
#define RCGCGPIO                (*(volatile uint32_t *) 0x400FE608) // configure GPIO
#define GPIOAFSEL               (*(volatile uint32_t *) 0x4005C420) // GPIO Alternate Function Select
#define GPIODEN_E               (*(volatile uint32_t *) 0x4005C51C) // GPIO analog function
#define GPIOAMSEL               (*(volatile uint32_t *) 0x4005C528) // GPIO Analog Mode selection
#define ADCACTSS                (*(volatile uint32_t *) 0x40038000) // ADC Active Sample Sequencer               
#define ADCEMUX                 (*(volatile uint32_t *) 0x40038014) // ADC Event Multiplexer select 
#define ADCSSMUX3               (*(volatile uint32_t *) 0x400380A0) // ADC sample sequence Input multiplexer select
#define ADCISC                  (*(volatile uint32_t *) 0x4003800C) // ADC Interrupt Status and clear
#define ADCSSCTL3               (*(volatile uint32_t *) 0x400380A4) // ADC Sample Sequence Control
#define ADCSSTSH3               (*(volatile uint32_t *) 0x400380BC) // ADC Sample Sequence 3 Sample and Hold Time



#define ADCSSCTL3               (*(volatile uint32_t *) 0x400380A4)//configur for ADC0 control
#define ADCIM                   (*(volatile uint32_t *) 0x40038008)// configure for ADC0 mask
#define NVIC_EN_0               (*(volatile uint32_t *) 0xE000E100)// Regrister for timerA in EN0
#define GPTMADCEV               (*(volatile uint32_t *) 0x40030070)// configure ADC Event

#define ADCRIS                  (*(volatile uint32_t *) 0x40038004)// configure Raw Interrupts for ADC
#define ADCSSFIFO3              (*(volatile uint32_t *) 0x400380A8)// configure fifo for ADC0 


#define RCGCTIMER 				(*((volatile uint32_t *) 0x400FE604)) //  set up for timer0
#define GPTMCTL   				(*((volatile uint32_t *) 0x4003000C)) //set up for subtimerA
#define GPTMCFG   				(*((volatile uint32_t *) 0x40030000)) // GPTM Configuration Register
#define GPTMTAMR  				(*((volatile uint32_t *) 0x40030004)) // configure TAMR (include count down and periodic mode)
#define GPTMTAILR 				(*((volatile uint32_t *) 0x40030028)) // Regrister for GPTMTAILR
#define GPTMRIS   				(*((volatile uint32_t *) 0x4003001C)) // Regrister for GPTMRIS
#define GPTMICR   				(*((volatile uint32_t *) 0x40030024)) // Regrister for GPTMICR
#define GPTMIMR_time0 (*((volatile uint32_t *) 0x40030018)) // Regrister for timer0 in GPTMTIR   


#endif  // _PLL_HEADER_H_