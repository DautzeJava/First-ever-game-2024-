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

// Fonction pour créer un Orc avec les paramètres donnés
Orc *createOrc(int pv, int attack, SDL_Renderer *render, const char *imagePath) {
    // Allocation de mémoire pour l'orc
    Orc *orc = malloc(sizeof(Orc));
    if (orc == NULL) {
        fprintf(stderr, "Erreur dans la création de l'orc\n");
        return NULL;
    }

    // Initialisation des attributs de l'orc
    orc->pv = pv;
    orc->attack = attack;
    orc->rect.x = (WINDOW_WIDTH / 2) - (ORC_WIDTH / 2);
    orc->rect.y = (WINDOW_HEIGHT / 2) - (ORC_HEIGHT / 2);
    orc->rect.h = ORC_HEIGHT;
    orc->rect.w = ORC_WIDTH;

    // Chargement de l'image statique de l'orc (Chemin corrigé)
    SDL_Surface *skin = IMG_Load("images\\SurMesure\\OrcStatic.png");
    if (skin == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface de l'orc : %s\n", IMG_GetError());
        free(orc);
        return NULL;
    }

    // Création de la texture à partir de la surface chargée
    orc->texture = SDL_CreateTextureFromSurface(render, skin);
    SDL_FreeSurface(skin); // Libération de la surface après la création de la texture

    if (orc->texture == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture de l'orc : %s\n", SDL_GetError());
        free(orc);
        return NULL;
    }
    return orc;
}

// Fonction pour détruire un Orc et libérer sa mémoire
void destroyOrc(Orc *orc) 
{
    if (orc != NULL) {
        if (orc->texture != NULL) {
            SDL_DestroyTexture(orc->texture);
        }
        free(orc);
    }
}

// Fonction pour animer l'attaque de l'orc
void attackOrcIn(Orc *orc, SDL_Renderer *render, SDL_bool attacking) 
{
    // Chemin corrigé
    SDL_Surface *attackAnimationBaseSurface = IMG_Load("images/Orc-Attack01Test.png");
    if (attackAnimationBaseSurface == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return;
    }

    SDL_Texture *attackAnimation = SDL_CreateTextureFromSurface(render, attackAnimationBaseSurface);
    SDL_FreeSurface(attackAnimationBaseSurface);

    if (attackAnimation == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return;
    }

    SDL_RenderClear(render);
    loadBackgroundA(render, orc);
    SDL_RenderCopy(render, attackAnimation, NULL, &orc->rect);
    SDL_RenderPresent(render);
    
    SDL_Delay(300); // Temps de préparation

    SDL_DestroyTexture(attackAnimation); // Libération de la texture après utilisation
}



// Fonction pour animer la fin de l'attaque de l'orc
void attackOrcOut(Orc *orc, SDL_Renderer *render) {
    // Chemin corrigé
    SDL_Surface *attackAnimationBaseSurface = IMG_Load("images/Orc-Attack02.png");
    if (attackAnimationBaseSurface == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return;
    }

    // Création de la texture à partir de la surface d'attaque
    SDL_Texture *attackAnimation = SDL_CreateTextureFromSurface(render, attackAnimationBaseSurface);
    SDL_FreeSurface(attackAnimationBaseSurface); // Libération de la surface après la création de la texture

    if (attackAnimation == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return;
    }

    Mix_Chunk *soundAttack = NULL;
    // Chemin corrigé
    soundAttack = Mix_LoadWAV("sound/soundAttack.wav");
    if(soundAttack == NULL)
    {
        fprintf(stderr, "Erreur dans la lecture de soundAttack: %s\n", Mix_GetError());
    } else {
        Mix_VolumeChunk(soundAttack, 8);
        Mix_PlayChannel(-1, soundAttack, 0);
    }

    // Affichage de l'animation de fin d'attaque
    SDL_RenderClear(render);
    loadBackgroundA(render, orc);
    SDL_RenderCopy(render, attackAnimation, NULL, &orc->rect);
    SDL_RenderPresent(render);
    
    SDL_Delay(300); // Temps d'impact
    
    // CORRECTION DU BUG DE MEMOIRE : Libérer avant de mettre à NULL
    if (soundAttack != NULL) {
        Mix_FreeChunk(soundAttack);
        soundAttack = NULL;
    }
    
    SDL_DestroyTexture(attackAnimation); // Libération de la texture après utilisation
}

void attackOrcEnd(Orc *orc, SDL_Renderer *render, SDL_bool attacking) 
{
    // Chemin corrigé
    SDL_Surface *attackAnimationBaseSurface = IMG_Load("images/Orc-Attack03.png");
    if (attackAnimationBaseSurface == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return;
    }

    SDL_Texture *attackAnimation = SDL_CreateTextureFromSurface(render, attackAnimationBaseSurface);
    SDL_FreeSurface(attackAnimationBaseSurface);

    if (attackAnimation == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return;
    }

    SDL_RenderClear(render);
    loadBackgroundA(render, orc);
    SDL_RenderCopy(render, attackAnimation, NULL, &orc->rect);
    SDL_RenderPresent(render);
    
    SDL_Delay(200); // Temps de récupération

    SDL_DestroyTexture(attackAnimation); // Libération de la texture après utilisation
}

