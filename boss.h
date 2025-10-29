#ifndef BOSS_H
#define BOSS_H

#include <SDL.h>
#include "map1.h"

class Player;

class Boss {
public:
    Boss(SDL_Renderer* renderer, int spawnX, int spawnY);
    ~Boss();

    void update(float deltaTime, Player& player, Map1& map);
    void render(SDL_Renderer* renderer, SDL_Rect camera);

    void takeHit();
    void reset();

    SDL_Rect getRect() const { return rect; }
    bool isDead() const { return hp <= 0; }

private:
    SDL_Texture* textures[2];
    SDL_Rect rect;
    float posX, posY;
    float velX, velY;
    bool onGround;
    bool facingRight;

    int spawnX, spawnY;
    int hp;

    float jumpCooldown;
    float animTimer;
    int currentFrame;
};

#endif
