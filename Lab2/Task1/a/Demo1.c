void inti_timer(){
  
  RCGCTIMER |= (1<<0);
  GPTMCTL &=~(1<<0); 
  GPTMCFG = 0x00000000; 
  GPTMTAMR |= (0x2<<0); 
  GPTMTAMR &= ~(1<<4);
  GPTMTAILR = 0x00F42400 ;
  GPTMCTL |=(1<<0);
}

void delay()
{
 while(1){
    
        if((GPTMRIS & 0x00000001) == 0x1)
        {
            GPTMICR |= (1<<0); 
        }
  }
}