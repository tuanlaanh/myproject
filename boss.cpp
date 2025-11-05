#include "boss.h"
#include "player.h"
#include <SDL2/SDL_image.h>
#include <iostream>

const float BOSS_MOVE_SPEED = 600.0f;
const float BOSS_JUMP_FORCE = -900.0f;
const float BOSS_GRAVITY    = 3000.0f;

Boss::Boss(SDL_Renderer* renderer, int sx, int sy)
    : posX((float)sx), posY((float)sy),
      velX(BOSS_MOVE_SPEED), velY(0),
      onGround(false), facingRight(true),
      spawnX(sx), spawnY(sy), hp(10),
      jumpCooldown(0.0f), animTimer(0.0f), currentFrame(0)
{
    textures[0] = IMG_LoadTexture(renderer, "assets/char/boss1.png");
    textures[1] = IMG_LoadTexture(renderer, "assets/char/boss2.png");
    if (!textures[0] || !textures[1]) std::cout << IMG_GetError() << std::endl;

    rect.w = 99;
    rect.h = 99;
    rect.x = sx;
    rect.y = sy;
}

Boss::~Boss() {
    for (int i=0; i<2; i++)
        if (textures[i]) SDL_DestroyTexture(textures[i]);
}
void Boss::takeHit() {
    if (hp <= 0) return;
    hp--;
    velY = BOSS_JUMP_FORCE * 1.4f;
    onGround = false;
    jumpCooldown = 0.7f;
    std::cout << "Bosshit=" << hp << std::endl;
    if (hp <= 0) {
        velX = 0;
        velY = 0;
        std::cout << "Bossdied\n";
    }
}

void Boss::reset() {
    posX = (float)spawnX;
    posY = (float)spawnY;
    velX = BOSS_MOVE_SPEED;
    velY = 0;
    hp = 10;
    onGround = false;
    facingRight = true;
    jumpCooldown = 0.0f;
    animTimer = 0.0f;
    currentFrame = 0;
    rect.x = spawnX;
    rect.y = spawnY;
}

void Boss::update(float deltaTime, Player& player, Map1& map) {
    if (hp <= 0) return;

    animTimer += deltaTime;
    if (animTimer >= 0.2f) {
        currentFrame =(currentFrame + 1) % 2;
        animTimer = 0.0f;
    }


    velY += BOSS_GRAVITY * deltaTime;
    posY += velY * deltaTime;

    int tileSize = map.getTileSize();
    const auto& data = map.getMapData();


    int footX1 = (int)posX / tileSize;
    int footX2 = (int)(posX + rect.w - 1) / tileSize;
    int footY  = (int)(posY + rect.h) / tileSize;

    bool groundHere = false;
    if (footY >=0 && footY < (int)data.size()) {
        for (int tx = footX1; tx <= footX2; ++tx) {
            if (tx<0 || tx>=(int)data[footY].size()) continue;
            int t = data[footY][tx];
            if (t!=0 && t!=5 && t!=6 && (t<10 || t>27) && t!=30 && t!=41 && t!=43 && t!=44 && t!=45 && t!=48 && t!=56 && t!=63 && t!=64 && t!=65 && t!=66  && t!=67 && t!=70) {
                groundHere = true; break;
            }
        }
    }

    if (groundHere && velY >=0) {
        posY = (float)(footY * tileSize - rect.h);
        velY = 0;
        if (!onGround && jumpCooldown <=0.0f) {
            velY = BOSS_JUMP_FORCE;
            onGround = false;
            jumpCooldown = 0.8f;
        }
        onGround = true;
    } else {
        onGround = false;
    }

    if (jumpCooldown >0.0f) jumpCooldown -= deltaTime;


    posX += velX * deltaTime;
    int leftTile   = (int)posX / tileSize;
    int rightTile  = (int)(posX + rect.w -1) / tileSize;
    int topTile    = (int)posY / tileSize;
    int bottomTile = (int)(posY + rect.h -1) / tileSize;

    for (int y=topTile; y<=bottomTile && y<(int)data.size(); y++) {
        for (int x=leftTile; x<=rightTile && x<(int)data[y].size(); x++) {
            if (x<0) continue;
            int t = data[y][x];
            if (t!=0 && t!=5 && t!=6 && (t<10 || t>27) && t!=30 && t!=41 && t!=43 && t!=44 && t!=45 && t!=48 && t!=56 && t!=63 && t!=64 && t!=65 && t!=66&& t!=67&& t!=70) {
                SDL_Rect tileRect = { x*tileSize, y*tileSize, tileSize, tileSize };
                SDL_Rect bossRect = { (int)posX, (int)posY, rect.w, rect.h };
                if (SDL_HasIntersection(&tileRect, &bossRect)) {
                    if (velX >0) { posX = tileRect.x - rect.w; velX = -BOSS_MOVE_SPEED; facingRight=false; }
                    else if (velX <0){ posX = tileRect.x + tileSize; velX = BOSS_MOVE_SPEED; facingRight=true; }
                }
            }
        }
    }

    rect.x = (int)posX;
    rect.y = (int)posY;
}

void Boss::render(SDL_Renderer* renderer, SDL_Rect camera) {
    if (hp <=0) return;
    SDL_Rect dst = { rect.x - camera.x, rect.y - camera.y, rect.w, rect.h };
    SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, textures[currentFrame], nullptr, &dst, 0.0, nullptr, flip);

    int barW = rect.w;
    SDL_Rect bg = { dst.x, dst.y - 10, barW, 10 };
    SDL_Rect fg = { dst.x, dst.y - 10, (int)(barW * (hp/10.0f)), 10 };
    SDL_SetRenderDrawColor(renderer, 40,40,40,255);
    SDL_RenderFillRect(renderer, &bg);
    SDL_SetRenderDrawColor(renderer, 200,30,30,255);
    SDL_RenderFillRect(renderer, &fg);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}
