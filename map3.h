#ifndef MAP3_H
#define MAP3_H

#include "map1.h"
#include "enemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include <vector>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_mixer.h>

class Map3 : public Map1 {
public:

    Map3();
    Map3(SDL_Renderer* renderer);
    ~Map3();



    void render(SDL_Renderer* renderer, SDL_Rect camera);
    void updateEnemy(float deltaTime, Player& player);
    bool checkPrevMapTile(Player* player);

    int chieungang() const;
    int chieudoc() const;



private:

    Enemy enemy1;
    Enemy2 enemy2;
    Enemy2 doi2;
    Enemy3 enemy3;

    SDL_Texture* tile30;
    SDL_Texture* tile31;
    SDL_Texture* tile32;
    SDL_Texture* tile33;
    SDL_Texture* tile34;
    SDL_Texture* tile35;
    SDL_Texture* tile36;
    SDL_Texture* tile37;
    SDL_Texture* tile38;
    SDL_Texture* tile39;
    SDL_Texture* tile40;
    SDL_Texture* tile41;
    SDL_Texture* tile42;
    SDL_Texture* tile43;
    SDL_Texture* tile44;
    SDL_Texture* tile45;
    SDL_Texture* tile46;
    SDL_Texture* tile47;
    SDL_Texture* tile48;
    SDL_Texture* tile49;

     SDL_Texture* tile50;
     SDL_Texture* tile51;
     SDL_Texture* tile52;
      SDL_Texture* tile53;
       SDL_Texture* tile54;
        SDL_Texture* tile55;
         SDL_Texture* tile56;
          SDL_Texture* tile57;
    Mix_Music* map3Music = nullptr;



    bool hoaFrame;
    float hoaTimer;
    float hoaFrameTime;
};

#endif
