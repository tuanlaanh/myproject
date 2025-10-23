#include "map4.h"
#include <iostream>

Map4::Map4(SDL_Renderer* renderer) : Map1(renderer) {

    nen = IMG_LoadTexture(renderer, "nen.png");
    if (!nen) {
        std::cout << "Không load được nền map4: " << IMG_GetError() << std::endl;
    }

    // Dữ liệu bản đồ
    int level[15][40] = {
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,61,61,61,61,61,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2},
        {2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    };

    mapData.resize(15, std::vector<int>(40));
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 40; x++) {
            mapData[y][x] = level[y][x];
        }
    }

    // Load tile tuyết
    tile60 = IMG_LoadTexture(renderer, "assets/map/tuyet11.png");
    tile61 = IMG_LoadTexture(renderer, "assets/map/tuyet22.png");
    tile62 = IMG_LoadTexture(renderer, "assets/map/tuyet33.png");

    if (!tile60 || !tile61 || !tile62) {
        std::cout << "Lỗi load tile tuyết: " << IMG_GetError() << std::endl;
    }
}

Map4::~Map4() {
    if (tile60) SDL_DestroyTexture(tile60);
    if (tile61) SDL_DestroyTexture(tile61);
    if (tile62) SDL_DestroyTexture(tile62);
}

void Map4::render(SDL_Renderer* renderer, SDL_Rect camera) {
    // Vẽ nền
    SDL_RenderCopy(renderer, nen, NULL, NULL);

    for (int y = 0; y < (int)mapData.size(); y++) {
        for (int x = 0; x < (int)mapData[y].size(); x++) {
            int tileType = mapData[y][x];
            if (tileType == 0) continue;

            SDL_Rect src = {0, 0, tileSize, tileSize};
            SDL_Rect dst = {x * tileSize - camera.x, y * tileSize - camera.y, tileSize, tileSize};

            SDL_Texture* current = nullptr;

            // tile tuyết riêng
            if (tileType == 60) current = tile60;
            else if (tileType == 61) current = tile61;
            else if (tileType == 62) current = tile62;
            else {
                // tile thường kế thừa từ Map1
                switch (tileType) {
                    case 1: current = tile1; break;
                    case 2: current = tile2; break;
                    case 3: current = tile3; break;
                    case 4: current = tile4; break;
                    case 5: current = tile5; break;
                    case 6: current = tile6; break;

                    case 8: current = tile8; break;
                    case 9: current = tile9; break;
                    case 10: current = tile10; break;
                    default: current = nullptr; break;
                }
            }

            if (current)
                SDL_RenderCopy(renderer, current, &src, &dst);
        }
    }
}

void Map4::updateEnemy(float deltaTime, Player& player) {
    // Tạm thời trống
}

bool Map4::checkPrevMapTile(Player* player) {
    return false;
}
