#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

#include "menu.h"
#include "map1.h"
#include "map2.h"
#include "map3.h"
#include "map4.h"
#include "player.h"

#ifdef main
#undef main
#endif



Mix_Music* map4Music = nullptr;


enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED
};


void renderPauseMenu(SDL_Renderer* ve, SDL_Texture* resumeTexture, SDL_Texture* quitTexture) {

    SDL_SetRenderDrawBlendMode(ve, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ve, 0, 0, 0, 150);
    SDL_Rect full = {0, 0, 1280, 720};
    SDL_RenderFillRect(ve, &full);

    SDL_Rect resumeBtn = {540, 300, 200, 80};
    SDL_Rect quitBtn   = {540, 420, 200, 80};

    if (resumeTexture) SDL_RenderCopy(ve, resumeTexture, nullptr, &resumeBtn);
    if (quitTexture)   SDL_RenderCopy(ve, quitTexture,   nullptr, &quitBtn);
}


bool startGame(SDL_Window* cuaso, SDL_Renderer* ve) {

    Player player(ve, 300, 500);
    Map1 map(ve);
    Map2 map2(ve);
    Map3 map3(ve);
    Map4 map4(ve, &player);


    Mix_Music* map2Music = nullptr;
    Mix_Music* map3Music = nullptr;
    bool map2MusicPlaying = false;
    bool map3MusicPlaying = false;
    bool localMap4Playing = false;


    SDL_Texture* resumeTexture = IMG_LoadTexture(ve, "assets/buttons/nutstart1.png");
    SDL_Texture* quitTexture   = IMG_LoadTexture(ve, "assets/buttons/home01.png");
    if (!resumeTexture) std::cout  << IMG_GetError() << std::endl;
    if (!quitTexture)   std::cout   << IMG_GetError() << std::endl;


    SDL_Event e;
    Uint32 lastTime = SDL_GetTicks();
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int currentMap = 1;
    GameState currentState = STATE_PLAYING;
    bool running = true;

    while (running) {
        Uint32 timestart = SDL_GetTicks();


        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {


                SDL_DestroyTexture(resumeTexture);
                SDL_DestroyTexture(quitTexture);

                if (map2Music) { Mix_FreeMusic(map2Music); map2Music = nullptr; }
                if (map3Music) { Mix_FreeMusic(map3Music); map3Music = nullptr; }
                if (localMap4Playing && map4Music) { Mix_FreeMusic(map4Music); map4Music = nullptr; }
                return false;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                if (currentState == STATE_PLAYING) currentState = STATE_PAUSED;
                else if (currentState == STATE_PAUSED) currentState = STATE_PLAYING;
            }


            if (currentState == STATE_PLAYING) {
                player.handleEvent(e);
            }


            if (e.type == SDL_KEYDOWN && currentState == STATE_PLAYING) {
                switch (e.key.keysym.sym) {
                    case SDLK_1:
                        currentMap = 1;
                        player.setPosition(100, 500);
                        Mix_HaltMusic();

                        break;
                    case SDLK_2:
                        currentMap = 2;
                        player.setPosition(3400, 500);
                        Mix_HaltMusic();
                        if (!map2MusicPlaying) {
                            if (map2Music) Mix_FreeMusic(map2Music);
                            map2Music = Mix_LoadMUS("assets/music/nhacnen2.mp3");
                            if (map2Music) { Mix_PlayMusic(map2Music, -1); map2MusicPlaying = true; }
                            else std::cout << Mix_GetError() << std::endl;
                        } else {
                            if (map2Music) Mix_PlayMusic(map2Music, -1);
                        }
                        break;
                    case SDLK_3:
                        currentMap = 3;
                        player.setPosition(100, 2100);
                        Mix_HaltMusic();
                        if (!map3MusicPlaying) {
                            if (map3Music) Mix_FreeMusic(map3Music);
                            map3Music = Mix_LoadMUS("assets/music/nhacnen3.mp3");
                            if (map3Music) { Mix_PlayMusic(map3Music, -1); map3MusicPlaying = true; }
                            else std::cout << Mix_GetError() << std::endl;
                        } else {
                            if (map3Music) Mix_PlayMusic(map3Music, -1);
                        }
                        break;
                    case SDLK_4:
                        currentMap = 4;
                        player.setPosition(100, 500);
                        Mix_HaltMusic();
                        if (!localMap4Playing) {
                            if (map4Music) Mix_FreeMusic(map4Music);
                            map4Music = Mix_LoadMUS("assets/music/nhacboss.mp3");
                            if (map4Music) { Mix_PlayMusic(map4Music, -1); localMap4Playing = true; }
                            else std::cout << Mix_GetError() << std::endl;
                        } else {
                            if (map4Music) Mix_PlayMusic(map4Music, -1);
                        }
                        break;
                }
            }


            if (currentState == STATE_PAUSED && e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x, y = e.button.y;
                SDL_Rect resumeBtn = {540, 300, 200, 80};
                SDL_Rect quitBtn   = {540, 420, 200, 80};


                if (x >= resumeBtn.x && x <= resumeBtn.x + resumeBtn.w &&
                    y >= resumeBtn.y && y <= resumeBtn.y + resumeBtn.h) {
                    currentState = STATE_PLAYING;
                }


                if (x >= quitBtn.x && x <= quitBtn.x + quitBtn.w &&
                    y >= quitBtn.y && y <= quitBtn.y + quitBtn.h) {
                    Mix_HaltMusic();
                    if (map2Music)  { Mix_FreeMusic(map2Music);  map2Music  = nullptr; map2MusicPlaying  = false; }
                    if (map3Music)  { Mix_FreeMusic(map3Music);  map3Music  = nullptr; map3MusicPlaying  = false; }
                    if (localMap4Playing && map4Music) { Mix_FreeMusic(map4Music); map4Music = nullptr; localMap4Playing = false; }

                    SDL_DestroyTexture(resumeTexture);
                    SDL_DestroyTexture(quitTexture);
                    return true;
                }
            }
        }


        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        if (currentState == STATE_PLAYING) {

            if (currentMap == 1) {
                player.update(deltaTime, map);
                map.update(deltaTime, player);
                if (map.checkNextMapTile(&player)) {

                    currentMap = 2; player.setPosition(100, 500);
                    Mix_HaltMusic();
                    if (!map2MusicPlaying) {
                        if (map2Music) Mix_FreeMusic(map2Music);
                        map2Music = Mix_LoadMUS("assets/music/nhacnen2.mp3");
                        if (map2Music) { Mix_PlayMusic(map2Music, -1); map2MusicPlaying = true; }
                        else std::cout << Mix_GetError() << std::endl;
                    } else if (map2Music) Mix_PlayMusic(map2Music, -1);
                    continue;
                }
            } else if (currentMap == 2) {
                player.update(deltaTime, map2);
                map2.update(deltaTime, player);
                map2.updateEnemy(deltaTime, player);
                if (map2.checkNextMapTile(&player)) {
                    currentMap = 3; player.setPosition(200, 2100);
                    Mix_HaltMusic();
                    if (!map3MusicPlaying) {
                        if (map3Music) Mix_FreeMusic(map3Music);
                        map3Music = Mix_LoadMUS("assets/music/nhacnen3.mp3");
                        if (map3Music) { Mix_PlayMusic(map3Music, -1); map3MusicPlaying = true; }
                        else std::cout << Mix_GetError() << std::endl;
                    } else if (map3Music) Mix_PlayMusic(map3Music, -1);
                    continue;
                }
            } else if (currentMap == 3) {
                player.update(deltaTime, map3);
                map3.update(deltaTime, player);
                map3.updateEnemy(deltaTime, player);
                if (map3.checkPrevMapTile(&player)) {
                    currentMap = 4; player.setPosition(100, 500);
                    Mix_HaltMusic();
                    if (!localMap4Playing) {
                        if (map4Music) Mix_FreeMusic(map4Music);
                        map4Music = Mix_LoadMUS("assets/music/nhacboss.mp3");
                        if (map4Music) { Mix_PlayMusic(map4Music, -1); localMap4Playing = true; }
                        else std::cout  << Mix_GetError() << std::endl;
                    } else if (map4Music) Mix_PlayMusic(map4Music, -1);
                    continue;
                }
            } else if (currentMap == 4) {
                player.update(deltaTime, map4);
                map4.update(deltaTime, player);
                map4.updateEnemy(deltaTime, player, ve);
                if (!localMap4Playing) {
                    if (map4Music) Mix_FreeMusic(map4Music);
                    map4Music = Mix_LoadMUS("assets/music/nhacboss.mp3");
                    if (map4Music) { Mix_PlayMusic(map4Music, -1); localMap4Playing = true; }
                    else std::cout  << Mix_GetError() << std::endl;
                }
            }
        }


        SDL_Rect camera = {0,0,1280,720};
        camera.x = player.getX() - camera.w / 2;
        camera.y = player.getY() - camera.h / 2;
        if (camera.x < 0) camera.x = 0;
        if (camera.y < 0) camera.y = 0;

        int mapW = 0, mapH = 0;
        if (currentMap == 1) { mapW = map.chieungang(); mapH = map.chieudoc(); }
        if (currentMap == 2) { mapW = map2.chieungang(); mapH = map2.chieudoc(); }
        if (currentMap == 3) { mapW = map3.chieungang(); mapH = map3.chieudoc(); }
        if (currentMap == 4) { mapW = map4.chieungang(); mapH = map4.chieudoc(); }

        if (camera.x > mapW - camera.w) camera.x = mapW - camera.w;
        if (camera.y > mapH - camera.h) camera.y = mapH - camera.h;


        SDL_SetRenderDrawColor(ve, 0, 0, 0, 255);
        SDL_RenderClear(ve);

        if (currentMap == 1) map.render(ve, camera);
        else if (currentMap == 2) map2.render(ve, camera);
        else if (currentMap == 3) map3.render(ve, camera);
        else if (currentMap == 4) map4.render(ve, camera);

        player.render(ve, camera);

        if (currentState == STATE_PAUSED) {
            renderPauseMenu(ve, resumeTexture, quitTexture);
        }

        SDL_RenderPresent(ve);


        Uint32 frameTime = SDL_GetTicks() - timestart;
        if (frameTime < (Uint32)frameDelay) SDL_Delay(frameDelay - frameTime);
    }

    if (map2Music)  { Mix_FreeMusic(map2Music); map2Music = nullptr; }
    if (map3Music)  { Mix_FreeMusic(map3Music); map3Music = nullptr; }
    if (localMap4Playing && map4Music) { Mix_FreeMusic(map4Music); map4Music = nullptr; }

    SDL_DestroyTexture(resumeTexture);
    SDL_DestroyTexture(quitTexture);
    return false;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cout<< SDL_GetError() << std::endl; return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout  << IMG_GetError() << std::endl; SDL_Quit(); return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout  << Mix_GetError() << std::endl;
    }

    SDL_Window* cuaso = SDL_CreateWindow("Alien Homcoming", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    SDL_Renderer* ve = SDL_CreateRenderer(cuaso, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Mix_Music* menuMusic = Mix_LoadMUS("assets/music/nhacnen1.mp3");

    bool running = true;
    while (running) {

        if (menuMusic) {
            Mix_HaltMusic();
            Mix_PlayMusic(menuMusic, -1);
        }

        bool vaogame = hienthimenu(cuaso, ve);
        if (!vaogame) break;


        Mix_HaltMusic();
        bool backToMenu = startGame(cuaso, ve);
        if (!backToMenu) {

            running = false;
        } else {
            running = true;
        }
    }

    if (menuMusic) Mix_FreeMusic(menuMusic);
    Mix_CloseAudio();
    SDL_DestroyRenderer(ve);
    SDL_DestroyWindow(cuaso);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
