/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


void drawRightTri(u_char x, u_char y, u_char l) {
  // diagonal
  for (u_char i = x; i < l+x; i++) {
    drawPixel(i,i,COLOR_BLACK);
    drawPixel(y,i, COLOR_BLACK);
    drawPixel(i, l+y, COLOR_BLACK);
  }
  //down
  for (u_char j = y; j < l+y; j++) {

  }
  // right
  for (u_char k = x; k < l+x; k++) {
    
  }
}

void drawTri(u_char x, u_char y, u_char l) {
  u_char j = y;
  u_char k = l+x;
  for (u_char i = x; i < l+x; i++) {
    drawPixel(i,j,COLOR_BLACK);
    drawPixel(k+i, k-i, COLOR_BLACK);
    j++;
  }
  
}

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  clearScreen(COLOR_BLUE);

  drawRightTri(5,5,30);
  //drawTri(10,10,50);
}
