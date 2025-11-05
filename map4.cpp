#include "map4.h"
#include <iostream>
#include <SDL_mixer.h>

Map4::Map4(SDL_Renderer* renderer, Player* player) : Map1(renderer) {
    dieSound = Mix_LoadWAV("assets/sound/die.wav");
if (!dieSound) {
    std::cout << "Khong tai duoc die.wav: " << Mix_GetError() << std::endl;
}
bogSound = Mix_LoadWAV("assets/sound/bog.mp3");
endMusic = Mix_LoadMUS("assets/sound/endgame.mp3");
if (!endMusic) {
    std::cout << "Khong tai duoc endgame.mp3: " << Mix_GetError() << std::endl;
}
    nen = IMG_LoadTexture(renderer, "nen.png");
    if (!nen) {
        std::cout << IMG_GetError() << std::endl;
    }




    int level[15][40] = {
        {8,0,0,0,0,0,0,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,0,0,0,0,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,0,0,0,0,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,0,0,0,0,0,0,0,0,65,0,0,0,65,0,0,0,65,0,0,0,65,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,0,0,0,0,0,0,0,0,66,0,0,0,66,0,0,0,66,0,0,0,66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,0,0,0,0,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,0,0,0,0,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,0,0,0,0,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {8,0,0,67,0,0,63,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,63,67,0,0,0,0,2},
        {2,61,61,61,61,61,62,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,60,61,61,61,61,61,61,61,61,2},
        {2,2,2,2,2,2,8,0,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,3,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,8,0,0,67,0,65,0,0,0,65,0,0,0,65,0,0,0,65,0,67,0,0,70,0,3,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    };

    mapData.resize(15, std::vector<int>(40));
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 40; x++) {
            mapData[y][x] = level[y][x];
        }
    }


    tile60 = IMG_LoadTexture(renderer, "assets/map/tuyet11.png");
    tile61 = IMG_LoadTexture(renderer, "assets/map/tuyet22.png");
    tile62 = IMG_LoadTexture(renderer, "assets/map/tuyet33.png");
    tile63 = IMG_LoadTexture(renderer, "assets/map/nguoituyet.png");
    tile64 = IMG_LoadTexture(renderer, "assets/map/day.png");
    tile65 = IMG_LoadTexture(renderer, "assets/map/dayduoi.png");
    tile66 = IMG_LoadTexture(renderer, "assets/map/daytren.png");
    tile67 = IMG_LoadTexture(renderer, "assets/map/cotrang.png");
    tile68 = IMG_LoadTexture(renderer, "assets/map/tuyet33.png");
    tile70 = IMG_LoadTexture(renderer, "assets/map/diabay.png");
if (!tile70) std::cout << "Lỗi load tile70: " << IMG_GetError() << std::endl;

    if (!tile60 || !tile61 || !tile62) {
        std::cout  << IMG_GetError() << std::endl;
    }



    boss = new Boss(renderer, 800, 360);
}

Map4::~Map4() {

    delete boss;
    if (tile60) SDL_DestroyTexture(tile60);
    if (tile61) SDL_DestroyTexture(tile61);
    if (tile62) SDL_DestroyTexture(tile62);
    if (tile63) SDL_DestroyTexture(tile63);
    if (tile64) SDL_DestroyTexture(tile64);
    if (tile65) SDL_DestroyTexture(tile65);
    if (tile66) SDL_DestroyTexture(tile66);
    if (tile67) SDL_DestroyTexture(tile67);
    if (tile68) SDL_DestroyTexture(tile68);
     if (tile68) SDL_DestroyTexture(tile70);

}

void Map4::render(SDL_Renderer* renderer, SDL_Rect camera) {

    SDL_RenderCopy(renderer, nen, NULL, NULL);

    for (int y = 0; y < (int)mapData.size(); y++) {
        for (int x = 0; x < (int)mapData[y].size(); x++) {
            int tileType = mapData[y][x];
            if (tileType == 0) continue;

            SDL_Rect src = {0, 0, tileSize, tileSize};
            SDL_Rect dst = {x * tileSize - camera.x, y * tileSize - camera.y, tileSize, tileSize};

            SDL_Texture* current = nullptr;


            if (tileType == 60) current = tile60;
            else if (tileType == 61) current = tile61;
            else if (tileType == 62) current = tile62;
            else if (tileType == 63) current = tile63;
            else if (tileType == 64) current = tile64;
            else if (tileType == 65) current = tile65;
            else if (tileType == 66) current = tile66;
            else if (tileType == 67) current = tile67;
            else if (tileType == 68) current = tile68;
            else if (tileType == 70) current = tile70;
            else {

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

    if (boss)
        boss->render(renderer, camera);

}


bool Map4::checkPrevMapTile(Player* player) {

    return false;
}


void Map4::updateEnemy(float deltaTime, Player& player, SDL_Renderer* renderer) {

    if (boss) {
        boss->update(deltaTime, player, *this);

        SDL_Rect playerRect = player.getRect();
        SDL_Rect bossRect   = boss->getRect();

        float playerNextY = playerRect.y + player.getVelY() * deltaTime;
        float playerBottom = playerNextY + playerRect.h;
        float bossTop = bossRect.y;
        if (SDL_HasIntersection(&playerRect, &bossRect)) {
            if (player.getVelY() > 0 && (playerBottom - bossTop) <= 40 && !player.isInvincible()) {
                boss->takeHit();
                player.bounce();
                player.setPosition(playerRect.x, bossTop - playerRect.h);
                player.setInvincible(0.2f);
                 if (bogSound) {
            Mix_PlayChannel(-1, bogSound, 0);
        }
            } else if (!player.isInvincible()) {
                player.resetToSpawn();
                boss->reset();
                player.setInvincible(0.2f);
                if (dieSound) {
                Mix_PlayChannel(-1, dieSound, 0);
                }
            }
        }

        player.updateInvincible(deltaTime);


       if (boss && boss->isDead()) {
    delete boss;
    boss = nullptr;
    bossDead = true;

    if (map4Music && Mix_PlayingMusic()) {
        Mix_HaltMusic();
        Mix_FreeMusic(map4Music);
        map4Music = nullptr;
    }
}
    }
    else {
        bossDead = true;
    }


    SDL_Rect rect = player.getRect();
    int tileX = (rect.x + rect.w / 2) / tileSize;
    int tileY = (rect.y + rect.h / 2) / tileSize;

    if (tileY >= 0 && tileY < (int)mapData.size() &&
        tileX >= 0 && tileX < (int)mapData[tileY].size()) {

        if (mapData[tileY][tileX] == 70) {
            if (bossDead) {
                    if (endMusic) {
                    Mix_PlayMusic(endMusic, 1);
                    }
                SDL_Texture* endTex = IMG_LoadTexture(renderer, "assets/map/credis.png");
                if (endTex) {
                    SDL_RenderClear(renderer);
                    SDL_Rect full = {0, 0, 1280, 720};
                    SDL_RenderCopy(renderer, endTex, NULL, &full);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(3000);
                    SDL_DestroyTexture(endTex);
                } else {
                    std::cout << IMG_GetError() << std::endl;
                }

                SDL_Quit();
                exit(0);
            } else {
                std::cout << "Boss chưa chết" << std::endl;
            }
        }
    }
}
