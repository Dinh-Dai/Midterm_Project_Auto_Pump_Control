# Midterm_Project_Auto_Pump_Control
Dự án giữa kỳ - Hệ thống điều khiển máy bơm mini tự động theo độ ẩm

# Giới thiệu
Tính ứng dụng thực tế
Hệ thống tưới tiêu tự động là một phần không thể thiếu trong nông nghiệp hiện đại, giúp tiết kiệm tài nguyên nước và nâng cao hiệu quả sản xuất. Đề tài này tập trung vào việc phát triển một giải pháp điều khiển máy bơm mini dựa trên độ ẩm đất. Hệ thống sẽ tự động kích hoạt máy bơm khi độ ẩm đất thấp hơn ngưỡng cài đặt và có khả năng theo dõi, điều khiển qua ứng dụng di động hoặc máy tính thông qua giao thức MQTT. 

# Nội dung chính
Thu thập dữ liệu: Sử dụng cảm biến độ ẩm đất để đo giá trị độ ẩm thực tế.

Điều khiển máy bơm: Viết mã trên nền tảng PlatformIO/Arduino để kích hoạt hoặc tắt máy bơm mini dựa trên giá trị độ ẩm và ngưỡng cài đặt.

Kết nối MQTT: Dữ liệu độ ẩm được gửi đến một broker MQTT online để hiển thị trên dashboard. Đồng thời, dashboard cho phép điều khiển thủ công máy bơm.

Giao diện dashboard: Sử dụng Node-RED để hiển thị giá trị độ ẩm, trạng thái máy bơm và cho phép điều khiển từ xa.

# Sơ đồ khối dự kiến
![image](https://github.com/user-attachments/assets/a4dbd092-9710-4f8d-acf7-d843e48872d6)

# Đặt bài toán
Vấn đề thực tế: Nông dân thường gặp khó khăn trong việc đảm bảo đất luôn đủ ẩm để cây trồng phát triển, đặc biệt trong mùa khô. Việc tưới thủ công không chỉ tốn nhiều thời gian mà còn dễ gây lãng phí nước nếu không biết chính xác tình trạng độ ẩm của đất.

Giải pháp đề xuất:
Theo dõi độ ẩm đất thời gian thực.

Tự động kích hoạt hoặc tắt máy bơm khi cần thiết.

Giám sát và điều khiển từ xa qua Internet.

Lợi ích:
Giảm công sức lao động.

Tối ưu hóa việc sử dụng nước.

Nâng cao hiệu quả quản lý đất canh tác.

# Tiến độ thực hiện
Tuần này: Hoàn thành dàn ý và thiết kế sơ đồ khối, tạo repo GitHub public để trình bày ý tưởng.

Các tuần tiếp theo:
Xây dựng mạch điện và lập trình ESP32.

Thiết kế giao diện Node-RED.

Kiểm tra và tối ưu hệ thống.

Báo cáo môn cấu trúc dữ liệu 

