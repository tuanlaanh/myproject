#ifndef MAP1_H
#define MAP1_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>






const int TILE_DEATH  = 7;


class Map1 {
public:
    Map1(SDL_Renderer* renderer);
    ~Map1();

    void render(SDL_Renderer* renderer, SDL_Rect camera);

    //  2 getter để Player truy cập
int getTileSize() const { return tileSize; }
const std::vector<std::vector<int>>& getMapData() const { return mapData; }



    int chieungang()const;   // thêm
    int chieudoc()const;



float treeTimer = 0.0f;  // thời gian tính frame cây
bool treeFrame = false;  // frame hiện tại (true = tile5, false = tile6)


void update(float deltaTime); // cập nhật animation

private:


    std::vector<std::vector<int>> mapData;   // ma trận map
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

    SDL_Texture* nen;
    int tileSize;        // kích thước 1 ô
};

#endif
