#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <math.h>
#include "menu.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL2_rotozoom.h"

Uint32 color;

Menu createMenu(SDL_Renderer *renderer) {
    Menu myMenu; 
    
    // Initialisation par sécurité
    myMenu.background = NULL;
    myMenu.playButton = NULL;
    myMenu.soundMuteButton = NULL;

    myMenu.background = IMG_LoadTexture(renderer, "images\\BackgroundMenu.png");
    myMenu.playButton = IMG_LoadTexture(renderer, "images\\Prinbles_Asset_UNDER (v 1.1) (9_7_2023)\\png\\Buttons\\Rect\\PlayText\\Default.png");
    myMenu.soundMuteButton = IMG_LoadTexture(renderer, "images\\Prinbles_Asset_UNDER (v 1.1) (9_7_2023)\\png@2x\\Buttons\\Square\\SoundOff\\Hover@2x.png");

    // Position du bouton Play
    myMenu.playButtonRect.w = 250; 
    myMenu.playButtonRect.h = 100;  
    myMenu.playButtonRect.x = WINDOW_WIDTH/2 - 100;
    myMenu.playButtonRect.y = WINDOW_HEIGHT/2 - 40;

    // --- CORRECTION ICI : On ajoute bien "Rect" ---
    myMenu.soundMuteButtonRect.w = 80; 
    myMenu.soundMuteButtonRect.h = 80;  
    myMenu.soundMuteButtonRect.x = 20;
    myMenu.soundMuteButtonRect.y = 20;
    // ----------------------------------------------
    
    return myMenu;
}

void destroyMenu(Menu *myMenu) {
    if (myMenu->background != NULL) {
        SDL_DestroyTexture(myMenu->background);
    }
    if (myMenu->playButton != NULL) {
        SDL_DestroyTexture(myMenu->playButton);
    }
    if (myMenu->soundMuteButton != NULL) {
        // --- CORRECTION ICI : On détruit bien le soundMuteButton, pas le playButton ---
        SDL_DestroyTexture(myMenu->soundMuteButton); 
    }
}