#include "enemy2.h"
#include <SDL2/SDL_image.h>
#include <iostream>

bool Enemy2::checkCollision(const SDL_Rect& rect)
{
    return SDL_HasIntersection(&dstRect, &rect);
}

Enemy2::Enemy2(SDL_Renderer* renderer, int x, int y, int rangeTiles)
{
    // Nạp đủ 3 ảnh dơi
    texture1 = IMG_LoadTexture(renderer, "assets/char/doi1.png");
    texture2 = IMG_LoadTexture(renderer, "assets/char/doi2.png");
    texture3 = IMG_LoadTexture(renderer, "assets/char/doi3.png");

    if (!texture1 || !texture2 || !texture3) {
        std::cout << "Không thể load đủ ảnh dơi: " << IMG_GetError() << std::endl;
    }

    currentTexture = texture1;
    dstRect = { x, y, 64, 64 };

    startY = y;
    moveRange = rangeTiles * 64;
    speed = 350.0f;
    direction = 1;
    animTimer = 0.0f;
    frameIndex = 0; // bắt đầu từ frame đầu
}

Enemy2::~Enemy2()
{
    if (texture1) SDL_DestroyTexture(texture1);
    if (texture2) SDL_DestroyTexture(texture2);
    if (texture3) SDL_DestroyTexture(texture3);
}

void Enemy2::update(float deltaTime)
{
    // --- Di chuyển lên xuống ---
    dstRect.y -= static_cast<int>(speed * direction * deltaTime);

    if (dstRect.y < startY - moveRange)
        direction = -1;
    else if (dstRect.y > startY + moveRange)
        direction = 1;

    // --- Animation ---
    animTimer += deltaTime;
    if (animTimer >= 0.1f) {
        animTimer = 0;
        frameIndex = (frameIndex + 1) % 3;

        if (frameIndex == 0)
            currentTexture = texture1;
        else if (frameIndex == 1)
            currentTexture = texture2;
        else
            currentTexture = texture3;
    }
}

void Enemy2::render(SDL_Renderer* renderer, SDL_Rect camera)
{
    SDL_Rect renderRect = {
        dstRect.x - camera.x,
        dstRect.y - camera.y,
        dstRect.w,
        dstRect.h
    };
    SDL_RenderCopy(renderer, currentTexture, nullptr, &renderRect);
}
