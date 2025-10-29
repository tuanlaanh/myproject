#ifndef MAP2_H
#define MAP2_H

#include "map1.h"
#include "enemy.h"
#include "enemy2.h"
#include <SDL_mixer.h>

class Map2 : public Map1 {
public:

// Animation hoa
bool hoaFrame;      // hiện frame nào
float hoaTimer;      // bộ đếm thời gian
float hoaFrameTime;  // thời gian mỗi frame

bool checkNextMapTile(Player* player);


Enemy enemy1;
    void render(SDL_Renderer* renderer, SDL_Rect camera) override;

    void updateEnemy(float deltaTime, Player& player); // thêm hàm cập nhật quái riêng map2



    Map2(SDL_Renderer* renderer);
    ~Map2();


    int chieungang() const;
    int chieudoc() const;

    Enemy2 enemy2;
     Enemy2 doi2;



private:



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

Mix_Music* map2Music;


};

#endif
