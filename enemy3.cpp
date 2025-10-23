#include "enemy3.h"

Enemy3::Enemy3(SDL_Renderer* renderer, int x, int y, int rangeTiles)
    : Enemy(renderer, x, y, rangeTiles,
            "assets/char/quai3.png",  // ảnh 1 của Enemy3
            "assets/char/quai4.png")  // ảnh 2 của Enemy3
{
     setSpeed(200.0f); // chỉ thay đổi Enemy3
}
