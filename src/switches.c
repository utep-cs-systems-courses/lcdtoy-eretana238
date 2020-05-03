#include <msp430.h>
#include <lcdutils.h>
#include <p2switches.h>
#include "switches.h"
#include "spaceship.h"

void senseSwitches() {
  u_int switches = p2sw_read(), i;
    /* update shapes based on switch press */
  for (i = 0; i < 4; i++)
    if(!(switches & (1<<i))) {
      if (i == 0 && xLoc > 22) {
	xLoc-=2;
      }
      else if ((i == 1 || i == 2) && !shooting) {
	xLazer = xLoc;
	shooting = 1;
      }
      else if (i == 3 && xLoc < screenWidth-22)
	xLoc+=2;
    }
}
