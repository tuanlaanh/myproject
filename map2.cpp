#include "map1.h"   // dùng chung Map1.h
#include <iostream>
#include "player.h"
#include <cmath>

class Map2 : public Map1 {
public:
    Map2(SDL_Renderer* renderer);
    ~Map2();
    int chieungang() const;
    int chieudoc() const;
    void render(SDL_Renderer* renderer, SDL_Rect camera);
};

int Map2::chieungang() const {
    return (int)mapData[0].size() * tileSize;
}

int Map2::chieudoc() const {
    return (int)mapData.size() * tileSize;
}

Map2::Map2(SDL_Renderer* renderer) : Map1(renderer) {
    // đổi nền map2
    if(nen) SDL_DestroyTexture(nen);
    nen = IMG_LoadTexture(renderer, "map2_background.png");
    if (!nen) {
        std::cout << "Lỗi load nền map2: " << IMG_GetError() << std::endl;
    }

    // mapData của map2
    int level[15][40] = {
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,21,24,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,17,17,17,24,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,23,21,21,21,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,17,17,17,20,0,0,7},
        {7,0,26,0,0,0,0,0,0,0,0,0,0,18,17,17,17,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,17,17,17,15,0,0,7},
        {7,0,23,21,24,0,0,0,0,0,0,0,0,0,18,16,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,16,15,0,0,0,4},
        {7,0,19,17,20,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,26,0,0,0,0,0,0,25,0,0,0,14,0,0,0,0,3},
        {9,0,18,16,15,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,4,1,1,9,0,0,0,0,0,4,9,0,0,14,0,0,10,0,3},
        {8,0,0,14,0,0,0,0,0,0,25,0,0,0,0,13,0,0,0,0,6,3,2,2,8,0,0,0,0,0,3,8,6,0,13,0,0,11,12,3},
        {8,0,0,14,0,0,0,0,0,4,1,1,1,1,1,1,1,1,1,1,1,2,2,2,8,0,0,0,0,0,3,4,1,1,1,1,1,1,1,2},
        {8,0,0,14,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {8,6,0,13,0,0,0,4,1,1,9,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,7,7,7,7,7,3,2,2,2,2,2,2,2,2,2}
    };

    mapData.resize(15, std::vector<int>(40));
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 40; x++)
            mapData[y][x] = level[y][x];

    // Không cần load lại tile nếu đã load trong Map1
    // tile1..tile29 và nen vẫn dùng chung
}

Map2::~Map2() {
    // Không destroy tile vì dùng chung
    if (nen) SDL_DestroyTexture(nen);
}

void Map2::render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_RenderCopy(renderer, nen, NULL, NULL);

    for (int y = 0; y < (int)mapData.size(); y++) {
        for (int x = 0; x < (int)mapData[y].size(); x++) {
            int tileType = mapData[y][x];
            if (tileType == 0 || tileType == TILE_DEATH) continue;

            SDL_Rect src = {0, 0, tileSize, tileSize};
            SDL_Rect dst = {x * tileSize - camera.x, y * tileSize - camera.y, tileSize, tileSize};

            SDL_Texture* current = nullptr;

            switch(tileType) {
                case 1: current = tile1; break;
                case 2: current = tile2; break;
                case 3: current = tile3; break;
                case 4: current = tile4; break;
                case 5:
                case 6: current = treeFrame ? tile5 : tile6; break;
                case 8: current = tile8; break;
                case 9: current = tile9; break;
                case 10: current = tile10; break;
                case 11: current = tile11; break;
                case 12: current = tile12; break;
                case 13: current = tile13; break;
                case 14: current = tile14; break;
                case 15: current = tile15; break;
                case 16: current = tile16; break;
                case 17: current = tile17; break;
                case 18: current = tile18; break;
                case 19: current = tile19; break;
                case 20: current = tile20; break;
                case 21: current = tile21; break;
                case 22: current = tile22; break;
                case 23: current = tile23; break;
                case 24: current = tile24; break;
                case 25: current = tile25; break;
                case 26:
                case 27: current = birdFrame ? tile27 : tile26; break;
                case 28:
                case 29: current = bird2Frame ? tile29 : tile28; break;
                default: current = nullptr; break;
            }

            if(current) SDL_RenderCopy(renderer, current, &src, &dst);
        }
    }
}

