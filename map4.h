#ifndef MAP4_H
#define MAP4_H
#include <SDL2/SDL_image.h>
#include "map1.h"

class Map4 : public Map1 {
public:
    Map4(SDL_Renderer* renderer);   // constructor
    ~Map4();                        // destructor
    void render(SDL_Renderer* renderer, SDL_Rect camera) override; // render lại nếu muốn khác
     void updateEnemy(float deltaTime, Player& player); // 👉 thêm để tránh lỗi
    bool checkPrevMapTile(Player* player);




private:


    SDL_Texture* tile60;
    SDL_Texture* tile61;
    SDL_Texture* tile62;
};

#endif
