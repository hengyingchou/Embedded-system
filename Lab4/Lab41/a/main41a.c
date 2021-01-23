/*
* CHOU, HENG-YINg
 * 1926322
 * 12/9/2020
*/
#include "SSD2119_Display_41a.h"
#include "SSD2119_Touch_41a.h"
#include "tm4c1294ncpdt_41a.h"
int main()
{
  
  LCD_Init(); // Initiallize LCD 
  for( int i = 9 ; i< 15; i++){ // Focous on bright colors 
    LCD_ColorFill( Color4[i]);  // LCD print color
    if(i == 14) i = 9;
  }
 
  return 0;
}
