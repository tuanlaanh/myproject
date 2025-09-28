#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "menu.h"

#ifdef main   // dung de fix main k chay dc
#undef main
#endif
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  //khoi tao cua sorender vaxac dinh loi
        std::cout << "Lỗi SDL: " << SDL_GetError() <<std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {  // tuong tu
        std::cout << "Lỗi SDL_image:" << IMG_GetError()<< std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* cuaso = SDL_CreateWindow("Game SDL2",    // tao cua so render
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* ve = SDL_CreateRenderer(cuaso, -1, SDL_RENDERER_ACCELERATED);

    bool vaogame = hienthimenu(cuaso, ve); // dung de hien thi menu

    if (vaogame) {   // dung de vao game
        std::cout<<"vao game";
        // TODO: viết game loop
    }

    SDL_DestroyRenderer(ve);    //giai phong tai nguyen
    SDL_DestroyWindow(cuaso);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

#ifdef _WIN32
#include <windows.h>

#endif
