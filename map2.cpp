#include "map1.h"
#include <iostream>
#include "player.h"
#include <algorithm>

class Map2 : public Map1{
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
    if(nen) SDL_DestroyTexture(nen);
    nen = IMG_LoadTexture(renderer, "chuacogi.png");
    if (!nen) {
        std::cout << IMG_GetError() << std::endl;
    }


    int level[16][80] = {
       {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2},
        {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,9,2},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,2},
        {1,1,1,1,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,2},
        {2,2,2,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    };

    mapData.clear();
    mapData.resize(16, std::vector<int>(80));
    for(int y=0;y<16;y++)
        for(int x=0;x<80;x++)
            mapData[y][x] = level[y][x];
}


Map2::~Map2() {}

void Map2::render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_RenderCopy(renderer, nen, NULL, NULL);

    int startX = camera.x / tileSize;
    int endX   = (camera.x + camera.w) / tileSize + 1;
    int startY = camera.y / tileSize;
    int endY   = (camera.y + camera.h) / tileSize + 1;

    startX = std::max(0, startX);
    endX   = std::min((int)mapData[0].size(), endX);
    startY = std::max(0, startY);
    endY   = std::min((int)mapData.size(), endY);

    for(int y=startY;y<endY;y++){
        for(int x=startX;x<endX;x++){
            int tileType = mapData[y][x];
            if(tileType==0 || tileType==TILE_DEATH) continue;

            SDL_Rect src={0,0,tileSize,tileSize};
            SDL_Rect dst={x*tileSize - camera.x, y*tileSize - camera.y, tileSize, tileSize};
            SDL_Texture* current = nullptr;

            switch(tileType){
                case 1: current=tile1; break;
                case 2: current=tile2; break;
                case 3: current=tile3; break;
                case 4: current=tile4; break;
                case 5:
                case 6: current=treeFrame?tile5:tile6; break;
                case 8: current=tile8; break;
                case 9: current=tile9; break;
                case 10: current=tile10; break;
                case 11: current=tile11; break;
                case 12: current=tile12; break;
                case 13: current=tile13; break;
                case 14: current=tile14; break;
                case 15: current=tile15; break;
                case 16: current=tile16; break;
                case 17: current=tile17; break;
                case 18: current=tile18; break;
                case 19: current=tile19; break;
                case 20: current=tile20; break;
                case 21: current=tile21; break;
                case 22: current=tile22; break;
                case 23: current=tile23; break;
                case 24: current=tile24; break;
                case 25: current=tile25; break;
                case 26:
                case 27: current=birdFrame?tile27:tile26; break;
                case 28:
                case 29: current=bird2Frame?tile29:tile28; break;
                default: current=nullptr; break;
            }


            if(current) SDL_RenderCopy(renderer, current, &src, &dst);
        }
         }
}
