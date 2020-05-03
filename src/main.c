#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>
#include "buzzer.h"
#include "soundEngine.h"
#include "spaceship.c"
#define GREEN_LED BIT6

u_char gameOver = 0;
u_char xLoc = screenWidth/2; /* for the ship since it only moves horizontally */
u_char xLazer = 0;           /* for the lazer shooting, it stays in the last xLoc pos */
u_char yLoc = screenHeight-35; /* for the lazer since it only moves vertically */
u_char shooting = 0;
Vec2 vel = {1,0};             /* for the alien (circle) to move and change over time */

void drawSpaceship(u_char x);
void drawLazer(u_char x, u_char y);
void clearLazer(u_char x, u_char y);


AbRectOutline fieldOutline = {	/* playing field */
  abRectOutlineGetBounds, abRectOutlineCheck,   
  {screenWidth/2 - 10, screenHeight/2 - 10}
};

Layer fieldLayer = {		/* playing field as a layer */
  (AbShape *) &fieldOutline,
  {screenWidth/2, screenHeight/2},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLUE,
  0
};

Layer layer0 = {		/**< Layer with a red circle */
  (AbShape *) &circle5,
  {screenWidth/2, 30}, /**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &fieldLayer,
};

/** Moving Layer
 *  Linked list of layer references
 *  Velocity represents one iteration of change (direction & magnitude)
 */
typedef struct MovLayer_s {
  Layer *layer;
  Vec2 velocity;
  struct MovLayer_s *next;
} MovLayer;

/* initial value of {0,0} will be overwritten */
MovLayer ml0 = { &layer0, {0,0}, 0 }; /**< this layer only moves */

void movLayerDraw(MovLayer *movLayers, Layer *layers)
{
  int row, col;
  MovLayer *movLayer;

  and_sr(~8);			/**< disable interrupts (GIE off) */
  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Layer *l = movLayer->layer;
    l->posLast = l->pos;
    l->pos = l->posNext;
  }
  or_sr(8);			/**< disable interrupts (GIE on) */


  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Region bounds;
    layerGetBounds(movLayer->layer, &bounds);
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1], 
		bounds.botRight.axes[0], bounds.botRight.axes[1]);
    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = bgColor;
	Layer *probeLayer;
	for (probeLayer = layers; probeLayer; 
	     probeLayer = probeLayer->next) { /* probe all layers, in order */
	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	    color = probeLayer->color;
	    break; 
	  } /* if probe check */
	} // for checking all layers at col, row
	lcd_writeColor(color); 
      } // for col
    } // for row
  } // for moving layer being updated
}	  



//Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}}; /**< Create a fence region */

/** Advances a moving shape within a fence
 *  
 *  \param ml The moving shape to be advanced
 *  \param fence The region which will serve as a boundary for ml
 */
void mlAdvance(MovLayer *ml, Region *fence)
{
  Vec2 newPos;
  Region shapeBoundary;
  
  vec2Add(&newPos, &ml->layer->posNext, &vel);
  int currentY = &ml->layer->posNext.axes[1];
  abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
  /**< collisions */
  if ((shapeBoundary.topLeft.axes[0] < fence->topLeft.axes[0]) ||
      (shapeBoundary.botRight.axes[0] > fence->botRight.axes[0]) ) {
    //TODO: check for alien last position, if alien gets closer to ship then speed up
    /*
    if (currentY > 1000)
      vel.axes[0] = vel.axes[0] > 0 ? 3 : -3;
    else if (currentY > 600) {
      vel.axes[0] = vel.axes[0] > 0 ? 2 : -2;
    }
    */
    vel.axes[0] = -vel.axes[0];
    newPos.axes[0] += (2*vel.axes[0]);
    newPos.axes[1] += 6;
  }	/**< if outside of fence */

  ml->layer->posNext = newPos;
}


u_int bgColor = COLOR_BLACK;     /**< The background color */
int redrawScreen = 1;           /**< Boolean for whether screen needs to be redrawn */

Region fieldFence;		/**< fence around playing field  */


/** Initializes everything, enables interrupts and green LED, 
 *  and handles the rendering for the screen
 */
void main()
{
  P1DIR |= GREEN_LED;		/**< Green led on when CPU on */		
  P1OUT |= GREEN_LED;

  configureClocks();
  lcd_init();
  shapeInit();
  p2sw_init(15);

  shapeInit();
  buzzer_init();

  layerInit(&layer0);
  layerDraw(&layer0);

  layerGetBounds(&fieldLayer, &fieldFence);
  drawString5x7(screenWidth/2-30,8, "Score:", COLOR_GREEN, COLOR_BLACK);
  drawString5x7(screenWidth/2+10,8,"0", COLOR_GREEN, COLOR_BLACK);

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  for(;;) { 
    if (gameOver) {
      P1OUT &= ~GREEN_LED;    /**< Green led off witHo CPU */
      buzzer_set_period(0);
      break;
    }
    while (!redrawScreen) { /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED;    /**< Green led off witHo CPU */
      or_sr(0x10);	      /**< CPU OFF */
    }
    
    P1OUT |= GREEN_LED;       /**< Green led on when CPU on */
    redrawScreen = 0;
    movLayerDraw(&ml0, &layer0);
    //&ml0->
    drawSpaceship(xLoc);
    if (shooting) {
      if (yLoc < 20) {        /** checks boundaries **/
	clearLazer(xLazer, yLoc);
	yLoc = screenHeight-35;
	shooting = 0;
      }
      else {
	yLoc -= 3;
	drawLazer(xLazer, yLoc);
      }
    }
        
    u_int switches = p2sw_read(), i;
    /* update shapes based on switch press */
    for (i = 0; i < 4; i++)
      if(!(switches & (1<<i))) {
	if (i == 0 && xLoc > 22)
	  xLoc-=2;
	else if ((i == 1 || i == 2) && !shooting) {
	  xLazer = xLoc;
	  shooting = 1;
	}
	else if (i == 3 && xLoc < screenWidth-22)
	  xLoc+=2;
      }
  }
  and_sr(~0x8);	              /**< GIE (enable interrupts) */
  or_sr(0x10);	              /**< CPU OFF */
}

/** Watchdog timer interrupt handler. 15 interrupts/sec */
void wdt_c_handler()
{
  static short count = 0;
  static char songCount = 0;
  P1OUT |= GREEN_LED;		      /**< Green LED on when cpu on */
  count ++;
  songCount++;
    
  if (count == 10) {
    mlAdvance(&ml0, &fieldFence);
    redrawScreen = 1;
    count = 0;
  }
  if (songCount == 10) {
    play_song();
    songCount = 0;
  }
  P1OUT &= ~GREEN_LED;		    /**< Green LED off when cpu off */ 
}
