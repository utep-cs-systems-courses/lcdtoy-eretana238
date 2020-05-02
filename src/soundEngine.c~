#include <msp430.h>  
#include "soundEngine.h"
#include "stateMachines.h"
#include "buzzer.h"

unsigned char song_selection = 0;
unsigned short song_state = 0;

/* song notes form secrets by one republic */
unsigned short secrets[64] = {D4,FS4,A4,FS4,A4,FS4,D4,FS4,D4,FS4,A4,FS4,A4,FS4,D4,FS4,CS4,FS4,A4,FS4,A4,FS4,CS4,FS4,CS4,FS4,A4,FS4,A4,FS4,CS4,FS4,B3,FS4,B4,FS4,B4,FS4,B3,FS4,B3,FS4,B4,FS4,B4,FS4,B3,FS4,G3,G4,B4,G4,B4,G4,G3,G4,G3,G4,A4,G4,A4,G4,G3,G4};

/* plays a note from a song everytime it is called */
void play_song() {
  if(song_state > 63)
    song_state = 0; /* resets song state at the end (to repeat) */
  
  short cycle = 2000000/secrets[song_state]; /* finds out the cycle for the buzzer */
  buzzer_set_period(cycle);
  song_state++;
}