void attackOrcInReverse(Orc *orc, SDL_Renderer *render, SDL_bool attacking) 
{
    // Chemin corrigé
    SDL_Surface *attackAnimationBaseSurface = IMG_Load("images/Orc-Attack01TestReverse.png");
    if (attackAnimationBaseSurface == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return;
    }

    SDL_Texture *attackAnimation = SDL_CreateTextureFromSurface(render, attackAnimationBaseSurface);
    SDL_FreeSurface(attackAnimationBaseSurface);

    if (attackAnimation == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return;
    }

    SDL_RenderClear(render);
    loadBackgroundA(render, orc);
    SDL_RenderCopy(render, attackAnimation, NULL, &orc->rect);
    SDL_RenderPresent(render);
    
    SDL_Delay(300);

    SDL_DestroyTexture(attackAnimation); // Libération de la texture après utilisation
}

// Fonction pour animer la fin de l'attaque de l'orc
void attackOrcOutReverse(Orc *orc, SDL_Renderer *render) {
    // Chemin corrigé
    SDL_Surface *attackAnimationBaseSurface = IMG_Load("images/Orc-Attack02Reverse.png");
    if (attackAnimationBaseSurface == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return;
    }

    // Création de la texture à partir de la surface d'attaque
    SDL_Texture *attackAnimation = SDL_CreateTextureFromSurface(render, attackAnimationBaseSurface);
    SDL_FreeSurface(attackAnimationBaseSurface); // Libération de la surface après la création de la texture

    if (attackAnimation == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return;
    }

    Mix_Chunk *soundAttack = NULL;
    // Chemin corrigé
    soundAttack = Mix_LoadWAV("sound/soundAttack.wav");
    if(soundAttack == NULL)
    {
        fprintf(stderr, "Erreur dans la lecture de soundAttack: %s\n", Mix_GetError());
    } else {
        Mix_VolumeChunk(soundAttack, 8);
        Mix_PlayChannel(-1, soundAttack, 0);
    }

    // Affichage de l'animation de fin d'attaque
    SDL_RenderClear(render);
    loadBackgroundA(render, orc);
    SDL_RenderCopy(render, attackAnimation, NULL, &orc->rect);
    SDL_RenderPresent(render);
    
    SDL_Delay(300);
    
    // CORRECTION DU BUG DE MEMOIRE : Libérer avant de mettre à NULL
    if (soundAttack != NULL) {
        Mix_FreeChunk(soundAttack);
        soundAttack = NULL;
    }
    
    SDL_DestroyTexture(attackAnimation); // Libération de la texture après utilisation
}

void attackOrcEndReverse(Orc *orc, SDL_Renderer *render, SDL_bool attacking) 
{
    // Chemin corrigé
    SDL_Surface *attackAnimationBaseSurface = IMG_Load("images/Orc-Attack03Reverse.png");
    if (attackAnimationBaseSurface == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return;
    }

    SDL_Texture *attackAnimation = SDL_CreateTextureFromSurface(render, attackAnimationBaseSurface);
    SDL_FreeSurface(attackAnimationBaseSurface);

    if (attackAnimation == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return;
    }

    SDL_RenderClear(render);
    loadBackgroundA(render, orc);
    SDL_RenderCopy(render, attackAnimation, NULL, &orc->rect);
    SDL_RenderPresent(render);
    
    SDL_Delay(200);

    SDL_DestroyTexture(attackAnimation); // Libération de la texture après utilisation
}

void movRight(Orc * orc)
{
    if(orc->rect.x < WINDOW_WIDTH - ORC_WIDTH - 12)
    orc->rect.x += 20;
    SDL_Delay(80);
}
void movLeft(Orc * orc)
{
    if(orc->rect.x > 0 + 12)
    orc->rect.x -= 20;
    SDL_Delay(80);
}
void movBottom(Orc * orc)
{
    if(orc->rect.y < WINDOW_HEIGHT - 200)
    orc->rect.y += 20;
    SDL_Delay(80);
}
void movUp(Orc * orc)
{
    if(orc->rect.y > 0 + 48)
    orc->rect.y -= 24;
    SDL_Delay(80);
}

void walkSoundEffect()
{
    // Utilisation de static pour ne charger le son qu'une seule fois
    static Mix_Chunk *walkSound = NULL;
    if(walkSound == NULL)
    {
        walkSound = Mix_LoadWAV("sound/walkSound.wav");
        if(walkSound == NULL)
        {
            fprintf(stderr, "Erreur dans le chargement de walkSound: %s\n", Mix_GetError());
        }
    }
    Mix_VolumeChunk(walkSound, 100);
    Mix_PlayChannel(-1, walkSound, 0);
}

void checkFreeWalkSound(Mix_Chunk *walkSound)
{
    if(walkSound != NULL && Mix_Playing(-1) == 0)
    {
        Mix_FreeChunk(walkSound);
    }
}