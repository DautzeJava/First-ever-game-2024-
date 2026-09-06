#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <math.h>
#include "orc.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL2_rotozoom.h"


Uint32 color;


void createMenu(SDL_Renderer *render)
{
    SDL_Surface *menu = NULL;
    SDL_Texture *playButton = NULL;
    menu = IMG_Load("src\\images\\Prinbles_Asset_UNDER (v 1.1) (9_7_2023)\\png\\Buttons\\Rect\\PlayText\\Default.png");
    SDL_CreateTextureFromSurface(render, menu);
    SDL_FreeSurface(menu);
    SDL_RenderCopy(render, playButton, NULL, NULL);
}