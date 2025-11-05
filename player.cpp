#include "player.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "map1.h"
#include <cmath>
#include <SDL_mixer.h>


const float MOVE_SPEED = 300.0f;
const float GRAVITY    = 2900.0f;
const float JUMP_FORCE = -750.0f;

void Player::die() {
    std::cout << "Player died\n";
     if (soundDie) {
        Mix_PlayChannel(-1, soundDie, 0);
    }
    posX = spawnX;
    posY = spawnY;
    velX = 0.0f;
    velY = 0.0f;
    dstRect.x = (int)posX;
    dstRect.y = (int)posY;
    onGround = false;
    jumpCount = 0;
}

Player::Player(SDL_Renderer* renderer, float x, float y) {
    spawnX = x;
    spawnY = y;

    posX = spawnX;
    posY = spawnY;
    velX = velY = 0.0f;

    onGround = false;
    jumpCount = 0;
    leftPressed = rightPressed = false;
    movingX = false;
    animTimer = 0.0f;
    currentState = 0;
    currentFrame = 0;
    facingRight = true;

    textureIdle = IMG_LoadTexture(renderer, "assets/char/player.png");
    textureJump = IMG_LoadTexture(renderer, "assets/char/player2.png");
    jumpSound = Mix_LoadWAV("assets/sound/jum.wav");
    soundDie = Mix_LoadWAV("assets/sound/die.wav");
if (!soundDie) {
    std::cout << "Lỗi tải âm thanh chết: " << Mix_GetError() << std::endl;
} else {
    std::cout << "Âm thanh chết đã load thành công!\n";
}



if (!jumpSound) {
    std::cout << "Lỗi tải âm thanh nhảy: " << Mix_GetError() << std::endl;
}


    if (!textureIdle || !textureJump)
        std::cout << "Load texture lỗi: " << IMG_GetError() << std::endl;

    srcRect = {0, 0, 64, 64};
    dstRect = {(int)posX, (int)posY, 64, 64};
}

Player::~Player() {
    if (textureIdle) SDL_DestroyTexture(textureIdle);
    if (textureJump) SDL_DestroyTexture(textureJump);
    if (jumpSound) Mix_FreeChunk(jumpSound);
    if (soundDie) Mix_FreeChunk(soundDie);
soundDie = nullptr;

}

// Handle input
void Player::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_LEFT) leftPressed = true;
        if (e.key.keysym.sym == SDLK_RIGHT) rightPressed = true;
        if (e.key.keysym.sym == SDLK_UP && jumpCount < MAX_JUMP) {
            velY = JUMP_FORCE;
            onGround = false;
            jumpCount++;
            Mix_PlayChannel(-1, jumpSound, 0);
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_LEFT) leftPressed = false;
        if (e.key.keysym.sym == SDLK_RIGHT) rightPressed = false;
    }

    if (leftPressed && !rightPressed) {
        velX = -MOVE_SPEED;
        movingX = true;
        facingRight = false;
    } else if (!leftPressed && rightPressed) {
        velX = MOVE_SPEED;
        movingX = true;
        facingRight = true;
    } else {
        velX = 0;
        movingX = false;
    }
}


