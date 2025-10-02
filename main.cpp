#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "menu.h"
#include "map1.h"
#include "player.h"

#ifdef main   // dung de fix main k chay dc
#undef main
#endif
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  //khoi tao cua sorender vaxac dinh loi
        std::cout << "loisdl: " << SDL_GetError() <<std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {  // tuong tu
        std::cout << "loianh:" << IMG_GetError()<< std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* cuaso = SDL_CreateWindow("Game SDL2",    // tao cua so render
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_SHOWN);

    SDL_Renderer* ve = SDL_CreateRenderer(cuaso, -1, SDL_RENDERER_ACCELERATED);

    bool vaogame = hienthimenu(cuaso, ve); // dung de hien thi menu

    if (vaogame) {   // dung de vao game
    std::cout << "vao game" << std::endl;

    Map1 map(ve);
    SDL_Rect camera = {0, 0, 1280, 720};

    bool running = true;   // thêm biến này để vòng lặp chạy
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        // TODO: update camera theo vị trí player sau này

        SDL_SetRenderDrawColor(ve, 0, 0, 0, 255); // xóa màn hình
        SDL_RenderClear(ve);

        map.render(ve, camera);

        SDL_RenderPresent(ve);
    }
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
