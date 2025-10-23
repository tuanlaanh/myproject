
#include "map2.h"
#include <iostream>
#include "player.h"
#include "enemy.h"
#include "enemy2.h"
#include <algorithm>


int Map2::chieungang() const {
    return (int)mapData[0].size() * tileSize;
}
int Map2::chieudoc() const {
    return (int)mapData.size() * tileSize;
}


Map2::Map2(SDL_Renderer* renderer)
    : Map1(renderer),
      enemy1(renderer, 2000, 450, 6),
      enemy2(renderer, 3200, 530, 3),
       doi2(renderer, 3900, 200, 2 ) {
    if(nen) SDL_DestroyTexture(nen);
    nen = IMG_LoadTexture(renderer, "maprungram.png");
    if (!nen) {
        std::cout << IMG_GetError() << std::endl;
    }


    tile30 = IMG_LoadTexture(renderer, "assets/map/da.png");
    tile31 = IMG_LoadTexture(renderer, "assets/map/bay.png");
    tile32 = IMG_LoadTexture(renderer, "assets/map/bay2.png");
    tile33 = IMG_LoadTexture(renderer, "assets/map/dat1.png");
    tile34 = IMG_LoadTexture(renderer, "assets/map/dat2.png");
    tile35 = IMG_LoadTexture(renderer, "assets/map/datduoi.png");
    tile36 = IMG_LoadTexture(renderer, "assets/map/datduoitrai.png");
    tile37 = IMG_LoadTexture(renderer, "assets/map/datduoiphai.png");
    tile38 = IMG_LoadTexture(renderer, "assets/map/datgiua.png");
    tile39 = IMG_LoadTexture(renderer, "assets/map/thancay2.png");
    tile40 = IMG_LoadTexture(renderer, "assets/map/canh1.png");
    tile41 = IMG_LoadTexture(renderer, "assets/map/canhcut2.png");
    tile42 = IMG_LoadTexture(renderer, "assets/map/canh2.png");
    tile43 = IMG_LoadTexture(renderer, "assets/map/thancayla.png");
    tile44 = IMG_LoadTexture(renderer, "assets/map/thancayphai.png");
    tile45 = IMG_LoadTexture(renderer, "assets/map/thancaytrai.png");
    tile46 = IMG_LoadTexture(renderer, "assets/map/canhcut.png");
    tile47 = IMG_LoadTexture(renderer, "assets/map/hoa1.png");
    tile48 = IMG_LoadTexture(renderer, "assets/map/hoa2.png");
    if (!tile30) std::cout <<  IMG_GetError() << std::endl;





    int level[16][80] = {
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,38,38,38,38,38,38,38,38,38,38,38,8,0,0,0,0,0,0,0,0,0,29,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,38,38,38,38,38,38,38,38,38,38,38,8,0,0,0,0,0,23,21,21,21,24,0,0,0,0,0,23,21,21,21,21,24,0,0,0,0,0,23,21,24,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,38,38,38,38,38,38,38,38,38,38,38,8,0,0,0,0,23,17,17,17,17,17,24,0,0,0,0,19,17,17,17,17,15,0,0,0,0,0,19,17,20,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,38,38,38,38,35,35,35,38,38,38,38,8,0,0,0,0,19,17,17,17,17,17,20,0,0,0,0,18,17,17,17,15,0,0,0,0,0,0,18,16,15,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,35,35,35,37,0,0,0,36,35,35,35,37,0,0,0,0,18,17,17,17,17,17,15,0,0,0,0,0,18,16,15,0,26,0,0,0,0,41,40,39,42,46,0,0,0,0,0,0,0,0,0,0,4,1},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,32,32,0,0,0,0,0,32,32,32,0,0,0,0,0,0,18,17,17,17,15,0,0,0,0,0,0,0,44,40,40,40,46,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,0,0,0,3,2},
        {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,16,15,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,0,0,6,3,2},
        {8,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,41,40,45,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,0,0,4,9,2},
        {8,6,0,0,4,9,0,0,0,0,33,0,0,0,0,0,33,0,0,0,0,0,0,48,48,4,1,1,1,1,1,1,1,1,1,1,1,1,9,0,0,0,0,41,42,45,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,10,0,3,2,2},
        {1,1,1,1,2,8,0,0,0,0,34,0,0,0,0,0,34,0,0,0,0,0,4,1,1,9,2,2,2,2,2,2,2,2,2,2,2,2,8,30,0,48,48,0,0,44,42,40,46,0,0,0,0,0,0,44,40,46,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,30,31,11,48,3,2,2},
        {2,2,2,2,2,8,31,31,31,31,34,31,31,31,31,31,34,31,31,31,31,31,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,1,1,1,1,9,0,0,14,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,14,0,0,0,0,4,1,1,1,1,1,1,2,2,2},
        {2,2,2,2,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,0,0,14,0,0,0,0,0,0,41,40,42,45,0,0,0,0,0,0,0,0,0,14,0,0,0,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8,31,31,13,31,31,31,31,31,31,31,31,31,13,31,31,31,31,31,31,31,31,31,13,31,31,31,31,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    };

    mapData.clear();
    mapData.resize(16, std::vector<int>(80));
    for(int y=0;y<16;y++)
        for(int x=0;x<80;x++)
            mapData[y][x] = level[y][x];




 // Khởi tạo các biến animation hoa
    hoaFrame = false;
    hoaTimer = 0.0f;
    hoaFrameTime = 0.3f;

}


