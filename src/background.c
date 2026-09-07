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

void loadBackgroundA(SDL_Renderer *render, Orc* orc)
{
    // Chemin corrigé
    SDL_Surface *backgroundImage = IMG_Load("images\\SurMesure\\Background\\background1F.png");
    SDL_Rect rectangle;
    
    if(backgroundImage == NULL)
    {
        fprintf(stderr, "Erreur dans la creation de la surface background : %s\n", IMG_GetError());
        return; // Stoppe la fonction pour éviter le crash si l'image manque
    }
    
    rectangle.x = 0;
    rectangle.y = 0;

    if(orc->rect.x < (WINDOW_WIDTH) - 80)
    {
        // Réservé pour un futur scrolling
    }

    rectangle.h = WINDOW_HEIGHT;
    rectangle.w = WINDOW_WIDTH;
    
    SDL_Texture *background = SDL_CreateTextureFromSurface(render, backgroundImage);
    SDL_FreeSurface(backgroundImage); // Libération de la surface
    
    if(background == NULL)
    {
        fprintf(stderr, "Erreur dans la creation de la texture background : %s\n", SDL_GetError());
        return;
    }
    
    // Affichage de l'arrière-plan
    SDL_RenderCopy(render, background, NULL, &rectangle);
    
    // CORRECTION CRITIQUE : Destruction de la texture après affichage
    SDL_DestroyTexture(background);
}