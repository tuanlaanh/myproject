#ifndef ENEMY3_H
#define ENEMY3_H

#include "enemy.h"

class Enemy3 : public Enemy {
public:
    Enemy3(SDL_Renderer* renderer, int x, int y, int rangeTiles);
    ~Enemy3() = default;
};

#endif
