# Project 3: Graphics LCD Toy

## Description
This lab consists of elaborating from lab2 to create more of a complex and fun toy/game using the `MSP430` LCD, interrupts, and waking/sleeping the CPU. Given the stressful time limit of only a couple of days, the aim for this project was to replicate classic arcade game *Galaga* or *Space Invaders* in a more simple fashion. The game consists of a spaceship in which the user can control, an alien that tries to come close and destroy the spaceship, and a score board. **However, a couple of implementations are missing due to time restrictions.**

### Gameplay
The player controls a spaceship loaded with lazers to shoot while an alien ship come closer over time. The objective is to shoot the alien before it reaches the spaceship (shooting is possible but the alien won't get destroyed). But if the enemy comes too close... GAMEOVER.


## How to compile and run
Once downloading the repo, please go through the follwing steps:

1. Compile all of the libraries and the `src` folder
```
../lcdtoy-eretana238> make all
```
2. Change direcotry to `src` and load the project into the `MSP430`
```
../lcdtoy-eretana238/src> make load
```
3. Congratulations! As of now the program should be running in the device without issues.

## How to use
To understand the controls of the game, the functions for each switch are mentioned below:
- SW1
    - Moves the spaceship left horizontally
- SW2
    - Spaceship shoots one bullet
- SW3
    - Spaceship shoots one bullet
- SW4
    - Moves the spaceship right horizontally
## Contents

- soundEngine.c
    - The source of sound being played in the buzzer. The engine has a sound library in which it can play theme songs and sound effects. To keep it simple, a flying sound effect is played throughout the game.
- spaceship.c
    - Contains all of the data for the spaceship including the lazer. Also methods such as drawing the lazer, spaceship and clearing leftover pixels from lazer.
- switches.c
    - Allows for the `MSP430` to take input from the player. Senses a button press and tells the model what to do.
- main.c
    - Where all of the contents get combined and manages the game state if it is active or inactive. It controls the CPU by turning it on when an update to the display will happen, and off when no updates are necessary. Ultimately, when the game state reaches game over, the CPU is turned off since no more updates are necessary.