#include "enemy.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <iostream>

bool Enemy::checkCollision(const SDL_Rect& rect)
{
    return SDL_HasIntersection(&dstRect, &rect);
}

// Constructor
Enemy::Enemy(SDL_Renderer* renderer, int x, int y, int rangeTiles)
{
    texture1 = IMG_LoadTexture(renderer, "assets/char/quai1.png");
    texture2 = IMG_LoadTexture(renderer, "assets/char/quai2.png");

    if (!texture1 || !texture2) {
        SDL_Log("Không thể load ảnh quái: %s", IMG_GetError());
    }

    currentTexture = texture1;
    dstRect = { x, y, 64, 64 };
    startX = x;
    moveRange = rangeTiles * 64;
    speed = 100.0f;
    direction = 1;
    animTimer = 0.0f;
}

// Constructor mới cho Enemy3
Enemy::Enemy(SDL_Renderer* renderer, int x, int y, int rangeTiles,
             const char* img1, const char* img2)
{
    texture1 = IMG_LoadTexture(renderer, img1);
    texture2 = IMG_LoadTexture(renderer, img2);

    if (!texture1 || !texture2) {
        SDL_Log("Không thể load ảnh quái: %s", IMG_GetError());
    }

    currentTexture = texture1;
    dstRect = { x, y, 64, 64 };
    startX = x;
    moveRange = rangeTiles * 64;
    speed = 100.0f;
    direction = 1;
    animTimer = 0.0f;
}

Enemy::~Enemy()
{
    if (texture1) SDL_DestroyTexture(texture1);
    if (texture2) SDL_DestroyTexture(texture2);
}

void Enemy::update(float deltaTime)
{
    dstRect.x += static_cast<int>(speed * direction * deltaTime);

    if (dstRect.x > startX + moveRange)
        direction = -1;
    else if (dstRect.x < startX - moveRange)
        direction = 1;

    animTimer += deltaTime;
    if (animTimer >= 0.3f) {
        animTimer = 0;
        currentTexture = (currentTexture == texture1) ? texture2 : texture1;
    }
}

void Enemy::render(SDL_Renderer* renderer, SDL_Rect camera)
{
    SDL_Rect renderRect = {
        dstRect.x - camera.x,
        dstRect.y - camera.y,
        dstRect.w,
        dstRect.h
    };

    SDL_RenderCopy(renderer, currentTexture, nullptr, &renderRect);
}
