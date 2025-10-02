#include "menu.h"

bool hienthimenu(SDL_Window* cuaso, SDL_Renderer* ve) {
    SDL_Surface* anhnen = IMG_Load("nen.png");     // tai anh len
    if (!anhnen) {
        std::cout << "Lỗi ảnh: " << IMG_GetError() <<std::endl;   // xac dinh loi cua anh
        return false;
    }
    SDL_Texture* nen =SDL_CreateTextureFromSurface(ve,anhnen);    // chuyen anh trong ram thanh anh trong gpu de render
    SDL_FreeSurface(anhnen);    // giai phong ram
    if (!nen) {
        std::cout << "Lỗi tạo texture: " << SDL_GetError()<<std::endl;  // xac dinh loi
        return false;
    }


   SDL_Surface* anhnen2 = IMG_Load("nen2.png");     // tai anh nen 2
    if (!anhnen2) {
        std::cout << "Lỗi ảnh nen2.png: " << IMG_GetError() <<std::endl;   // xac dinh loi cua anh
        return false;
    }
    SDL_Texture* nen2 =SDL_CreateTextureFromSurface(ve,anhnen2);    // chuyen anh trong ram thanh anh trong gpu de render
    SDL_FreeSurface(anhnen2);    // giai phong ram
    if (!nen2) {
        std::cout << "Lỗi tạo texture nen2.png: " << SDL_GetError()<<std::endl;  // xac dinh loi
        return false;
    }

    float nen2X = 0;   // toa do cuon ngang cua nen2




    SDL_Rect nutplay = {550, 250, 200, 80};   // tao nut play
    SDL_Rect nutoptions = {550, 350, 200, 80};   // tao nut options
    SDL_Rect nutthoat ={550, 450, 200, 80};  // tao nut exit

    // tai anh nut start (5 frame)
    SDL_Texture* texstart[5] = {nullptr};
    for (int i = 0; i < 5; i++) {
        std::string filename = "nutstart" + std::to_string(i+1) + ".png";
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if (surf) {
            texstart[i] = SDL_CreateTextureFromSurface(ve, surf);
            SDL_FreeSurface(surf);
        } else {
            std::cout << "Lỗi ảnh " << filename << ": " << IMG_GetError() << std::endl;
        }
    }

    // tai anh nut options (5 frame)
    SDL_Texture* texoptions[5] = {nullptr};
    for (int i = 0; i < 5; i++) {
        std::string filename = "nutoptions" + std::to_string(i+1) + ".png";
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if (surf) {
            texoptions[i] = SDL_CreateTextureFromSurface(ve, surf);
            SDL_FreeSurface(surf);
        } else {
            std::cout << "Lỗi ảnh " << filename << ": " << IMG_GetError() << std::endl;
        }
    }

    // tai anh nut exit (5 frame)
    SDL_Texture* texexit[5] = {nullptr};
    for (int i = 0; i < 5; i++) {
        std::string filename = "nutexit" + std::to_string(i+1) + ".png";
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if (surf) {
            texexit[i] = SDL_CreateTextureFromSurface(ve, surf);
            SDL_FreeSurface(surf);
        } else {
            std::cout << "Lỗi ảnh " << filename << ": " << IMG_GetError() << std::endl;
        }
    }

    bool dangchay =true;   // dung de duy tri menu
    bool vaogame = false;   // dung de vao game
    SDL_Event sk;

    // bien animation cho 3 nut
    bool animatingStart = false, animatingOptions = false, animatingExit = false;
    int frameStart = 0, frameOptions = 0, frameExit = 0;
    Uint32 lastTimeStart = 0, lastTimeOptions = 0, lastTimeExit = 0;

    while (dangchay){
        while (SDL_PollEvent(&sk)) {
            if (sk.type == SDL_QUIT){
                dangchay = false;
            } else if (sk.type == SDL_MOUSEBUTTONDOWN){
                int x = sk.button.x;
                int y = sk.button.y;

                if (x >= nutplay.x && x <= nutplay.x+ nutplay.w &&
                    y >= nutplay.y &&y <= nutplay.y +nutplay.h){
                    animatingStart = true;
                    frameStart = 0;
                    lastTimeStart = SDL_GetTicks();
                }
                if (x >= nutoptions.x && x <= nutoptions.x+ nutoptions.w &&
                    y >= nutoptions.y &&y <= nutoptions.y +nutoptions.h){
                    animatingOptions = true;
                    frameOptions = 0;
                    lastTimeOptions = SDL_GetTicks();
                }
                if (x >= nutthoat.x && x <= nutthoat.x + nutthoat.w &&
                    y >= nutthoat.y && y <= nutthoat.y + nutthoat.h) {
                    animatingExit = true;
                    frameExit = 0;
                    lastTimeExit = SDL_GetTicks();
                }
            }
        }

        // xu ly animation nut start
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

        // xu ly animation nut options
        if (animatingOptions) {
            Uint32 now = SDL_GetTicks();
            if (now - lastTimeOptions > 120) {
                frameOptions++;
                lastTimeOptions = now;
                if (frameOptions >= 5) {
                    animatingOptions = false;
                    std::cout << "Chọn Options" << std::endl;
                }
            }
        }

        // xu ly animation nut exit
        if (animatingExit) {
            Uint32 now = SDL_GetTicks();
            if (now - lastTimeExit > 120) {
                frameExit++;
                lastTimeExit = now;
                if (frameExit >= 5) {
                    animatingExit = false;
                    vaogame = false;
                    dangchay = false;
                }
            }
        }

        SDL_SetRenderDrawColor(ve,0,0,0,255);
        SDL_RenderClear(ve);
        SDL_RenderCopy(ve, nen, NULL, NULL);
          // ve nen 2 cuon ngang
        SDL_Rect nen2Rect1 = {nen2X, 0, 1280, 720};
        SDL_Rect nen2Rect2 = {nen2X + 1280, 0, 1280, 720};
        SDL_RenderCopy(ve, nen2, NULL, &nen2Rect1);
        SDL_RenderCopy(ve, nen2, NULL, &nen2Rect2);
        nen2X -= 0.3;   // toc do cuon cua nen 2
        if (nen2X <= -1280) nen2X = 0;

        // ve nut start
        if (animatingStart && texstart[frameStart]) {
            SDL_RenderCopy(ve, texstart[frameStart], NULL, &nutplay);
        } else if (texstart[0]) {
            SDL_RenderCopy(ve, texstart[0], NULL, &nutplay);
        }

        // ve nut options
        if (animatingOptions && texoptions[frameOptions]) {
            SDL_RenderCopy(ve, texoptions[frameOptions], NULL, &nutoptions);
        } else if (texoptions[0]) {
            SDL_RenderCopy(ve, texoptions[0], NULL, &nutoptions);
        }

        // ve nut exit
        if (animatingExit && texexit[frameExit]) {
            SDL_RenderCopy(ve, texexit[frameExit], NULL, &nutthoat);
        } else if (texexit[0]) {
            SDL_RenderCopy(ve, texexit[0], NULL, &nutthoat);
        }

        SDL_RenderPresent(ve);
    }


    SDL_DestroyTexture(nen);
    SDL_DestroyTexture(nen2);
    for (int i = 0; i < 5; i++) {
        if (texstart[i]) SDL_DestroyTexture(texstart[i]);
        if (texoptions[i]) SDL_DestroyTexture(texoptions[i]);
        if (texexit[i]) SDL_DestroyTexture(texexit[i]);
    }
    return vaogame;
}
