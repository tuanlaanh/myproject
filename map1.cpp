#include "map1.h"
#include <iostream>

Map1::Map1(SDL_Renderer* renderer) {
    // ma trận map mẫu
    int level[11][20] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // đất
        {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2}, // cỏ
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // đá
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    // copy mảng level vào mapData
    mapData.resize(11, std::vector<int>(20));
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 20; x++) {
            mapData[y][x] = level[y][x];
        }
    }

    // load tile textures
    tile1 = IMG_LoadTexture(renderer, "tile_0002.png"); // đất
    tile2 = IMG_LoadTexture(renderer, "tile_0006.png"); // cỏ
    tile3 = IMG_LoadTexture(renderer, "tile_0006.png"); // đá

    if (!tile1 || !tile2 || !tile3) {
        std::cout << "Lỗi load tile: " << IMG_GetError() << std::endl;
    }

    tileSize = 64; // mỗi ô 64x64 px
}

Map1::~Map1() {
    if (tile1) SDL_DestroyTexture(tile1);
    if (tile2) SDL_DestroyTexture(tile2);
    if (tile3) SDL_DestroyTexture(tile3);
}

void Map1::render(SDL_Renderer* renderer, SDL_Rect camera) {
    for (int y = 0; y < (int)mapData.size(); y++) {
        for (int x = 0; x < (int)mapData[y].size(); x++) {
            int tileType = mapData[y][x];
            if (tileType == 0) continue;

            SDL_Rect src = {0,0,tileSize,tileSize};
            SDL_Rect dst = {x*tileSize - camera.x, y*tileSize - camera.y, tileSize, tileSize};

            if (tileType == 1) SDL_RenderCopy(renderer, tile1, &src, &dst);
            else if (tileType == 2) SDL_RenderCopy(renderer, tile2, &src, &dst);
            else if (tileType == 3) SDL_RenderCopy(renderer, tile3, &src, &dst);
        }
    }
}
