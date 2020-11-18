#define FLAG_NONE 0x00000000 // pull down flag
#define FLAG_TOGGLE_LED 0x00000001 // raise flag
volatile uint32_t flags = FLAG_NONE; // define and initialize flag

void Timer0A_Handler( void )
{
            flags = FLAG_TOGGLE_LED; // raise the flag
            GPTMICR |= (1<<0); // reset timer
}

void inti_timer(){ // initiallize timer and interrupt
  
  RCGCTIMER |= (1<<0);
  GPTMCTL &=~(1<<0); 
  GPTMCFG = 0x00000000; 
  GPTMTAMR |= (0x2<<0); 
  GPTMTAMR &= ~(1<<4);
  GPTMTAILR = 0x00F42400 ;
  GPTMIMR_time0 |= (1<<0);
  NVIC_EN_0 |= (1<<19);
  GPTMCTL |=(1<<0);
}
int main()
{
  Init();
  inti_timer();
  LA_State = LA_SMStart;
  while(1){
    if(flags == FLAG_TOGGLE_LED){ // wait for the raise of flag 
    TickFct_Latch();
    flags = FLAG_NONE  ; // put down flag
    }
    
  }
  return 0;
}