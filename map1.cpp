#include "map1.h"
#include <iostream>
#include "player.h"
#include <cmath>
#include <SDL_mixer.h>

int Map1::chieungang() const {
    return (int)mapData[0].size() * tileSize;
}

int Map1::chieudoc() const {
    return (int)mapData.size() * tileSize;
}

Map1::Map1(SDL_Renderer* renderer) {  // constructor
    nen = IMG_LoadTexture(renderer, "maprungram.png");
    if (!nen) {
        std::cout <<  IMG_GetError() << std::endl;
    }


Mix_Music* map1Music = Mix_LoadMUS("assets/music/nhacnen2.mp3");
if (!map1Music) {
    std::cout << "Không tải được nhạc map1: " << Mix_GetError() << std::endl;
} else {
    Mix_PlayMusic(map1Music, -1);
}

    int level[15][40] = {
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,21,24,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,17,17,17,24,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,23,21,21,21,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,17,17,17,20,0,0,7},
        {7,0,26,0,0,0,0,0,0,0,0,0,0,18,17,17,17,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,17,17,17,15,0,0,12},
        {7,0,23,21,24,0,0,0,0,0,0,0,0,0,18,16,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,16,15,0,0,0,4},
        {7,0,19,17,20,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,26,0,0,0,0,0,0,25,0,0,0,14,0,0,0,0,3},
        {9,0,18,16,15,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,4,1,1,9,0,0,0,0,0,4,9,0,0,14,0,0,10,0,3},
        {8,0,0,14,0,0,0,0,0,0,25,0,0,0,0,13,0,0,0,0,6,3,2,2,8,0,0,0,0,0,3,8,6,0,13,0,0,11,0,3},
        {8,0,0,14,0,0,0,0,0,4,1,1,1,1,1,1,1,1,1,1,1,2,2,2,8,0,0,0,0,0,3,4,1,1,1,1,1,1,1,2},
        {8,0,0,14,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {8,6,0,13,0,0,0,4,1,1,9,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,7,7,7,7,7,3,2,2,2,2,2,2,2,2,2},
    };

    mapData.resize(15, std::vector<int>(40));
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 40; x++) {
            mapData[y][x] = level[y][x];
        }

    }


    tile1 = IMG_LoadTexture(renderer, "assets/map/tile_0022.png");
    tile2 = IMG_LoadTexture(renderer, "assets/map/tile_0122.png");
    tile3 = IMG_LoadTexture(renderer, "assets/map/tile_0121.png");
    tile4 = IMG_LoadTexture(renderer, "assets/map/tile_0021.png");
    tile5 = IMG_LoadTexture(renderer, "assets/map/tile_0125.png");
    tile6 = IMG_LoadTexture(renderer, "assets/map/tile_0124.png");
    tile8 = IMG_LoadTexture(renderer, "assets/map/tile_0123.png");
    tile9 = IMG_LoadTexture(renderer, "assets/map/tile_0023.png");
    tile10 = IMG_LoadTexture(renderer, "assets/map/cua1.png");
    tile11 = IMG_LoadTexture(renderer, "assets/map/cua2.png");
    tile12 = IMG_LoadTexture(renderer, "assets/map/caythong.png");
    tile13 = IMG_LoadTexture(renderer, "assets/map/goccay.png");
    tile14 = IMG_LoadTexture(renderer, "assets/map/thancay.png");
    tile15 = IMG_LoadTexture(renderer, "assets/map/laphaiduoi.png");
    tile16 = IMG_LoadTexture(renderer, "assets/map/ngoncay.png");
    tile17 = IMG_LoadTexture(renderer, "assets/map/la0canh.png");
    tile18 = IMG_LoadTexture(renderer, "assets/map/latraiduoi.png");
    tile19 = IMG_LoadTexture(renderer, "assets/map/latrai.png");
    tile20 = IMG_LoadTexture(renderer, "assets/map/laphai.png");
    tile21 = IMG_LoadTexture(renderer, "assets/map/latren.png");
    tile22 = IMG_LoadTexture(renderer, "assets/map/laduoi.png");
    tile23 = IMG_LoadTexture(renderer, "assets/map/latraitren.png");
    tile24 = IMG_LoadTexture(renderer, "assets/map/laphaitren.png");
    tile25 = IMG_LoadTexture(renderer, "assets/map/muitenphai.png");
    tile26 = IMG_LoadTexture(renderer, "assets/map/chim1.png");
    tile27 = IMG_LoadTexture(renderer, "assets/map/chim2.png");
    tile28 = IMG_LoadTexture(renderer, "assets/map/chim3.png");
    tile29 = IMG_LoadTexture(renderer, "assets/map/chim4.png");

    if (!tile1 || !tile2 || !tile3 || !tile4||!tile5){   // test load
        std::cout << IMG_GetError()<< std::endl;
    }

    tileSize = 64;


    birdFrame = false;
    birdTimer = 0.0f;

    // Animation cây
    treeFrame = false;
    treeTimer = 0.0f;
}

