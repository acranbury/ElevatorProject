#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timer.h"
#include "lcd.h"
#include "usonic.h"
#include "utils.h"



void main(void) {
  
  word distance;
  
  timer_init();
  LCDinit();
  
  LCDprintf("Hello World");
  
  usonic_init();


	EnableInterrupts;


  for(;;) {
      LCDclear();
      distance = usonic_getDistance();
      LCDprintf("Hello World!\n %d mm", distance);
      msleep(100);
  } 
}
