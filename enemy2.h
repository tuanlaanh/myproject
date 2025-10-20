#ifndef ENEMY2_H
#define ENEMY2_H

#include <SDL.h>

class Enemy2 {
public:
    Enemy2(SDL_Renderer* renderer, int x, int y, int rangeTiles);
    ~Enemy2();

    void update(float deltaTime);
    void render(SDL_Renderer* renderer, SDL_Rect camera);
    bool checkCollision(const SDL_Rect& rect);

private:
    SDL_Texture* texture1;
    SDL_Texture* texture2;
    SDL_Texture* texture3;
    SDL_Texture* currentTexture;
    SDL_Rect dstRect;
     SDL_Renderer* renderer; // lưu renderer lại
    float speed;
    int direction;
    int startY;
    int moveRange;
    float animTimer;
     int frameIndex;
};

#endif

