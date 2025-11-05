#include "menu.h"
#include <SDL_mixer.h>

GameOptions gameOptions;

bool hienthimenu(SDL_Window* cuaso, SDL_Renderer* ve) {
    SDL_Surface* anhnen = IMG_Load("nen.png");
    if (!anhnen) {
        std::cout << IMG_GetError() <<std::endl;
        return false;
    }
    SDL_Texture* nen = SDL_CreateTextureFromSurface(ve, anhnen);
    SDL_FreeSurface(anhnen);
    if (!nen) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Surface* anhnen2 = IMG_Load("nen2.png");
    if (!anhnen2) {
        std::cout <<IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* nen2 = SDL_CreateTextureFromSurface(ve, anhnen2);
    SDL_FreeSurface(anhnen2);
    if (!nen2) {
        std::cout << SDL_GetError()<< std::endl;
        return false;
    }

    float nen2X = 0;

    SDL_Texture* tenTexture = nullptr;
    SDL_Surface* tenSurface = IMG_Load("ten.png");
    if (tenSurface) {
        tenTexture = SDL_CreateTextureFromSurface(ve, tenSurface);
        SDL_FreeSurface(tenSurface);
    } else {
        std::cout << IMG_GetError() << std::endl;
    }

    SDL_Rect tenRect = {426, 80, 450, 170};
    SDL_Rect nutplay = {550, 300, 200, 80};
    SDL_Rect nutoptions = {550, 400, 200, 80};
    SDL_Rect nutthoat = {550, 500, 200, 80};

    // Nút Start
    SDL_Texture* texstart[5] = {nullptr};
    for (int i = 0; i < 5; i++) {
        std::string filename = "assets/buttons/nutstart" + std::to_string(i + 1) + ".png";
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if (surf) {
            texstart[i] = SDL_CreateTextureFromSurface(ve, surf);
            SDL_FreeSurface(surf);
        } else {
            std::cout << "error " << filename << ": " << IMG_GetError() << std::endl;
        }
    }

    // Nút Options
    SDL_Texture* texoptions[5] = {nullptr};
    for (int i = 0; i < 5; i++) {
        std::string filename = "assets/buttons/nutoptions" + std::to_string(i + 1) + ".png";
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if (surf) {
            texoptions[i] = SDL_CreateTextureFromSurface(ve, surf);
            SDL_FreeSurface(surf);
        } else {
            std::cout << "error png "<< filename << ": " << IMG_GetError() << std::endl;
        }
    }

    // Nút Exit
    SDL_Texture* texexit[5] = {nullptr};
    for (int i = 0; i < 5; i++) {
        std::string filename = "assets/buttons/nutexit" + std::to_string(i + 1) + ".png";
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if (surf) {
            texexit[i] = SDL_CreateTextureFromSurface(ve, surf);
            SDL_FreeSurface(surf);
        } else {
            std::cout << "error png " << filename << ": " << IMG_GetError() << std::endl;
        }
    }

    bool dangchay = true;
    bool vaogame = false;
    SDL_Event sk;

    bool animatingStart = false, animatingOptions = false, animatingExit = false;
    int frameStart = 0, frameOptions = 0, frameExit = 0;
    Uint32 lastTimeStart = 0, lastTimeOptions = 0, lastTimeExit = 0;

    Mix_Chunk* clickSound = Mix_LoadWAV("assets/sound/bt.mp3");
    if (!clickSound) {
        std::cout <<Mix_GetError() << std::endl;
    }

    while (dangchay) {
        while (SDL_PollEvent(&sk)) {
            if (sk.type == SDL_QUIT) {
                dangchay = false;
            } else if (sk.type == SDL_MOUSEBUTTONDOWN) {
                int x = sk.button.x;
                int y = sk.button.y;

                if (x >= nutplay.x && x <= nutplay.x + nutplay.w &&
                    y >= nutplay.y && y <= nutplay.y + nutplay.h) {
                    if (gameOptions.sfxOn && clickSound)
                        Mix_PlayChannel(-1, clickSound, 0);
                    animatingStart = true;
                    frameStart = 0;
                    lastTimeStart = SDL_GetTicks();
                }

                if (x >= nutoptions.x && x <= nutoptions.x + nutoptions.w &&
                    y >= nutoptions.y && y <= nutoptions.y + nutoptions.h) {
                    if (gameOptions.sfxOn && clickSound)
                        Mix_PlayChannel(-1, clickSound, 0);
                    animatingOptions = true;
                    frameOptions = 0;
                    lastTimeOptions = SDL_GetTicks();
                }

                if (x >= nutthoat.x && x <= nutthoat.x + nutthoat.w &&
                    y >= nutthoat.y && y <= nutthoat.y + nutthoat.h) {
                    if (gameOptions.sfxOn && clickSound)
                        Mix_PlayChannel(-1, clickSound, 0);
                    animatingExit = true;
                    frameExit = 0;
                    lastTimeExit = SDL_GetTicks();
                }
            }
        }


        if (animatingStart) {
            Uint32 now = SDL_GetTicks();
            if (now - lastTimeStart > 120) {
                frameStart++;
                lastTimeStart = now;
                if (frameStart >= 5) {
                    animatingStart = false;
                    vaogame = true;
                    dangchay = false;
                }
            }
        }


        if (animatingOptions) {
            Uint32 now = SDL_GetTicks();
            if (now - lastTimeOptions > 120) {
                frameOptions++;
                lastTimeOptions = now;
                if (frameOptions >= 5) {
                    animatingOptions = false;
                    hienThiOptions(cuaso, ve, gameOptions);
                }
            }
        }


        if (animatingExit) {
            Uint32 now = SDL_GetTicks();
            if (now - lastTimeExit > 120) {
                frameExit++;
                lastTimeExit = now;
                if (frameExit >= 5) {
                    animatingExit = false;
                    vaogame=false;
                    dangchay= false;
                }
            }
        }
        SDL_SetRenderDrawColor(ve, 0, 0, 0, 255);
        SDL_RenderClear(ve);
        SDL_RenderCopy(ve, nen, NULL, NULL);

        SDL_Rect nen2Rect1 = {static_cast<int>(nen2X), 0, 1280, 720};
        SDL_Rect nen2Rect2 = {static_cast<int>(nen2X + 1280.0f), 0, 1280, 720};
        SDL_RenderCopy(ve, nen2, NULL, &nen2Rect1);
        SDL_RenderCopy(ve, nen2, NULL, &nen2Rect2);
        nen2X -= 1;
        if (nen2X <= -1280) nen2X = 0;

        if (tenTexture)
            SDL_RenderCopy(ve, tenTexture, NULL, &tenRect);


        SDL_RenderCopy(ve,texstart[animatingStart ? frameStart : 0], NULL, &nutplay);
        SDL_RenderCopy(ve,texoptions[animatingOptions ? frameOptions : 0], NULL, &nutoptions);
        SDL_RenderCopy(ve, texexit[animatingExit ? frameExit : 0], NULL, &nutthoat);

        SDL_RenderPresent(ve);
    }

    Mix_HaltChannel(-1);
    if (clickSound) Mix_FreeChunk(clickSound);

    SDL_DestroyTexture(nen);
    SDL_DestroyTexture(nen2);
    for (int i = 0; i < 5; i++) {
        if (texstart[i]) SDL_DestroyTexture(texstart[i]);
        if (texoptions[i]) SDL_DestroyTexture(texoptions[i]);
        if (texexit[i]) SDL_DestroyTexture(texexit[i]);
    }

    return vaogame;
}


void hienThiOptions(SDL_Window* cuaso, SDL_Renderer* ve, GameOptions& options) {
    Mix_Chunk* clickSound = Mix_LoadWAV("assets/sound/bt.mp3");
    if (!clickSound) std::cout << "Lỗi load bt.mp3: " << Mix_GetError() << std::endl;

    SDL_Surface* anhnen = IMG_Load("nen.png");
    SDL_Texture* nen = SDL_CreateTextureFromSurface(ve, anhnen);
    SDL_FreeSurface(anhnen);

    SDL_Surface* anhnen2 = IMG_Load("nen2.png");
    SDL_Texture* nen2 = SDL_CreateTextureFromSurface(ve, anhnen2);
    SDL_FreeSurface(anhnen2);

    float nen2X = 0.0f;

    SDL_Rect nutMusic = {550, 300, 200, 80};
    SDL_Rect nutSFX   = {550, 400, 200, 80};
    SDL_Rect nutBack  = {550, 500, 200, 80};

      SDL_Texture* texMusicOn  = IMG_LoadTexture(ve, "musicon.png");
    SDL_Texture* texMusicOff =IMG_LoadTexture(ve, "musicoff.png");
    SDL_Texture* texSFXOn   = IMG_LoadTexture(ve, "soundon.png");
    SDL_Texture* texSFXOff   = IMG_LoadTexture(ve, "soundoff.png");

    SDL_Texture* texBack[5] = {nullptr};
    const char* backFiles[5] = {
        "assets/buttons/home01.png",
        "assets/buttons/home02.png",
        "assets/buttons/home03.png",
    "assets/buttons/home04.png",
        "assets/buttons/home05.png"
    };

    for (int i = 0; i < 5; i++) {
        SDL_Surface* surf = IMG_Load(backFiles[i]);
        if (surf) {
            texBack[i] = SDL_CreateTextureFromSurface(ve, surf);
            SDL_FreeSurface(surf);
        } else std::cout << "Lỗi " << backFiles[i] << ": " << IMG_GetError() << std::endl;
    }

    bool dangChay = true;
    SDL_Event sk;
    bool animatingBack = false;
    int frameBack = 0;
    Uint32 lastTimeBack = 0;

    while (dangChay) {
        while (SDL_PollEvent(&sk)) {
            if (sk.type == SDL_QUIT) exit(0);
            else if (sk.type == SDL_MOUSEBUTTONDOWN) {
                int x = sk.button.x, y = sk.button.y;

                if (x >= nutMusic.x && x <= nutMusic.x + nutMusic.w &&
                    y >= nutMusic.y && y <= nutMusic.y + nutMusic.h) {
                    options.musicOn = !options.musicOn;
                    if (options.musicOn) Mix_ResumeMusic();
                else Mix_PauseMusic();
                    if (options.sfxOn && clickSound)
                        Mix_PlayChannel(-1, clickSound, 0);
                }

                if (x >= nutSFX.x && x <= nutSFX.x + nutSFX.w &&
                    y >= nutSFX.y && y <= nutSFX.y + nutSFX.h) {
                    options.sfxOn = !options.sfxOn;
                if (options.sfxOn && clickSound)
                        Mix_PlayChannel(-1, clickSound, 0);
                }

                if (x >= nutBack.x && x <= nutBack.x + nutBack.w &&
                    y >= nutBack.y && y <= nutBack.y + nutBack.h) {
                animatingBack = true;
                    frameBack = 0;
                    lastTimeBack = SDL_GetTicks();
                    if (options.sfxOn && clickSound)
                        Mix_PlayChannel(-1, clickSound, 0);
                }
            }
        }

        if (animatingBack) {
            Uint32 now = SDL_GetTicks();
            if (now - lastTimeBack > 120) {
                frameBack++;
                lastTimeBack = now;
            if (frameBack >= 5) {
                    animatingBack = false;
                    dangChay = false;
                }
            }
        }

        SDL_RenderClear(ve);
        SDL_RenderCopy(ve, nen, NULL, NULL);

        SDL_Rect nen2Rect1 = {static_cast<int>(nen2X), 0, 1280, 720};
        SDL_Rect nen2Rect2 = {static_cast<int>(nen2X + 1280.0f), 0, 1280, 720};
        SDL_RenderCopy(ve, nen2, NULL, &nen2Rect1);
    SDL_RenderCopy(ve, nen2, NULL, &nen2Rect2);
        nen2X -= 1.0f;
        if (nen2X <= -1280) nen2X = 0;

        SDL_RenderCopy(ve, options.musicOn ? texMusicOn : texMusicOff, NULL, &nutMusic);
        SDL_RenderCopy(ve, options.sfxOn ? texSFXOn : texSFXOff, NULL, &nutSFX);
        SDL_RenderCopy(ve, texBack[animatingBack ? frameBack : 0], NULL, &nutBack);

        SDL_RenderPresent(ve);
    }

    Mix_FreeChunk(clickSound);
    SDL_DestroyTexture(nen);
    SDL_DestroyTexture(nen2);
    SDL_DestroyTexture(texMusicOn);
    SDL_DestroyTexture(texMusicOff);
    SDL_DestroyTexture(texSFXOn);
    SDL_DestroyTexture(texSFXOff);
    for (int i = 0; i < 5; i++) if (texBack[i]) SDL_DestroyTexture(texBack[i]);
}
