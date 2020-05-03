#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>


void drawSpaceship(u_char x) {
  for (u_char r = 0; r < 10; r++) {
    for (u_char c = 0; c < r; c++) {
      drawPixel(x+c,screenHeight-30+r,COLOR_GREEN);
      drawPixel(x-c,screenHeight-30+r,COLOR_GREEN);
    }
  }

  for (u_char c = 0; c < 11; c++) {
    for (u_char r = 0; r <= c; r++) {
      drawPixel(x+c,screenHeight-30+r,COLOR_BLACK);
      drawPixel(x-c,screenHeight-30+r,COLOR_BLACK);
    }
  }
}
void drawLazer(u_char x, u_char y) {
  for (u_char r = 0; r < 2; r++) {
    for (u_char c = 0; c < 2; c++) {
      drawPixel(x+c,y+r, COLOR_RED); 
    }
  }

  for (u_char c = 0; c < 2; c++) {
    for (u_char r = 0; r < 4; r++) {
      drawPixel(x+c, y+2+r, COLOR_BLACK);
    }
  }
}
void clearLazer(u_char x, u_char y) {
  for (u_char c = 0; c < 2; c++) {
    for (u_char r = 0; r < 4; r++) {
      drawPixel(x+c, y+r, COLOR_BLACK);
    }
  }
}
