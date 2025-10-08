#include "player.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "map1.h"

//Constan
const float MOVE_SPEED = 300.0f;
const float GRAVITY    = 3000.0f;
const float JUMP_FORCE = -700.0f;



void Player::die() {
    std::cout << "Pl die\n";
    posX = spawnX;
    posY = spawnY;
    velX = 0.0f;
    velY = 0.0f;

    // cập nhật dstRect
    dstRect.x = (int)posX;
    dstRect.y = (int)posY;
    dstRect.w = 64;
    dstRect.h = 64;
}

// Constructor
Player::Player(SDL_Renderer* renderer, float x, float y) {


    spawnX = x;   // x truyền vào constructor = vị trí an toàn trên map
    spawnY = y;   // y truyền vào constructor = vị trí an toàn trên map

     // Khởi tạo pos ban đầu bằng spawn
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

    //Load texture
    textureIdle = IMG_LoadTexture(renderer, "assets/char/player.png");
    textureJump = IMG_LoadTexture(renderer, "assets/char/player2.png");

    if (!textureIdle || !textureJump)
        std::cout << IMG_GetError() << std::endl;

    srcRect = {0, 0, 64, 64};
    dstRect = {(int)posX, (int)posY, 64, 64};
}

// Destructor
Player::~Player() {
    if (textureIdle) SDL_DestroyTexture(textureIdle);
    if (textureJump) SDL_DestroyTexture(textureJump);
}

//Handle key events
void Player::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_LEFT) leftPressed = true;
        if (e.key.keysym.sym == SDLK_RIGHT) rightPressed = true;
        if (e.key.keysym.sym == SDLK_UP && jumpCount < MAX_JUMP) {
            velY = JUMP_FORCE;
            onGround = false;
            jumpCount++;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_LEFT) leftPressed = false;
        if (e.key.keysym.sym == SDLK_RIGHT) rightPressed = false;
    }

    if (leftPressed && !rightPressed) {
        velX = -MOVE_SPEED;
        movingX = true;
    } else if (!leftPressed && rightPressed) {
        velX = MOVE_SPEED;
        movingX = true;
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



    //  KIỂM TRACHẾT
    int tileX1 = (int)(newX) / tileSize;
    int tileX2 = (int)(newX + dstRect.w - 1) / tileSize;
    int tileY  = (int)(newY + dstRect.h - 1) / tileSize;

    for (int tx = tileX1; tx <= tileX2; ++tx) {
        int currentTile = map.getMapData()[tileY][tx];
        if (currentTile == TILE_DEATH) {
            die();      // quay về spawn
            return;     // dừng update tiếp
        }
    }



    onGround = false;

  //  X
{
    int leftTile   = (int)newX / tileSize;
    int rightTile  = (int)(newX + dstRect.w - 1) / tileSize;
    int topTile    = (int)posY / tileSize;
    int bottomTile = (int)(posY + dstRect.h - 1) / tileSize;

    for (int y = topTile; y <= bottomTile && y < (int)data.size(); y++) {
        for (int x = leftTile; x <= rightTile && x < (int)data[y].size(); x++) {
            int tileType = data[y][x];
            if (tileType != 0 && tileType != 5 && tileType != 6 &&
                (tileType < 10 || tileType > 25))
            {
                SDL_Rect tileRect   = {x * tileSize, y * tileSize, tileSize, tileSize};
                SDL_Rect playerRect = {(int)newX, (int)posY, dstRect.w, dstRect.h};

                if (SDL_HasIntersection(&playerRect, &tileRect)) {
                    if (velX > 0)  // đi sang phải
                        newX = tileRect.x - dstRect.w;
                    else if (velX < 0) // đi sang trái
                        newX = tileRect.x + tileSize;
                    velX = 0;
                }
            }
        }
    }
}

// y
{
    int leftTile   = (int)newX / tileSize;
    int rightTile  = (int)(newX + dstRect.w - 1) / tileSize;
    int topTile    = (int)newY / tileSize;
    int bottomTile = (int)(newY + dstRect.h - 1) / tileSize;

    onGround = false; // reset, để kiểm tra lại

    for (int y = topTile; y <= bottomTile && y < (int)data.size(); y++) {
        for (int x = leftTile; x <= rightTile && x < (int)data[y].size(); x++) {
            int tileType = data[y][x];
            if (tileType != 0 && tileType != 5 && tileType != 6 &&
                (tileType < 10 || tileType > 25))
            {
                SDL_Rect tileRect   = {x * tileSize, y * tileSize, tileSize, tileSize};
                SDL_Rect playerRect = {(int)newX, (int)newY, dstRect.w, dstRect.h};

                if (SDL_HasIntersection(&playerRect, &tileRect)) {
                    if (velY > 0) {
                        // chạm đất
                        newY = tileRect.y - dstRect.h;
                        velY = 0;
                        onGround = true;
                        jumpCount = 0;
                    } else if (velY < 0) {
                        // chạm trần
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


    if (velX != 0) {
        currentState = 1;   // đang di chuyển player2.png
    } else {
        currentState = 0;   // đứng im player.png
    }
}


void Player::render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_Rect renderQuad = {
        dstRect.x - camera.x,
        dstRect.y - camera.y,
        dstRect.w,
        dstRect.h
    };

    SDL_Texture* currentTexture = (currentState == 1) ? textureJump : textureIdle;
    SDL_RenderCopy(renderer, currentTexture, &srcRect, &renderQuad);
}

