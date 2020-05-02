#ifndef soundEngine_included
#define soundEngine_included

/* soundbank -------- notes with s = sharp */
#define C3 131
#define CS3 139
#define D3 147
#define DS3 156
#define E3 165
#define F3 175
#define FS3 185
#define G3 196
#define GS3 208
#define A3 220
#define AS3 233
#define B3 247
#define C4 262
#define CS4 279
#define D4 294
#define DS4 311
#define E4 330;
#define F4 349
#define FS4 370
#define G4 392
#define GS4 415
#define A4 440
#define AS4 466
#define B4 494
#define C5 523
#define CS5 554
#define D5 587
#define DS5 622
#define E5 659
#define F5 699
#define FS5 740
#define G5 784
#define GS5 831
#define A5 880
#define AS5 932
#define B5 988


unsigned char song_selection;
unsigned char sound_state;

void song_state_reset();
void play_song();

#endif //included
