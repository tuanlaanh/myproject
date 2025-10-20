#include "enemy.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>

bool Enemy::checkCollision(const SDL_Rect& rect)
{
    // rect là khung hình của player
    return SDL_HasIntersection(&dstRect, &rect);
}

Enemy::Enemy(SDL_Renderer* renderer, int x, int y, int rangeTiles)
{
    // Nạp hai ảnh quái
    texture1 = IMG_LoadTexture(renderer, "assets/char/quai1.png");
    texture2 = IMG_LoadTexture(renderer, "assets/char/quai2.png");

    // Nếu lỗi nạp ảnh
    if (!texture1 || !texture2) {
        SDL_Log("Không thể load ảnh quái: %s", IMG_GetError());
    }

    currentTexture = texture1;

    dstRect = { x, y, 64, 64 }; // kích thước 1 tile (32x32)
    startX = x;
    moveRange = rangeTiles * 64; // ví dụ: 6 tile = 192 pixel
    speed = 100.0f;               // tốc độ di chuyển
    direction = 1;               // 1 = phải, -1 = trái
    animTimer = 0.0f;            // reset bộ đếm animation
}

Enemy::~Enemy()
{
    if (texture1) SDL_DestroyTexture(texture1);
    if (texture2) SDL_DestroyTexture(texture2);
}

void Enemy::update(float deltaTime)
{
    // Di chuyển qua lại trong phạm vi
    dstRect.x += static_cast<int>(speed * direction * deltaTime);

    if (dstRect.x > startX + moveRange)
        direction = -1;
    else if (dstRect.x < startX - moveRange)
        direction = 1;

    // Đổi ảnh qua lại để tạo animation
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
