#pragma once
#include <SDL.h>
#include <SDL2/SDL_image.h>

class Enemy {
public:

    Enemy(SDL_Renderer* renderer, int x, int y, int rangeTiles);
    ~Enemy();

    Enemy(SDL_Renderer* renderer, int x, int y, int rangeTiles,
          const char* img1, const char* img2);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, SDL_Rect camera);
    bool checkCollision(const SDL_Rect& playerRect);

    SDL_Rect getRect() const { return dstRect; }

    void setSpeed(float s) { speed = s; }
    float getSpeed() const { return speed; }

private:
    SDL_Texture* texture1;
    SDL_Texture* texture2;
    SDL_Texture* currentTexture;

    SDL_Rect dstRect;

    int startX;
    int moveRange;
    float speed;
    int direction;
    float animTimer;
};
