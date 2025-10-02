#ifndef MAP1_H
#define MAP1_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Map1 {
public:
    Map1(SDL_Renderer* renderer);
    ~Map1();

    void render(SDL_Renderer* renderer, SDL_Rect camera);

private:
    std::vector<std::vector<int>> mapData;   // ma trận map
    SDL_Texture* tile1;  // đất
    SDL_Texture* tile2;  // cỏ
    SDL_Texture* tile3;  // đá
    int tileSize;        // kích thước 1 ô
};

#endif
