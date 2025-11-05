#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>

struct GameOptions {
    bool musicOn = true;
    bool sfxOn = true;
};

bool hienthimenu(SDL_Window* cuaso, SDL_Renderer* ve);
void hienThiOptions(SDL_Window* cuaso, SDL_Renderer* ve, GameOptions& options);




#endif
