#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <math.h>
#include "orc.h"
#include "SDL2_gfxPrimitives.h"

void cleanQuit(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, Mix_Music *music);
SDL_Texture *reverseOrcToLeft(Orc *orc, SDL_Renderer *render);
SDL_Texture *reverseOrcToRight(Orc *orc, SDL_Renderer *render);
void walkSoundEffect();

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "Erreur dans la création de la fenêtre : %s\n", SDL_GetError());
        cleanQuit(NULL, NULL, NULL, NULL);
        return EXIT_FAILURE;
    }

    // Création du renderer
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == NULL) {
        fprintf(stderr, "Erreur dans la création du renderer : %s\n", SDL_GetError());
        cleanQuit(window, NULL, NULL, NULL);
        return EXIT_FAILURE;
    }

    // Création de l'orc et chargement de sa texture
    Orc *orc = createOrc(200, 100, render, "images/Orc.png");
    if (orc == NULL) {
        cleanQuit(window, render, NULL, NULL);
        return EXIT_FAILURE;
    }

    // Initialisation de la bibliothèque SDL_mixer pour l'audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Erreur dans l'ouverture du module audio SDL_mixer : %s\n", Mix_GetError());
        cleanQuit(window, render, orc->texture, NULL);
        return EXIT_FAILURE;
    }

    // Chargement de la musique de fond
    Mix_Music *music = Mix_LoadMUS("sound/underTale.mp3");
    if (music == NULL) {
        fprintf(stderr, "Erreur dans le chargement du fichier sonore : %s\n", Mix_GetError());
        cleanQuit(window, render, orc->texture, NULL);
        return EXIT_FAILURE;
    }

    // Lecture en boucle de la musique
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(8); // Réglage du volume de la musique (0-128)

    // Variables pour le déplacement et les animations
    SDL_bool prog_launched = SDL_TRUE;
    SDL_Event event;
    SDL_bool attacking = SDL_FALSE;
    SDL_bool movToRight = SDL_TRUE;
    int i = 0;

    // Boucle principale du programme
    while (prog_launched) {
        // Gestion des événements SDL
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    prog_launched = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_d:
                            movRight(orc);
                            i++;
                            if (!movToRight) {
                                SDL_DestroyTexture(orc->texture); // Évite la fuite de mémoire
                                orc->texture = reverseOrcToRight(orc, render);
                            }
                            movToRight = SDL_TRUE;
                            if (i == 1) walkSoundEffect();
                            break;
                        case SDLK_a:
                            movLeft(orc);
                            i++;
                            if (movToRight) {
                                SDL_DestroyTexture(orc->texture); // Évite la fuite de mémoire
                                orc->texture = reverseOrcToLeft(orc, render);
                            }
                            movToRight = SDL_FALSE;
                            if (i == 1) walkSoundEffect();
                            break;
                        case SDLK_w:
                            movUp(orc);
                            i++;
                            if (i == 1) walkSoundEffect();
                            break;
                        case SDLK_s:
                            movBottom(orc);
                            i++;
                            if (i == 1) walkSoundEffect();
                            break;
                        case SDLK_x:
                            if (!attacking) {
                                attacking = SDL_TRUE;
                                if (movToRight) {
                                    attackOrcIn(orc, render, attacking);
                                    attacking = SDL_FALSE;
                                    attackOrcOut(orc, render);
                                } else {
                                    attackOrcInReverse(orc, render, attacking);
                                    attacking = SDL_FALSE;
                                    attackOrcOutReverse(orc, render);
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_d:
                        case SDLK_a:
                        case SDLK_w:
                        case SDLK_s:
                            i = 0;
                            Mix_HaltChannel(-1); // Arrête le son de marche au relâchement
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // Effacer l'écran
        SDL_RenderClear(render);

        // Dessiner l'arrière-plan
        loadBackgroundA(render, orc);

        // Dessiner l'orc
        SDL_RenderCopy(render, orc->texture, NULL, &orc->rect);

        // Mettre à jour l'affichage
        SDL_RenderPresent(render);

        // Limiter la fréquence d'images
        SDL_Delay(1000 / 165);
    }

    // Nettoyage et fermeture du programme
    destroyOrc(orc);
    // On passe NULL pour la texture car destroyOrc est censé l'avoir déjà libérée
    cleanQuit(window, render, NULL, music); 
    return 0;
}

// Fonction pour nettoyer et quitter le programme en cas d'erreur
void cleanQuit(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, Mix_Music *music) {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    if (music != NULL) {
        Mix_FreeMusic(music);
    }

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

// Fonction pour charger l'animation d'attaque vers la droite
SDL_Texture *reverseOrcToRight(Orc *orc, SDL_Renderer *render) {
    SDL_Surface *orcStaticToRight = IMG_Load("images/Orc-static.png");
    if (orcStaticToRight == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture *OrcStaticR = SDL_CreateTextureFromSurface(render, orcStaticToRight);
    SDL_FreeSurface(orcStaticToRight);

    if (OrcStaticR == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return NULL;
    }

    return OrcStaticR;
}

// Fonction pour charger l'animation d'attaque vers la gauche
SDL_Texture *reverseOrcToLeft(Orc *orc, SDL_Renderer *render) {
    SDL_Surface *orcStaticToLeft = IMG_Load("images/Orc-static-reverse.png");
    if (orcStaticToLeft == NULL) {
        fprintf(stderr, "Erreur dans la création de la surface d'attaque : %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture *OrcStaticL = SDL_CreateTextureFromSurface(render, orcStaticToLeft);
    SDL_FreeSurface(orcStaticToLeft);

    if (OrcStaticL == NULL) {
        fprintf(stderr, "Erreur dans la création de la texture d'attaque : %s\n", SDL_GetError());
        return NULL;
    }

    return OrcStaticL;
}

// Fonction pour jouer l'effet sonore de marche
static void walkSoundEffect() {
    // Le mot-clé static permet de ne charger le son qu'une seule fois en mémoire
    static Mix_Chunk *walkSound = NULL; 
    
    if (walkSound == NULL) {
        walkSound = Mix_LoadWAV("sound/walkSound.wav");
        if (walkSound == NULL) {
            fprintf(stderr, "Erreur dans le chargement du son de marche : %s\n", Mix_GetError());
            return;
        }
        Mix_VolumeChunk(walkSound, MIX_MAX_VOLUME / 2);
    }

    Mix_PlayChannel(-1, walkSound, 0);
}