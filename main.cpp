#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "menu.h"
#include "map1.h"
#include "map2.h"
#include "player.h"

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
    int currentMap = 1;  // 1 = map1, 2 = map2
    Map2 map2(ve);       // khởi tạo map2 sẵn để dùng sau

        while (running) {
            timestart = SDL_GetTicks();  // bat dau 1 khung hinh

            while (SDL_PollEvent(&e)) { //xac dinh sk dau vao va tra ve true neu nhan sk , tv false
                if (e.type == SDL_QUIT) {
                    running = false;
                }
                player.handleEvent(e); // xu ly phim dieu khien player
            }

            // tinh deltaTime
            Uint32 currentTime = SDL_GetTicks();



            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;

             // --- cập nhật theo map hiện tại ---
        if (currentMap == 1) {
            player.update(deltaTime, map); // tg giua 2 khung hinh
            map.update(deltaTime, player);

            // kiểm tra nếu chạm tile 30 -> chuyển sang map2
            if (map.checkNextMapTile(&player)) {
                currentMap = 2;
                player.setPosition(100, 500); // spawn vị trí mới bên map2
                continue; // bỏ qua frame còn lại, chuyển map ngay
            }
        }

            else if (currentMap == 2) {
            player.update(deltaTime, map2);
            map2.update(deltaTime, player);

            // nếu muốn có tile quay lại map1 thì thêm tương tự:
            // if (map2.checkPrevMapTile(&player)) {
            //     currentMap = 1;
            //     player.setPosition(1200, 500);
            //     continue;
            // }
        }

            camera.x = player.getX() - camera.w / 2; // dat cam cho nv giua map
            camera.y = player.getY() - camera.h / 2;
            if (camera.x < 0) { camera.x = 0; } // chan cam 0 ra ngoai map bien trai tren
            if (camera.y < 0) { camera.y = 0; }  // chan cam 0 ra ngoai map
            if (currentMap == 1) {
    if (camera.x > map.chieungang() - camera.w) { camera.x = map.chieungang() - camera.w; }
    if (camera.y > map.chieudoc() - camera.h) { camera.y = map.chieudoc() - camera.h; }
} else {
    if (camera.x > map2.chieungang() - camera.w) { camera.x = map2.chieungang() - camera.w; }
    if (camera.y > map2.chieudoc() - camera.h) { camera.y = map2.chieudoc() - camera.h; }
}
            // --- ve man hinh ---
            SDL_SetRenderDrawColor(ve, 0, 0, 0, 255); // xóa màn hình
            SDL_RenderClear(ve);

            // ve map va player
            if (currentMap == 1)
    map.render(ve, camera);
else
    map2.render(ve, camera);

player.render(ve, camera);


            SDL_RenderPresent(ve); // hien thi khung hinh

            // gioi han fps
            frametime = SDL_GetTicks() - timestart;  // tinh time xu ly khung hinh
            if (timefps > frametime) {
                SDL_Delay(timefps - frametime);    // tg nghi cho du
            }
        }
    }

    SDL_DestroyRenderer(ve);    // giai phong tai nguyen
    SDL_DestroyWindow(cuaso);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

#ifdef _WIN32
#include <windows.h>
#endif
