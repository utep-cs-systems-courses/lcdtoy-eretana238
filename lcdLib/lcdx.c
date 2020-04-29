/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


void drawSquareDiamond(u_char x, u_char y, u_char size){
  for (u_char r = 0; r < size; r++) {
    u_char colstart = size-r;
    u_char colend = size;
      for (u_char c = colstart; c < colend; c+= 3) {
	drawPixel(x+c,y+r,COLOR_RED);
	drawPixel(x-c,y+r,COLOR_RED);
	drawPixel(x+c,y-r,COLOR_RED);
	drawPixel(x-c,y-r,COLOR_RED);
      }
  }
}

void drawSquare(u_char x, u_char y, u_char s) {
  for (u_char r = 0; r < s; r++) {
    drawPixel(x,r+y,COLOR_BLACK);
    drawPixel(x+s,r+y,COLOR_BLACK);
  }
  for (u_char c = 0; c < s; c++) {
    drawPixel(c+x, y, COLOR_BLACK);
    drawPixel(c+x, y+s, COLOR_BLACK);
  }
}
void fillTrapezoid(u_char x, u_char y, u_char h) {
  for (u_char r = 0; r < h; r++) {
    u_char colStart = 0;
    u_char colEnd = x+20;
    for (u_char c = 0; c < 20; c++) {
      drawPixel(c+x+10, r+y, COLOR_BLACK);
    }
  
    for (u_char c = 0; c < r; c++) {
      drawPixel(c+x+30,r+y,COLOR_BLACK);
      drawPixel(9+x-c,r+y,COLOR_BLACK);
    }
  }
}
void drawDiamond(u_char x, u_char y) {
  for (u_char row = 0; row < 10; row++) {
    for (u_char col = 0; col < row; col++) {
      drawPixel(x-col, y+row, COLOR_BLACK);
      drawPixel(x+col, y+row, COLOR_BLACK);
      drawPixel(x-col, y+19-row, COLOR_BLACK);
      drawPixel(x+col, y+19-row, COLOR_BLACK);
    }
  }
}
/*
void drawThis(u_char fr, u_char size) {
  for (u_char c = 0; c <= size; c++) {
   
  }
}
*/
/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  clearScreen(COLOR_BLUE);

  //drawRightTri(5,5,20,80);
  //drawTri(10,10,50);
  //fillSquare(10,10,30);
  //drawSquare(10,10,30);
  //fillTrapezoid(10,10,10);
  //drawTriangle(20);
  //drawSquareDiamond(50,50,20);
  drawDiamond(40,40);
}
