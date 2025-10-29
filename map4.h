#ifndef MAP4_H
#define MAP4_H
#include <SDL2/SDL_image.h>
#include "map1.h"
#include "boss.h"
#include <SDL_mixer.h>

class Map4 : public Map1 {
public:
    Map4(SDL_Renderer* renderer, Player* player);   //constructor
    ~Map4();                        // destructor
    void render(SDL_Renderer* renderer, SDL_Rect camera) override;
     void updateEnemy(float deltaTime, Player& player, SDL_Renderer* renderer);
    bool checkPrevMapTile(Player* player);

bool bossDead = false;



private:


Boss* boss;
    SDL_Texture* tile60;
    SDL_Texture* tile61;
    SDL_Texture* tile62;
    SDL_Texture* tile63;
    SDL_Texture* tile64;
    SDL_Texture* tile65;
    SDL_Texture* tile66;
    SDL_Texture* tile67;
    SDL_Texture* tile68;

    SDL_Texture* tile70;

};
extern Mix_Music* map4Music;
#endif
