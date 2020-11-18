bool x = false; // for sustaining program
enum LA_States { LA_SMStart, A, B} LA_State; // state
void TickFct_Latch() // state machine
int main()
{
  Init();
  inti_timer();
  init_switch();
  LA_State = LA_SMStart;
  while(1){
    if(flags == FLAG_TOGGLE_LED || x == true){ // wait for the raise of flag or 
    TickFct_Latch();                           // if Boolean x is true
    flags = FLAG_NONE ;// put down flag
    }
  }
  return 0;
}