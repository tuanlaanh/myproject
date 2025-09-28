#include "menu.h"

bool hienthimenu(SDL_Window* cuaso, SDL_Renderer* ve) {
    SDL_Surface* anhnen = IMG_Load("Reference.png");     // tai anh len
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

    SDL_Rect nutplay = {300, 300, 200, 80};   //tao nut play
    SDL_Rect nutthoat ={300, 420, 200, 80};  // tao nut exit

    bool dangchay =true;   // dung de duy tri menu
    bool vaogame = false;   // dung de vao game
    SDL_Event sk;

    while (dangchay){     // dung de giu menu chay cho den khi co sk
        while (SDL_PollEvent(&sk)) {   // xac dinh su kien tren menu cu the dung de xac dinh click chuot
            if (sk.type == SDL_QUIT){   // dung de quit khi dung nut x goc trai man hinh
                dangchay = false;
            } else if (sk.type == SDL_MOUSEBUTTONDOWN){   // kiem tra click mouse
                int x = sk.button.x;    // xd toa do click
                int y = sk.button.y;

                if (x >= nutplay.x && x <= nutplay.x+ nutplay.w &&   // dung de kiem tra click chuot trong toa do nut play
                    y >= nutplay.y &&y <= nutplay.y +nutplay.h){
                    vaogame = true;
                    dangchay = false;
                }
                if (x >= nutthoat.x && x <= nutthoat.x + nutthoat.w&&     // tuong tu
                    y >= nutthoat.y && y <= nutthoat.y + nutthoat.h) {
                    vaogame = false;
                    dangchay = false;
                }
            }
        }

        SDL_SetRenderDrawColor(ve,0,0,0,255);
        SDL_RenderClear(ve);
        SDL_RenderCopy(ve, nen, NULL, NULL);


        SDL_SetRenderDrawColor(ve, 0, 200, 0, 255);
        SDL_RenderFillRect(ve, &nutplay);


        SDL_SetRenderDrawColor(ve, 200, 0, 0, 255);
        SDL_RenderFillRect(ve, &nutthoat);

        SDL_RenderPresent(ve);
    }

    SDL_DestroyTexture(nen);
    return vaogame;
}
