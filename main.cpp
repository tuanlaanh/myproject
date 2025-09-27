#include <SDL2/SDL.h>        // Thư viện chính của SDL2 (dùng để tạo cửa sổ, render, xử lý sự kiện)
#include <SDL2/SDL_image.h>  // Thư viện SDL2_image (dùng để load ảnh PNG, JPG...)
#include <iostream>          // Thư viện chuẩn C++ để in ra màn hình (std::cout)

// Xóa định nghĩa mặc định của "main" trên Windows để tránh xung đột với SDL
#ifdef main
#undef main
#endif

int main(int argc, char* argv[]) {
    // ------------------- KHỞI TẠO SDL -------------------
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // Khởi tạo SDL2 với module video
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1; // Nếu lỗi thì thoát chương trình
    }

    // ------------------- KHỞI TẠO SDL_IMAGE -------------------
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) { // Khởi tạo SDL2_image để load file PNG
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // ------------------- TẠO CỬA SỔ -------------------
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Menu Test",          // Tiêu đề cửa sổ
        SDL_WINDOWPOS_CENTERED,    // Vị trí X (giữa màn hình)
        SDL_WINDOWPOS_CENTERED,    // Vị trí Y (giữa màn hình)
        800, 600,                  // Kích thước cửa sổ (800x600)
        SDL_WINDOW_SHOWN           // Hiển thị cửa sổ ngay sau khi tạo
    );
    if (!window) { // Nếu tạo cửa sổ lỗi thì in ra và thoát
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // ------------------- TẠO RENDERER -------------------
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED // Renderer dùng GPU để tăng tốc
    );
    if (!renderer) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // ------------------- LOAD ẢNH NỀN -------------------
    SDL_Surface* surface = IMG_Load("Reference.png"); // Load ảnh PNG
    if (!surface) {
        std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface); // Chuyển ảnh sang texture
    SDL_FreeSurface(surface); // Giải phóng surface (không cần nữa)
    if (!background) {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // ------------------- TẠO 2 NÚT -------------------
    SDL_Rect startButton = {300, 300, 200, 80}; // Nút Start (tọa độ X=300, Y=200, rộng=200, cao=80)
    SDL_Rect exitButton  = {300, 420, 200, 80}; // Nút Exit (tọa độ X=300, Y=320, rộng=200, cao=80)

    // ------------------- VÒNG LẶP CHÍNH -------------------
    bool running = true;   // Cờ để điều khiển vòng lặp game
    SDL_Event e;           // Biến sự kiện

    while (running) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { // Nếu bấm nút X thì thoát
                running = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) { // Nếu nhấn chuột
                int x = e.button.x; // Lấy tọa độ X chuột
                int y = e.button.y; // Lấy tọa độ Y chuột

                // Kiểm tra xem có click vào nút Start không
                if (x >= startButton.x && x <= startButton.x + startButton.w &&
                    y >= startButton.y && y <= startButton.y + startButton.h) {
                    std::cout << "Start button clicked!" << std::endl;
                }

                // Kiểm tra xem có click vào nút Exit không
                if (x >= exitButton.x && x <= exitButton.x + exitButton.w &&
                    y >= exitButton.y && y <= exitButton.y + exitButton.h) {
                    std::cout << "Exit button clicked!" << std::endl;
                    running = false; // Thoát chương trình
                }
            }
        }

        // ------------------- VẼ LÊN MÀN HÌNH -------------------
        SDL_RenderClear(renderer);                   // Xóa màn hình cũ
        SDL_RenderCopy(renderer, background, NULL, NULL); // Vẽ ảnh nền toàn màn hình

        // Vẽ nút Start (xanh lá)
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
        SDL_RenderFillRect(renderer, &startButton);

        // Vẽ nút Exit (đỏ)
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        SDL_RenderFillRect(renderer, &exitButton);

        SDL_RenderPresent(renderer); // Cập nhật màn hình
    }

    // ------------------- DỌN DẸP BỘ NHỚ -------------------
    SDL_DestroyTexture(background); // Hủy texture ảnh nền
    SDL_DestroyRenderer(renderer);  // Hủy renderer
    SDL_DestroyWindow(window);      // Hủy cửa sổ
    IMG_Quit();                     // Thoát SDL_image
    SDL_Quit();                     // Thoát SDL

    return 0;
}

