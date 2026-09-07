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
Menu myMenu; 

Menu createMenu(SDL_Renderer *renderer) {
    
    // Initialisation par sécurité
    myMenu.background = NULL;
    myMenu.playButton = NULL;
    myMenu.soundOnOffButton = NULL;

    myMenu.background = IMG_LoadTexture(renderer, "images\\BackgroundMenu.png");
    myMenu.playButton = IMG_LoadTexture(renderer, "images\\Prinbles_Asset_UNDER (v 1.1) (9_7_2023)\\png\\Buttons\\Rect\\PlayText\\Default.png");
    myMenu.soundOnOffButton = IMG_LoadTexture(renderer, "images\\Prinbles_Asset_UNDER (v 1.1) (9_7_2023)\\png@2x\\Buttons\\Square\\SoundOn\\Hover@2x.png");

    // Position du bouton Play
    myMenu.playButtonRect.w = 250; 
    myMenu.playButtonRect.h = 100;  
    myMenu.playButtonRect.x = WINDOW_WIDTH/2 - 100;
    myMenu.playButtonRect.y = WINDOW_HEIGHT/2 - 40;

    // --- CORRECTION ICI : On ajoute bien "Rect" ---
    myMenu.soundOnOffButtonRect.w = 80; 
    myMenu.soundOnOffButtonRect.h = 80;  
    myMenu.soundOnOffButtonRect.x = 20;
    myMenu.soundOnOffButtonRect.y = 20;
    // ----------------------------------------------
    
    return myMenu;
}

void soundOnOff(SDL_Renderer *renderer, Menu *menu) {
    static int isMuted = 0; 
    
    // Destruction de l'ancienne texture avant de charger la nouvelle
    if (menu->soundOnOffButton != NULL) {
        SDL_DestroyTexture(menu->soundOnOffButton);
    }

    if (!isMuted) {
        // Couper le son
        Mix_VolumeMusic(0);
        menu->soundOnOffButton = IMG_LoadTexture(renderer, "images/Prinbles_Asset_UNDER (v 1.1) (9_7_2023)/png@2x/Buttons/Square/SoundOff/Hover@2x.png");
        isMuted = 1;
    } else {
        // Remettre le son
        Mix_VolumeMusic(10);
        menu->soundOnOffButton = IMG_LoadTexture(renderer, "images/Prinbles_Asset_UNDER (v 1.1) (9_7_2023)/png@2x/Buttons/Square/SoundOn/Hover@2x.png");
        isMuted = 0;
    }
}

void destroyMenu(Menu *myMenu) {
    if (myMenu->background != NULL) {
        SDL_DestroyTexture(myMenu->background);
    }
    if (myMenu->playButton != NULL) {
        SDL_DestroyTexture(myMenu->playButton);
    }
    if (myMenu->soundOnOffButton != NULL) {
        // --- CORRECTION ICI : On détruit bien le soundMuteButton, pas le playButton ---
        SDL_DestroyTexture(myMenu->soundOnOffButton); 
    }
}
