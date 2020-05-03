#ifndef spaceship_INCLUDED
#define spaceship_INCLUDED

#include "lcdutils.h"

u_char xLoc;
u_char xLazer;
u_char yLoc;
u_char shooting;

void drawSpaceship(u_char x);

void drawLazer(u_char x, u_char y);

void clearLazer(u_char x, u_char y);

#endif
