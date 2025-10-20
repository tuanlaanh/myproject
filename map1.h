#ifndef MAP1_H
#define MAP1_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "player.h"

class Player;

const int TILE_DEATH  = 7;
const int TILE_NEXTMAP = 11;
const int TILE_TRAP = 31;
const int TILE_TRAP2 = 32;

class Map1 {
public:
    Map1(SDL_Renderer* renderer);
    ~Map1();

   virtual  void render(SDL_Renderer* renderer, SDL_Rect camera);


    int getTileSize() const { return tileSize; }
    const std::vector<std::vector<int>>& getMapData() const { return mapData; }

    int chieungang() const;   // chiều ngang
    int chieudoc() const;     // chiều dọc

float birdTimer = 0.0f;   // thời gian tính frame chim đậu
    bool birdFrame = false;   // frame hiện tại chim đậu

     float bird2Timer = 0.0f;
    bool bird2Frame = false;

    float treeTimer = 0.0f;
    bool treeFrame = false;

    void update(float deltaTime, Player& player); //cập nhật animation

    // hàm kiểm tra tile để sang map2
    bool checkNextMapTile(Player* player);

protected:
    std::vector<std::vector<int>> mapData;   // ma trận map

    // Các texture tile
    SDL_Texture* tile1;
    SDL_Texture* tile2;
    SDL_Texture* tile3;
    SDL_Texture* tile4;
    SDL_Texture* tile5;
    SDL_Texture* tile6;
    SDL_Texture* tile8;
    SDL_Texture* tile9;
    SDL_Texture* tile10;
    SDL_Texture* tile11;
    SDL_Texture* tile12;
    SDL_Texture* tile13;
    SDL_Texture* tile14;
    SDL_Texture* tile15;
    SDL_Texture* tile16;
    SDL_Texture* tile17;
    SDL_Texture* tile18;
    SDL_Texture* tile19;
    SDL_Texture* tile20;
    SDL_Texture* tile21;
    SDL_Texture* tile22;
    SDL_Texture* tile23;
    SDL_Texture* tile24;
    SDL_Texture* tile25;
    SDL_Texture* tile26;
    SDL_Texture* tile27;
    SDL_Texture* tile28;
    SDL_Texture* tile29;

    SDL_Texture* nen;
    int tileSize;
};



#endif
