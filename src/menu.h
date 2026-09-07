#ifndef MENU_H
#define MENU_H

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <math.h>
#include "SDL2_gfxPrimitives.h"
#include "SDL2_rotozoom.h"

// 1. D'ABORD LA STRUCTURE
typedef struct {
    SDL_Texture *background;
    SDL_Texture *playButton;
    SDL_Texture *soundOnOffButton;
    SDL_Rect soundOnOffButtonRect;
    SDL_Rect playButtonRect;
} Menu;

// 2. ENSUITE LES FONCTIONS (qui ont besoin de connaître la structure au-dessus)
Menu createMenu(SDL_Renderer *renderer);
void destroyMenu(Menu *myMenu);
void soundOnOff(SDL_Renderer *renderer, Menu *menu);
#endif