void Player::update(float deltaTime, Map1& map) {
    velY += GRAVITY * deltaTime;
    if (velY > 3300.0f) velY = 3300.0f;

    float newX = posX + velX * deltaTime;
    float newY = posY + velY * deltaTime;

    int tileSize = map.getTileSize();
    const auto& data = map.getMapData();

    int topTile    = (int)newY / tileSize;
int bottomTile = (int)(newY + dstRect.h - 1) / tileSize;
int leftTile   = (int)newX / tileSize;
int rightTile  = (int)(newX + dstRect.w - 1) / tileSize;

for (int y = topTile; y <= bottomTile; ++y) {
    for (int x = leftTile; x <= rightTile; ++x) {
        int currentTile = data[y][x];
        if (currentTile == TILE_DEATH || currentTile == TILE_TRAP || currentTile == TILE_TRAP2 || currentTile == 32) {
            die();
            return;
        }
    }
}

    onGround = false;

    {
        int leftTile = (int)newX / tileSize;
        int rightTile = (int)(newX + dstRect.w - 1) / tileSize;
        int topTile = (int)posY / tileSize;
        int bottomTile = (int)(posY + dstRect.h - 1) / tileSize;

        for (int y = topTile; y <= bottomTile && y < (int)data.size(); y++) {
            for (int x = leftTile; x <= rightTile && x < (int)data[y].size(); x++) {
                int tileType = data[y][x];

                // Điều kiện các tile player đi xuyên được
                if (tileType != 0 && tileType != 5 && tileType != 6 &&
                    (tileType < 10 || tileType > 27) &&
                    tileType != 30 && tileType != 41 && tileType != 43 &&
                    tileType != 44 && tileType != 45 && tileType != 48 &&
                    tileType != 56 && tileType != 63 && tileType != 64 &&
                    tileType != 65 && tileType != 66 && tileType != 67 &&
                    tileType != 70) {

                    SDL_Rect tileRect = {x * tileSize, y * tileSize, tileSize, tileSize};
                    SDL_Rect playerRect = {(int)newX, (int)posY, dstRect.w, dstRect.h};

                    if (SDL_HasIntersection(&playerRect, &tileRect)) {
                        if (velX > 0)
                            newX = tileRect.x - dstRect.w;
                        else if (velX < 0)
                            newX = tileRect.x + tileSize;
                        velX = 0;
                    }
                }
            }
        }
    }


onGround = false;
{
    int leftTile = (int)newX / tileSize;
    int rightTile = (int)(newX + dstRect.w - 1) / tileSize;
    int topTile = (int)newY / tileSize;
    int bottomTile = (int)(newY + dstRect.h - 1) / tileSize;

    for (int y = topTile; y <= bottomTile && y < (int)data.size(); y++) {
        for (int x = leftTile; x <= rightTile && x < (int)data[y].size(); x++) {
            int tileType = data[y][x];

            if (tileType != 0 && tileType != 5 && tileType != 6 &&
                (tileType < 10 || tileType > 27) &&
                tileType != 30 && tileType != 41 && tileType != 43 &&
                tileType != 44 && tileType != 45 && tileType != 48 &&
                tileType != 56 && tileType != 63 && tileType != 64 &&
                tileType != 65 && tileType != 66 && tileType != 67 &&
                tileType != 70) {

                SDL_Rect tileRect = {x * tileSize, y * tileSize, tileSize, tileSize};
                SDL_Rect playerRect = {(int)newX, (int)newY, dstRect.w, dstRect.h};



                if (SDL_HasIntersection(&playerRect, &tileRect)) {


                    if (velY > 0) {


                        if (tileType == 50) {
                            newY = tileRect.y - dstRect.h;
                            velY = -1200.0f;
                            onGround = false;
                            jumpCount = 0;
                        }


                        else if (tileType == 51) {
                            newY = tileRect.y - dstRect.h;
                            velY = -750.0f;
                            onGround = false;
                            jumpCount = 0;
                        }


                        else {
                            newY = tileRect.y - dstRect.h;
                            velY = 0;
                            onGround = true;
                            jumpCount = 0;
                        }
                    }


                    else if (velY < 0) {
                        newY = tileRect.y + tileSize;
                        velY = 0;
                    }
                }
            }
        }
    }
}


    posX = newX;
    posY = newY;
    dstRect.x = (int)posX;
    dstRect.y = (int)posY;

    currentState = movingX ? 1 : 0;


    if (movingX) {
        animTimer += deltaTime;
        if (animTimer >= animSpeed) {
            animTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 2;
        }
    } else {
        currentFrame = 0;
    }
}


void Player::setPosition(int x, int y) {
    posX = x;
    posY = y;
}


void Player::render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_Texture* currentTexture = (currentFrame == 0) ? textureIdle : textureJump;

    SDL_Rect renderQuad = {
        dstRect.x - camera.x,
        dstRect.y - camera.y,
        dstRect.w,
        dstRect.h
    };

    SDL_RenderCopyEx(renderer, currentTexture, &srcRect, &renderQuad, 0, nullptr,
                     facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}


float Player::getVelY() const {
    return velY;
}

void Player::bounce() {
    velY = JUMP_FORCE;
    onGround = false;
    jumpCount = 1;
}


void Player::resetToSpawn() {
    posX = spawnX;
    posY = spawnY;
    velX = velY = 0.0f;
    dstRect.x = (int)posX;
    dstRect.y = (int)posY;
    onGround = false;
    jumpCount = 0;
    alive = true;
}
