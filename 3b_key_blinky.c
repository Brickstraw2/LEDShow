#include <stdio.h>
#include "os.h"

int toggle = 0;

int blinkingDelay = 40000000;

// adjustable delay
void delay(int BLNK_DLY)
{
  volatile int cnt;

  for (cnt=0; cnt<BLNK_DLY; cnt++);
}

#define SWI_OS_Byte "0x00006"
int OS_Byte(int r0, int r1, int r2)
{
  register int _r1 __asm("r1") = r1;

  __asm__ ("SWI " SWI_OS_Byte);

  return _r1;
}

void compareSwitch(){
/**	
	<- arrow key ===>  increase frequency
	 -> arrow key ===> decrease frequency
	 task is used to increment or decrement the blinkingDelay
**/
    taskstart("select");

    if (OS_Byte(0x79, (1<<7)+25,0) == 0xFF)
    {
	  // freq increment
      blinkingDelay = blinkingDelay - 20000000;
    }
    if(OS_Byte(0x79, (1<<7)+121,0) == 0xFF)
    {
	  // freq decrement
      blinkingDelay = blinkingDelay + 20000000;
    }

    taskend();
}


int main (void)
{
  

  printf("To close press Escape\n");

  while (1)
  {

	// toggling between red and black colour

    if (toggle)
    {
      // LED red
      gcol(3);
      disc(20, 20, 30, 30);
    }
    else
    {
      // LED black
      gcol(0);
      disc(20, 20, 30, 30);
    }

	// toggle = !toggle logic
    toggle = 1 - toggle;

	// delay added to show the blinking effect
    delay(blinkingDelay);

	compareSwitch();
  }
  return 0;
}

