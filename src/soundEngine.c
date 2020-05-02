#include <msp430.h>  
#include "soundEngine.h"
#include "buzzer.h"

u_char song_selection = 0;
unsigned short song_state = 0;
u_char length = 63;

/* song notes form secrets by one republic */


/* plays a note from a song everytime it is called */
void play_song() {
  if(song_state > length)
    song_state = 0; /* resets song state at the end (to repeat) */
  
  short cycle = 2000000/secrets[song_state]; /* finds out the cycle for the buzzer */
  buzzer_set_period(cycle);
  song_state++;
}
