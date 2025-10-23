#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "menu.h"
#include "map1.h"
#include "map2.h"
#include "map3.h"     // 👉 THÊM FILE MAP3
#include "player.h"
#include "enemy.h"
#include "map4.h"

#ifdef main   // dung de fix main k chay dc
#undef main
#endif

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  //khoi tao cua so render va xac dinh loi
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {  // tuong tu
        std::cout << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* cuaso = SDL_CreateWindow("Game cua toi",    // tao cua so render
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    SDL_Renderer* ve = SDL_CreateRenderer(
        cuaso, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //khoi tao bo ve // bo sung vsync

    bool vaogame = hienthimenu(cuaso, ve); // dung de hien thi menu

    if (vaogame) {
        std::cout << "yo";

        Map1 map(ve);
        Map2 map2(ve);
        Map3 map3(ve);
        Map4 map4(ve);
        Player player(ve, 300, 500); // toa do spon player
        SDL_Rect camera = {0, 0, 1280, 720};

        bool running = true;   // dieu khien vl chinh xdinh game chay hay end
        SDL_Event e;           // luu skien dau vao

        // gioi han fps cho card do hoa chay do nong may
        const int FPS = 60;                // fps
        const int timefps = 1000 / FPS;    // time 1 khung hinh (ms)

        Uint32 timestart; // bat dau 1 kh
        int frametime;    // time xu ly 1 khung hinh

        Uint32 lastTime = SDL_GetTicks(); // thoi gian truoc do

        // --- thêm biến điều khiển map ---
        int currentMap = 1;  // 1 = map1, 2 = map2, 3 = map3

        while (running) {
            timestart = SDL_GetTicks();  // bat dau 1 khung hinh

            while (SDL_PollEvent(&e)) { //xac dinh sk dau vao va tra ve true neu nhan sk , tv false
                if (e.type == SDL_QUIT) {
                    running = false;
                }
                player.handleEvent(e); // xu ly phim dieu khien player

                // 📌 Phím tắt chuyển map nhanh
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_1: // phím 1 -> Map1
                            currentMap = 1;
                            player.setPosition(100, 500); // vị trí spawn trên map1
                            std::cout << "Chuyen nhanh sang Map1\n";
                            break;

                        case SDLK_2: // phím 2 -> Map2
                            currentMap = 2;
                            player.setPosition(3400, 500); // vị trí spawn trên map2
                            std::cout << "Chuyen nhanh sang Map2\n";
                            break;

                        case SDLK_3: //  phím 3 -> Map3
                            currentMap = 3;
                            player.setPosition(100, 2100); // vị trí spawn trên map3
                            std::cout << "Chuyen nhanh sang Map3\n";
                            break;

                        case SDLK_4: // phím 4 -> Map4
                          currentMap = 4;
                            player.setPosition(100, 500); // vị trí spawn map4
                            std::cout << "Chuyen nhanh sang Map4\n";
                            break;
                    }
                }
            }

            // tinh deltaTime
            Uint32 currentTime = SDL_GetTicks();
            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;

            // --- cập nhật theo map hiện tại ---
            if (currentMap == 1) {
                player.update(deltaTime, map); // tg giua 2 khung hinh
                map.update(deltaTime, player);

                // kiểm tra nếu chạm tile chuyển sang map2
                if (map.checkNextMapTile(&player)) {
                    currentMap = 2;
                    player.setPosition(100, 500); // spawn vị trí mới bên map2
                    continue; // bỏ qua frame còn lại, chuyển map ngay
                }
            }

            else if (currentMap == 2) {
                player.update(deltaTime, map2);
                map2.update(deltaTime, player);
                map2.updateEnemy(deltaTime, player); // 👉 cập nhật enemy map2

                // Kiểm tra tile chuyển từ map2 sang map3
       if (map2.checkNextMapTile(&player)) {
         currentMap = 3;
        player.setPosition(200, 2100); // vị trí spawn map3
        continue;
    }
            }

            else if (currentMap == 3) { // THÊM
                player.update(deltaTime, map3);
                map3.update(deltaTime, player);
                map3.updateEnemy(deltaTime, player); // cập nhật quái map3

                // kiểm tra nếu chạm tile quay lại map2
                if (map3.checkPrevMapTile(&player)) {
                    currentMap = 2;
                    player.setPosition(100, 500);
                    continue;
                }
            }

             else if (currentMap == 4) { // THÊM PHẦN MAP4
             player.update(deltaTime, map4);
              map4.update(deltaTime, player);
               map4.updateEnemy(deltaTime, player); // nếu có quái thì thêm, không thì bỏ

               // kiểm tra nếu chạm tile quay lại map3
               if (map4.checkPrevMapTile(&player)) {
                   currentMap = 3;
                   player.setPosition(200, 2100); // ví dụ vị trí spawn map3
                   continue;
    }
}

            // --- cập nhật camera ---
            camera.x = player.getX() - camera.w / 2;
            camera.y = player.getY() - camera.h / 2;

            if (camera.x < 0) { camera.x = 0; }
            if (camera.y < 0) { camera.y = 0; }

            // giới hạn camera theo map hiện tại
            if (currentMap == 1) {
                if (camera.x > map.chieungang() - camera.w) { camera.x = map.chieungang() - camera.w; }
                if (camera.y > map.chieudoc() - camera.h) { camera.y = map.chieudoc() - camera.h; }
            }
            else if (currentMap == 2) {
                if (camera.x > map2.chieungang() - camera.w) { camera.x = map2.chieungang() - camera.w; }
                if (camera.y > map2.chieudoc() - camera.h) { camera.y = map2.chieudoc() - camera.h; }
            }
            else if (currentMap == 3) { // 👉 THÊM GIỚI HẠN CAMERA MAP3
                if (camera.x > map3.chieungang() - camera.w) { camera.x = map3.chieungang() - camera.w; }
                if (camera.y > map3.chieudoc() - camera.h) { camera.y = map3.chieudoc() - camera.h; }
            }
            else if (currentMap == 4) { // 👉 GIỚI HẠN CAMERA MAP4
           if (camera.x > map4.chieungang() - camera.w) { camera.x = map4.chieungang() - camera.w; }
            if (camera.y > map4.chieudoc() - camera.h) { camera.y = map4.chieudoc() - camera.h; }
          }

            // --- ve man hinh ---
            SDL_SetRenderDrawColor(ve, 0, 0, 0, 255);
            SDL_RenderClear(ve);

            // ve map va player
            if (currentMap == 1)
                map.render(ve, camera);
            else if (currentMap == 2)
                map2.render(ve, camera);
            else if (currentMap == 3) // thêm render map3
                map3.render(ve, camera);
            else if (currentMap == 4) //dd
            map4.render(ve, camera);

            player.render(ve, camera);

            SDL_RenderPresent(ve); // hien thi khung hinh

            // gioi han fps
            frametime = SDL_GetTicks() - timestart;
            if (timefps > frametime) {
                SDL_Delay(timefps - frametime);
            }
        }
    }

    SDL_DestroyRenderer(ve);
    SDL_DestroyWindow(cuaso);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

#ifdef _WIN32
#include <windows.h>
#endif
