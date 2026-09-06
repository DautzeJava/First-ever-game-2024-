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
    SDL_Texture *soundMuteButton;
    SDL_Rect soundMuteButtonRect;
    SDL_Rect playButtonRect;
} Menu;

// 2. ENSUITE LES FONCTIONS (qui ont besoin de connaître la structure au-dessus)
Menu createMenu(SDL_Renderer *renderer);
void destroyMenu(Menu *myMenu);

#endif