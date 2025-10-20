#pragma once
#include <SDL.h>
#include <SDL2/SDL_image.h>

class Enemy {
public:
    // Khởi tạo quái, truyền renderer, vị trí (x, y) và số tile muốn di chuyển
    Enemy(SDL_Renderer* renderer, int x, int y, int rangeTiles);
    ~Enemy();

    void update(float deltaTime);                     // cập nhật vị trí + animation
    void render(SDL_Renderer* renderer, SDL_Rect camera);  // vẽ quái
    bool checkCollision(const SDL_Rect& playerRect);  // kiểm tra va chạm với player

    SDL_Rect getRect() const { return dstRect; }      // lấy khung của quái

private:
    SDL_Texture* texture1;       // ảnh 1
    SDL_Texture* texture2;       // ảnh 2
    SDL_Texture* currentTexture; // ảnh hiện tại đang hiển thị

    SDL_Rect dstRect;            // vị trí và kích thước quái

    int startX;                  // vị trí bắt đầu
    int moveRange;               // phạm vi di chuyển (tính bằng pixel)
    float speed;                 // tốc độ di chuyển
    int direction;               // hướng: 1 = phải, -1 = trái
    float animTimer;             // bộ đếm để đổi hình
};