Map1::~Map1() {   // giải phóng RAM
    if (tile1) SDL_DestroyTexture(tile1);
    if (tile2) SDL_DestroyTexture(tile2);
    if (tile3) SDL_DestroyTexture(tile3);
    if (tile4) SDL_DestroyTexture(tile4);
    if (tile5) SDL_DestroyTexture(tile5);
    if (tile6) SDL_DestroyTexture(tile6);
    if (tile8) SDL_DestroyTexture(tile8);
    if (tile9) SDL_DestroyTexture(tile9);
    if (tile10) SDL_DestroyTexture(tile10);
    if (tile11) SDL_DestroyTexture(tile11);
    if (tile12) SDL_DestroyTexture(tile12);
    if (tile13) SDL_DestroyTexture(tile13);
    if (tile14) SDL_DestroyTexture(tile14);
    if (tile15) SDL_DestroyTexture(tile15);
    if (tile16) SDL_DestroyTexture(tile16);
    if (tile17) SDL_DestroyTexture(tile17);
    if (tile18) SDL_DestroyTexture(tile18);
    if (tile19) SDL_DestroyTexture(tile19);
    if (tile20) SDL_DestroyTexture(tile20);
    if (tile21) SDL_DestroyTexture(tile21);
    if (tile22) SDL_DestroyTexture(tile22);
    if (tile23) SDL_DestroyTexture(tile23);
    if (tile24) SDL_DestroyTexture(tile24);
    if (tile25) SDL_DestroyTexture(tile25);
    if (tile26) SDL_DestroyTexture(tile26);
    if (tile27) SDL_DestroyTexture(tile27);
     if (tile28) SDL_DestroyTexture(tile28);
    if (tile29) SDL_DestroyTexture(tile29);
    if (nen) SDL_DestroyTexture(nen);
}

void Map1::render(SDL_Renderer* renderer, SDL_Rect camera) { // render map theo window
    SDL_RenderCopy(renderer, nen, NULL, NULL);

    for (int y = 0; y < (int)mapData.size(); y++) {
        for (int x = 0; x < (int)mapData[y].size(); x++) {
            int tileType = mapData[y][x];
            if (tileType == 0 || tileType == TILE_DEATH) continue;

            SDL_Rect src = {0, 0, tileSize, tileSize};
            SDL_Rect dst = {x * tileSize - camera.x, y * tileSize - camera.y, tileSize, tileSize};

            SDL_Texture* current = nullptr; // khai b chung

            if (tileType == 1) SDL_RenderCopy(renderer, tile1, &src, &dst);
            else if (tileType == 2) SDL_RenderCopy(renderer, tile2, &src, &dst);
            else if (tileType == 3) SDL_RenderCopy(renderer, tile3, &src, &dst);
            else if (tileType == 4) SDL_RenderCopy(renderer, tile4, &src, &dst);
            else if (tileType == 8) SDL_RenderCopy(renderer, tile8, &src, &dst);
            else if (tileType == 9) SDL_RenderCopy(renderer, tile9, &src, &dst);
            else if (tileType == 10) SDL_RenderCopy(renderer, tile10, &src, &dst);
            else if (tileType == 11) SDL_RenderCopy(renderer, tile11, &src, &dst);
            else if (tileType == 12) SDL_RenderCopy(renderer, tile12, &src, &dst);
            else if (tileType == 13) SDL_RenderCopy(renderer, tile13, &src, &dst);
            else if (tileType == 14) SDL_RenderCopy(renderer, tile14, &src, &dst);
            else if (tileType == 15) SDL_RenderCopy(renderer, tile15, &src, &dst);
            else if (tileType == 16) SDL_RenderCopy(renderer, tile16, &src, &dst);
            else if (tileType == 17) SDL_RenderCopy(renderer, tile17, &src, &dst);
            else if (tileType == 18) SDL_RenderCopy(renderer, tile18, &src, &dst);
            else if (tileType == 19) SDL_RenderCopy(renderer, tile19, &src, &dst);
            else if (tileType == 20) SDL_RenderCopy(renderer, tile20, &src, &dst);
            else if (tileType == 21) SDL_RenderCopy(renderer, tile21, &src, &dst);
        else if (tileType == 22) SDL_RenderCopy(renderer, tile22, &src, &dst);
        else if (tileType == 23) SDL_RenderCopy(renderer, tile23, &src, &dst);
        else if (tileType == 24) SDL_RenderCopy(renderer, tile24, &src, &dst);
        else if (tileType == 25) SDL_RenderCopy(renderer, tile25, &src, &dst);

            // animation cây
            else if (tileType == 5 || tileType == 6) {
                current = treeFrame ? tile5 : tile6;
                SDL_RenderCopy(renderer, current, &src, &dst);
            }

            // animation chim
            else if (tileType == 26 || tileType == 27 ) {
                current = birdFrame ? tile27 : tile26;
                SDL_RenderCopy(renderer, current, &src, &dst);
            }
            // animation chim 2
        else if (tileType == 28 || tileType == 29) {
              SDL_Texture* bird2Current = bird2Frame ? tile29 : tile28;
           SDL_RenderCopy(renderer, bird2Current, &src, &dst);
}
        }
    }
}



void Map1::update(float deltaTime, Player& player) {

    birdTimer += deltaTime;
    if (birdTimer >= 0.7f) {
        birdTimer = 0.0f;
        birdFrame = !birdFrame;
    }


    bird2Timer += deltaTime;
    if (bird2Timer >= 0.6f) {
        bird2Timer = 0.0f;
        bird2Frame = !bird2Frame;
    }


    treeTimer += deltaTime;
    if (treeTimer >= 0.4f) {
        treeTimer = 0.0f;
        treeFrame = !treeFrame;
    }

    if (checkNextMapTile(&player)) {
        printf("Player Chuyen \n");


    }
}


bool Map1::checkNextMapTile(Player* player){

     int tileSize = getTileSize();


    int playerX = player->getX();
    int playerY = player->getY();
    int playerW = player->getWidth();
    int playerH = player->getHeight();


    int tileX = (playerX + playerW / 2) / tileSize;
    int tileY = (playerY + playerH / 2) / tileSize;



    if (tileY < 0 || tileY >= chieudoc() || tileX < 0 || tileX >= chieungang())
        return false;
    int tileID = mapData[tileY][tileX];



    if (tileID == TILE_NEXTMAP) {



        return true;

    }


    return false;
}

