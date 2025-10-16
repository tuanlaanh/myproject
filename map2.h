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




};

#endif
