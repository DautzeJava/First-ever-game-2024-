#ifndef ORC_H
#define ORC_H

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
#define ORC_WIDTH 66
#define ORC_HEIGHT 45

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

#define ORC_PV 200
#define ORC_ATTACK 100

typedef struct Orc {
    int pv;
    int attack;
    SDL_Rect rect;
    SDL_Texture *texture;
} Orc;

Orc *createOrc(int pv, int attack, SDL_Renderer *render, const char *imagePath);
void loadBackgroundA(SDL_Renderer *render, Orc* orc);
void destroyOrc(Orc *orc);
void attackOrcIn(Orc *orc, SDL_Renderer *render, SDL_bool attacking);
void attackOrcInReverse(Orc *orc, SDL_Renderer *render, SDL_bool attacking);
void attackOrcOut(Orc *orc, SDL_Renderer *render);
void attackOrcOutReverse(Orc *orc, SDL_Renderer *render);
static void walkSoundEffect();
void checkFreeWalkSound(Mix_Chunk *walkSound);
void movRight(Orc * orc);
void movLeft(Orc * orc);
void movBottom(Orc * orc);
void movUp(Orc * orc);
void createMenu(SDL_Renderer *render);


#endif