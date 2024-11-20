# Midterm_Project_Auto_Pump_Control
Dự án giữa kỳ - Hệ thống điều khiển máy bơm mini tự động theo độ ẩm

1. Giới thiệu
Tính ứng dụng thực tế
Hệ thống tưới tiêu tự động là một phần không thể thiếu trong nông nghiệp hiện đại, giúp tiết kiệm tài nguyên nước và nâng cao hiệu quả sản xuất. Đề tài này tập trung vào việc phát triển một giải pháp điều khiển máy bơm mini dựa trên độ ẩm đất. Hệ thống sẽ tự động kích hoạt máy bơm khi độ ẩm đất thấp hơn ngưỡng cài đặt và có khả năng theo dõi, điều khiển qua ứng dụng di động hoặc máy tính thông qua giao thức MQTT.

2. Nội dung chính
Thu thập dữ liệu: Sử dụng cảm biến độ ẩm đất để đo giá trị độ ẩm thực tế.
Điều khiển máy bơm: Kích hoạt hoặc tắt máy bơm mini dựa trên giá trị độ ẩm và ngưỡng cài đặt.
Kết nối MQTT: Dữ liệu độ ẩm được gửi đến một broker MQTT online để hiển thị trên dashboard. Đồng thời, dashboard cho phép điều khiển thủ công máy bơm.
Giao diện dashboard: Sử dụng Node-RED để hiển thị giá trị độ ẩm, trạng thái máy bơm và cho phép điều khiển từ xa.

3. Sơ đồ khối dự kiến

