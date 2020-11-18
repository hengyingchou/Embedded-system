void delay(){
  while(1){   
    if(flags == FLAG_TOGGLE_LED){ // wait for the flag raise
      flags = FLAG_NONE; // pull down the flag
      break;
    }
  }
}
void LED_on_pc4 ( void ){
  GPIODATA_C |= 0x10 ;
  for(int i = 0 ; i <5; i++){ // keep 0.3 seconds
          delay();
         if(switch_input_B()){ // see whether switch B is pressed  
           LA_State = warn; // transit to warn 
           break;
         }
         system_off();
       }
}
unsigned long switch_input_A ( void ){
  int count = 0;
  while( GPIODATA_N & 0x4){
    count++;
    delay();
    if(count == 2) return ( GPIODATA_N & 0x4) ; // 0x4 (pressed) or 0 (not pressed)
  }
  return 0x0;
}