Map2::~Map2() {


    if (tile30) SDL_DestroyTexture(tile30);
    if (tile31) SDL_DestroyTexture(tile31);
    if (tile32) SDL_DestroyTexture(tile32);
    if (tile33) SDL_DestroyTexture(tile33);
    if (tile34) SDL_DestroyTexture(tile34);
    if (tile35) SDL_DestroyTexture(tile35);
    if (tile36) SDL_DestroyTexture(tile36);
    if (tile37) SDL_DestroyTexture(tile37);
    if (tile38) SDL_DestroyTexture(tile38);
    if (tile39) SDL_DestroyTexture(tile39);
    if (tile40) SDL_DestroyTexture(tile40);
    if (tile41) SDL_DestroyTexture(tile41);
    if (tile42) SDL_DestroyTexture(tile42);
    if (tile43) SDL_DestroyTexture(tile43);
    if (tile44) SDL_DestroyTexture(tile44);
    if (tile45) SDL_DestroyTexture(tile45);
    if (tile46) SDL_DestroyTexture(tile46);
    if (tile47) SDL_DestroyTexture(tile47);
     if (tile48) SDL_DestroyTexture(tile48);
}

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
                case 30: current=tile30; break;
                case 31: current=tile31; break;
                case 32: current=tile32; break;
                case 33: current=tile33; break;
                case 34: current=tile34; break;
                case 35: current=tile35; break;
                case 36: current=tile36; break;
                case 37: current=tile37; break;
                case 38: current=tile38; break;
                case 39: current=tile39; break;
                case 40: current=tile40; break;
                case 41: current=tile41; break;
                case 42: current=tile42; break;
                case 43: current=tile43; break;
                case 44: current=tile44; break;
                case 45: current=tile45; break;
                case 46: current=tile46; break;
                case 47:
                case 48: current=hoaFrame?tile48:tile47; break;  // <-- đây chèn animation hoa
                default: current=nullptr; break;
            }


            if(current) SDL_RenderCopy(renderer, current, &src, &dst);
        }
         }


         enemy1.render(renderer, camera);
         enemy2.render(renderer, camera);
         doi2.render(renderer, camera);

}
void Map2::updateEnemy(float deltaTime, Player& player) {
    enemy1.update(deltaTime);

    if (enemy1.checkCollision(player.getRect())) {
        // Dịch chuyển player về vị trí spawn ban đầu
        player.setPosition(player.getSpawnX(), player.getSpawnY());
        std::cout << "Va cham voi quai! Tra ve vi tri ban dau.\n";
    }



    enemy2.update(deltaTime);
     doi2.update(deltaTime);
     if (doi2.checkCollision(player.getRect())) {
        player.setPosition(player.getSpawnX(), player.getSpawnY());
        std::cout << "Va cham voi con doi! Tra ve vi tri ban dau.\n";
    }

    if (enemy2.checkCollision(player.getRect())) {
        player.setPosition(player.getSpawnX(), player.getSpawnY());
        std::cout << "Va cham voi con doi! Tra ve vi tri ban dau.\n";
    }


    hoaTimer += deltaTime;
    if(hoaTimer >= hoaFrameTime) {
        hoaTimer = 0.0f;
        hoaFrame = !hoaFrame; // chuyển frame
    }
}

bool Map2::checkNextMapTile(Player* player) {
    SDL_Rect playerRect = player->getRect();

    int tileX = playerRect.x / tileSize;
    int tileY = playerRect.y / tileSize;

    // Tile cửa chuyển map
    if (mapData[tileY][tileX] == 10) {
        return true;
    }
    return false;
}

