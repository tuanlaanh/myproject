#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "menu.h"
#include "map1.h"
#include "map2.h"
#include "map3.h"
#include "player.h"
#include "enemy.h"
#include "map4.h"
#include <SDL_mixer.h>

#ifdef main   // dung de fix main k chay dc
#undef main
#endif

Mix_Music* map4Music = nullptr;

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


    // --- Khởi tạo SDL_mixer ---
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Lỗi âm thanh: " << Mix_GetError() << std::endl;
    }


    SDL_Window* cuaso = SDL_CreateWindow("Game cua toi",    // tao cua so render
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    SDL_Renderer* ve = SDL_CreateRenderer(
        cuaso, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //khoi tao bo ve // bo sung vsync


         // --- Tải và phát nhạc menu ---
    Mix_Music* menuMusic = Mix_LoadMUS("assets/music/nhacnen1.mp3");
    if (!menuMusic) {
        std::cout << "Không tải được nhạc menu: " << Mix_GetError() << std::endl;
    } else {
        Mix_PlayMusic(menuMusic, -1); // phát lặp vô hạn trong menu
    }

    Mix_Music* map2Music = nullptr;
     Mix_Music* map3Music = nullptr;


    bool vaogame = hienthimenu(cuaso, ve); // dung de hien thi menu

    if (vaogame) {

            Mix_HaltMusic(); // Dừng nhạc menu trước khi chuyển sang game
        std::cout << "yo";
         Player player(ve, 300, 500); // toa do spon player
        Map1 map(ve);
        Map2 map2(ve);
        Map3 map3(ve);
        Map4 map4(ve, &player);

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
                            player.setPosition(100, 500); // vị trí spaw


                            break;

                        case SDLK_2:
                            currentMap = 2;
                            player.setPosition(3400, 500);
                            std::cout << "Chuyen nhanh sang Map2\n";
                            break;

                        case SDLK_3:
                            currentMap = 3;
                            player.setPosition(100, 2100);
                            std::cout << "Chuyen nhanh sang Map3\n";
                            break;

                        case SDLK_4:
                          currentMap = 4;
                            player.setPosition(100, 500);
                            std::cout << "Chuyen nhanh sang Map4\n";
                            break;
                    }
                }
            }
static bool map2MusicPlaying = false;
static bool map3MusicPlaying = false;
static bool map4MusicPlaying = false;
            // tinh deltaTime
            Uint32 currentTime = SDL_GetTicks();
            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;

          // cập nhật theo map hiện tại
if (currentMap == 1) {
    player.update(deltaTime, map);
    map.update(deltaTime, player);

    if (map.checkNextMapTile(&player)) {
        Mix_HaltMusic();

        if (!map2MusicPlaying) {
            map2Music = Mix_LoadMUS("assets/music/nhacnen2.mp3");
            if (map2Music) Mix_PlayMusic(map2Music, -1);
            else printf("Lỗi tải nhạc map2: %s\n", Mix_GetError());
            map2MusicPlaying = true;
        }

        currentMap = 2;
        player.setPosition(100, 500);
        continue;
    }
}
else if (currentMap == 2) {
    player.update(deltaTime, map2);
    map2.update(deltaTime, player);
    map2.updateEnemy(deltaTime, player);

    if (map2.checkNextMapTile(&player)) {
        currentMap = 3;
        player.setPosition(200, 2100);
        Mix_HaltMusic();

        if (!map3MusicPlaying) {
            map3Music = Mix_LoadMUS("assets/music/nhacnen3.mp3");
            if (map3Music) Mix_PlayMusic(map3Music, -1);
            else printf("Lỗi tải nhạc map3: %s\n", Mix_GetError());
            map3MusicPlaying = true;
        }
        continue;
    }
}
else if (currentMap == 3) {
    player.update(deltaTime, map3);
    map3.update(deltaTime, player);
    map3.updateEnemy(deltaTime, player);

    if (map3.checkPrevMapTile(&player)) {
        currentMap = 4;
        player.setPosition(100, 500);
        Mix_HaltMusic();

        if (!map4MusicPlaying) {
            map4Music = Mix_LoadMUS("assets/music/nhacboss.mp3");
            if (map4Music) Mix_PlayMusic(map4Music, -1);
            else printf("Lỗi tải nhạc map4/boss: %s\n", Mix_GetError());
            map4MusicPlaying = true;
        }
        continue;
    }
}
else if (currentMap == 4) {
    player.update(deltaTime, map4);
    map4.update(deltaTime, player);
    map4.updateEnemy(deltaTime, player, ve);

    // --- nhạc boss chỉ load 1 lần khi vào map4 ---
    if (!map4MusicPlaying) {
        Mix_HaltMusic();
        map4Music = Mix_LoadMUS("assets/music/nhacboss.mp3");
        if (map4Music) Mix_PlayMusic(map4Music, -1);
        else printf("Lỗi tải nhạc boss map4: %s\n", Mix_GetError());
        map4MusicPlaying = true;
    }
}
            //  camera
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
            else if (currentMap == 3) {
                if (camera.x > map3.chieungang() - camera.w) { camera.x = map3.chieungang() - camera.w; }
                if (camera.y > map3.chieudoc() - camera.h) { camera.y = map3.chieudoc() - camera.h; }
            }
            else if (currentMap == 4) {
           if (camera.x > map4.chieungang() - camera.w) { camera.x = map4.chieungang() - camera.w; }
            if (camera.y > map4.chieudoc() - camera.h) { camera.y = map4.chieudoc() - camera.h; }
          }

            // ve man hinh
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
    Mix_FreeMusic(menuMusic);
    Mix_CloseAudio();
    SDL_DestroyRenderer(ve);
    SDL_DestroyWindow(cuaso);
    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}

#ifdef _WIN32
#include <windows.h>
#endif
