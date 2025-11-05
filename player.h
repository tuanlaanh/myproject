#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

class Map1;

class Player {
public:
    Player(SDL_Renderer* renderer, float x, float y);
    ~Player();
Mix_Chunk* jumpSound;
    void handleEvent(const SDL_Event& e);
    void update(float deltaTime, Map1& map);
    void render(SDL_Renderer* renderer, SDL_Rect camera);
    void setPosition(int x, int y);

    float getVelY() const;
    void bounce();
    void resetToSpawn();

    SDL_Rect getRect() const { return dstRect; }
    int getX() const { return (int)posX; }
    int getY() const { return (int)posY; }
    int getWidth() const { return dstRect.w; }
    int getHeight() const { return dstRect.h; }
    int getSpawnX() const { return (int)spawnX; }
    int getSpawnY() const { return (int)spawnY; }

    bool isAlive() const { return alive; }
    void setAlive(bool a) { alive = a; }

    bool isInvincible() const { return invincibleTime > 0.0f; }
    void setInvincible(float t) { invincibleTime = t; }
    void updateInvincible(float deltaTime) {
        if (invincibleTime > 0.0f) invincibleTime -= deltaTime;
        if (invincibleTime < 0.0f) invincibleTime = 0.0f;
    }

    float animTimer;
    int currentState;
    int currentFrame;
    float animSpeed = 0.2f;
    Mix_Chunk* soundNext;
    Mix_Chunk* soundDie;
private:
    void die();

    bool alive = true;
    float posX, posY;
    float velX, velY;
    bool onGround;
    int jumpCount;
    const int MAX_JUMP = 2;

    float spawnX, spawnY;

    SDL_Texture* textureIdle;
    SDL_Texture* textureJump;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    float invincibleTime = 0.0f;

    bool leftPressed;
    bool rightPressed;
    bool movingX;
    bool facingRight;
};

#endif
