#include <msp430.h>  
#include "soundEngine.h"
#include "buzzer.h"

unsigned char song_selection = 0;
unsigned short song_state = 0;
unsigned char length = 12;

/* song notes form secrets by one republic */
short song[12] = {F3,F4,F3,F4,0,0,0,0,0,0,0,0};

/* plays a note from a song everytime it is called */
void play_song() {
  if(song_state > length-1)
    song_state = 0; /* resets song state at the end (to repeat) */
  
  short cycle = 2000000/song[song_state]; /* finds out the cycle for the buzzer */
  buzzer_set_period(cycle);
  song_state++;
}
