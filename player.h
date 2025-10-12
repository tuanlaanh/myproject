#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <string>
#include "map1.h"



class Map1; // Khai báo sớm để compiler biết Map1 là một class

class Player {
public:
    Player(SDL_Renderer* renderer, float x, float y);
    ~Player();

    void handleEvent(const SDL_Event& e);
    void update(float deltaTime, Map1& map);
    void render(SDL_Renderer* renderer, SDL_Rect camera);
    void setPosition(int x, int y);//moi


    int getX() const { return (int)posX; }
    int getY() const { return (int)posY; }
    SDL_Rect getDstRect() const { return dstRect; }


    float animTimer;
    int currentState;      // 0 = đứng, 1 = chạy, 2 = nhảy
    int currentFrame;      // 0 hoặc 1, để đổi frame chạy


    int getWidth() const { return dstRect.w; }
    int getHeight() const { return dstRect.h; }

private:
    float posX, posY;
    float velX, velY;
    bool onGround;
    int jumpCount;
    const int MAX_JUMP = 2;

    float spawnX, spawnY; // tọa độ spawn
     void die(); // chết


    SDL_Texture* textureIdle;   // texture đứng / frame 1
    SDL_Texture* textureJump;   // texture nhảy / frame 2
    SDL_Rect srcRect;           // source rectangle
    SDL_Rect dstRect;           // destination rectangle


    bool leftPressed;           // phím trái
    bool rightPressed;          // phím phải
    bool movingX;               // đang chạy ngang
};

#endif
