unsigned long switch_input_A ( void ){
  int count = 0;
  while( GPIODATA_N & 0x4){ // Using while loop to create 2 seconds delay
    count++;
    delay();
    if(count == 2) return ( GPIODATA_N & 0x4) ; 
  }
  return 0x0;
}

void LED_on_pc4 ( void ){
  GPIODATA_C |= 0x10 ;
  for(int i = 0 ; i <5; i++){ // Using for loop to create 5 seconds delay
          delay();
         if(switch_input_B()){  
           LA_State = warn; 
           break;
         }
         system_off();        
       }
}



