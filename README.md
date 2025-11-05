#  Alien Homcoming

"Best Game 2025"

**Họ và tên:** Nguyễn Sỹ Tuân
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
## 🌌 CỐT TRUYỆN: Hành trình trở về của kẻ lạc loài

Một vụ va chạm bất ngờ khiến phi thuyền của bạn, một sinh vật ngoài hành tinh nhỏ bé, rơi xuống Trái Đất.
Khi mở mắt ra, bạn nhận ra mình đang mắc kẹt giữa một hành tinh xa lạ — nơi bầu trời có màu xanh, cây cối mọc đầy và những sinh vật khổng lồ di chuyển khắp nơi.

Không hiểu gì về thế giới này, bạn chỉ biết rằng phải tìm lại phi thuyền để quay về hành tinh quê hương trước khi năng lượng sinh tồn cạn kiệt.
Từ những khu rừng rậm um tùm, vách đá cheo leo, đến các vùng đất băng giá lạnh lẽo, bạn phải vượt qua vô vàn địa hình hiểm trở, né tránh những mối nguy và khám phá những bí ẩn mà hành tinh xanh ẩn giấu.

Trên hành trình ấy, cậu dần nhận ra — đôi khi, điều khiến ta mạnh mẽ hơn không phải là nơi ta đến, mà là hành trình để tìm đường trở về.

## 🕹️ Cơ chế chính

- **Di chuyển:** Sử dụng các phím mũi tên để di chuyển qua lại.  
- **Nhảy:** Nhấn phím ` mũi tên trên ` để nhảy và bạn có khả năng double jum.  
- **Mục tiêu:** Tìm cánh cửa cuối màn để sang địa hình kế tiếp.  
- **Thua cuộc:** Khi va chạm vào các chướng ngại vật hoặc rơi khỏi bản đồ.  
- **Âm thanh:** Nhạc nền và hiệu ứng được phát qua SDL_mixer.  

---

## 🧭 Hành trình người chơi

Người chơi sẽ bắt đầu từ bản đồ đầu tiên, băng qua nhiều khu vực có địa hình khác nhau  v.v.  
Mỗi khi chạm đến **cánh cửa thần kì**, người chơi sẽ được **dịch chuyển sang map mới**, tiến gần hơn đến mục tiêu trở về hành tinh quê hương.
Tại vùng đất cuối cùng khi tìm thấy phi thuyền của mình bạn sẽ phải đối đầu với tên trùm canh giữ chiếc phi thuyền và khi đánh bại hắn bạn với có thể lấy lại được chiếc phi thuyền.

---

## 🎨 Đồ họa

- Tài nguyên hình ảnh được lấy từ **Kenney.nl** và **tự thiết kế thêm bằng Piskel**.  
- Toàn bộ game được dựng trong không gian **2D pixel art**, tạo cảm giác hoài cổ và gần gũi.

---
## 📝 Chú thích & Lưu ý

- Các địa hình và map được thiết kế để **tạo thử thách liên tục**, từ rừng rậm, vực sâu, đến vùng băng giá.  
- Double jump đã được hỗ trợ để tăng tính linh hoạt khi di chuyển qua các chướng ngại vật.  
- Phi thuyền ở map cuối được **canh giữ bởi boss**, là mục tiêu cuối cùng của hành trình.  
- Tài nguyên media:
  - Hình ảnh: **Kenney.nl** + tự vẽ bằng **Piskel**
  - Nhạc nền & hiệu ứng: SDL_mixer, tham khảo từ game Dadish và các nguồn tài nguyên miễn phí  



## 🔧 Cấu trúc dự án

