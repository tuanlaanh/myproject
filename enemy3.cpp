#include "enemy3.h"

Enemy3::Enemy3(SDL_Renderer* renderer, int x, int y, int rangeTiles)
    : Enemy(renderer, x, y, rangeTiles,
            "assets/char/quai3.png",
            "assets/char/quai4.png")
{
     setSpeed(200.0f);
}
