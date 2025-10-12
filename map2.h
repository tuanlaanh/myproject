#ifndef MAP2_H
#define MAP2_H

#include "map1.h"   //Kế thừa từ Map1

class Map2 : public Map1 {
public:
    Map2(SDL_Renderer* renderer);
    ~Map2();

    //các hàm riêng của map2
    int chieungang() const;
    int chieudoc() const;
    void render(SDL_Renderer* renderer, SDL_Rect camera);
};

#endif
