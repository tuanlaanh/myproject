#  Alien Homecoming


**Sinh viên:** Nguyễn Sỹ Tuân
**Mã sinh viên:** 24023083  
**Thể loại:** Phiêu lưu – Platformer 2D  
**Ngôn ngữ lập trình:** C++  
**Thư viện sử dụng:** SDL2, SDL_image, SDL_mixer  

---

## 🎮 Giới thiệu

**Alien Homcoming** là một trò chơi phiêu lưu 2D nơi bạn hóa thân thành **một người ngoài hành tinh bị lạc trên Trái Đất**, đang tìm cách trở về hành tinh của mình.  
Người chơi sẽ phải vượt qua nhiều **địa hình và chướng ngại vật** khác nhau để **bước qua các cánh cửa không gian**, mở ra những bản đồ (map) mới.

Game được lấy cảm hứng từ lối chơi của **Dadish** – đơn giản nhưng đầy thử thách, tập trung vào **di chuyển, nhảy và vượt chướng ngại vật**.

---
## 🌌 CỐT TRUYỆN: 

Một vụ va chạm bất ngờ khiến phi thuyền của bạn, một sinh vật ngoài hành tinh nhỏ bé, rơi xuống Trái Đất.
Khi mở mắt ra, bạn nhận ra mình đang mắc kẹt giữa một hành tinh xa lạ — nơi bầu trời có màu xanh, cây cối mọc đầy và những sinh vật kì lạ di chuyển khắp nơi.

Không hiểu gì về thế giới này, bạn chỉ biết rằng phải tìm lại phi thuyền để quay về hành tinh quê hương trước khi năng lượng sinh tồn cạn kiệt.
Từ những khu rừng rậm um tùm, vách đá cheo leo, đến các vùng đất băng giá lạnh lẽo, bạn phải vượt qua vô vàn địa hình hiểm trở, né tránh những mối nguy và khám phá những bí ẩn mà hành tinh xanh ẩn giấu.

Trên hành trình ấy, bạn dần nhận ra — đôi khi, điều khiến ta mạnh mẽ hơn không phải là nơi ta đến, mà là hành trình để tìm đường trở về.

## 🕹️ Cơ chế chính

- **Di chuyển:** Sử dụng các phím mũi tên để di chuyển qua lại.  
- **Nhảy:** Nhấn phím ` mũi tên trên ` để nhảy và bạn có khả năng double jum.  
- **Mục tiêu:** Tìm cánh cửa cuối màn để sang địa hình kế tiếp.  
- **Thua cuộc:** Khi va chạm vào các chướng ngại vật hoặc rơi khỏi bản đồ.  
- **Âm thanh:** Nhạc nền và hiệu ứng được phát qua SDL_mixer.  

---

## 🧭 Hành trình người chơi

Người chơi sẽ bắt đầu từ bản đồ đầu tiên, băng qua nhiều khu vực có địa hình khác nhau  v.v.  
Mỗi khi chạm đến **cánh cửa thần kì**, người chơi sẽ được **dịch chuyển sang map mới**, tiến gần hơn đến mục tiêu tìm kiếm phi thuyền.
Tại vùng đất cuối cùng khi tìm thấy phi thuyền của mình bạn sẽ phải đối đầu với tên trùm canh giữ chiếc phi thuyền và khi đánh bại hắn bạn với có thể lấy lại được chiếc phi thuyền.

---

## 🎨 Đồ họa, tài nguyên

- Tài nguyên hình ảnh được lấy từ **Kenney.nl** và **tự thiết kế thêm bằng Piskel**.  
- tài nguyên âm thanh được tham khảo từ game **dadish** và tổng hợp âm thanh từ nhiều nguồn khác trên mạng

---
## Thông tin ,chú thích 
Sử dụng ChatGPT để hỗ trợ hiểu mã SDL, tối ưu hóa logic, phát hiện và sửa lỗi, tham khảo đoạn code, đồng thời học hỏi và nâng cao kỹ năng lập trình.
có tham khảo code và học hỏi cấu trúc chính trong game từ các nguồn:
tham khảo cấu trúc map ma trận-https://youtu.be/FQOiFUl93lI?si=cZvcsHR8shXqvha9
 tham khảo cơ chế enemy-https://youtu.be/LETiw3RocZA?si=1r4F0V1ytuAOy8tH
 và các nguồn khác trên youtube, lazyfoo...




## 🔧 Cấu trúc dự án

Alien-Homcoming/
│
├── main.cpp              → Tệp khởi động chính, điều khiển vòng lặp game (Game Loop)
│
├── menu.h / menu.cpp     → Quản lý menu chính, giao diện bắt đầu và chọn bản đồ
│
├── player.h / player.cpp → Xử lý nhân vật chính: di chuyển, nhảy, va chạm, hoạt ảnh, trạng thái
│
├── enemy.cpp / enemy3.cpp   → Quản lý kẻ địch di chuyển tuần tra, va chạm và phản ứng với môi trường
│
├── boss.h / boss.cpp     → Quản lý trùm cuối: AI chiến đấu, thanh máu, va chạm,
│
├── map1.cpp → map4.cpp   → Mỗi map tương ứng với một cấp độ, có cấu trúc riêng và nhạc nền riêng
│
├── assets/               → Hình ảnh sprite, tilemap,âm thanh ,hiệu ứng ,background, (Pixel Art từ Kenney + Piskel)
│
└── README.md             → Tài liệu mô tả dự án, ý tưởng, cốt truyện, cơ chế game
## LINK VIDEO DEMO:
https://youtu.be/vYLS9BwVYDk

