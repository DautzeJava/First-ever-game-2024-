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

void loadBackground(SDL_Renderer *render, Orc* orc)
{
    SDL_Surface *backgroundImage = IMG_Load("src\\images\\background1F.png");
    SDL_Rect rectangle;
    if(backgroundImage == NULL)
    {
        fprintf(stderr, "Erreur dans la creation de la surface background");
    }
    rectangle.x = 0;
    rectangle.y = 0 ;

    if(orc->rect.x < (WINDOW_WIDTH) - 80)
    {
    }

    rectangle.h = WINDOW_HEIGHT;
    rectangle.w = WINDOW_WIDTH;
    SDL_Texture *background = SDL_CreateTextureFromSurface(render, backgroundImage);
    if(background == NULL)
    {
        fprintf(stderr, "Erreur dans la creation de la texture background");
    }
    SDL_FreeSurface(backgroundImage);
    SDL_RenderCopy(render, background, NULL, &rectangle);
}