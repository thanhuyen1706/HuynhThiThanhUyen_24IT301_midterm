**BÁO CÁO MIDTERM PROJECT**

**XÂY DỰNG CHƯƠNG TRÌNH my\_ls**

Môn học: Lập trình hệ thống    

Sinh viên: Huỳnh Thị Thanh Uyên\
Mã sinh viên: 24IT301    

Kho mã nguồn: https://github.com/thanhuyen1706/HuynhThiThanhUyen\_24IT301\_midterm
# **1. Giới thiệu**
Đề tài xây dựng chương trình my\_ls bằng ngôn ngữ C, mô phỏng một phần chức năng của lệnh ls trên hệ điều hành UNIX/Linux. Chương trình đọc tham số dòng lệnh, phân tích các tùy chọn và liệt kê nội dung thư mục được chỉ định. Mục tiêu là thực hành thao tác hệ thống tệp, sử dụng thư viện chuẩn/POSIX, tổ chức mã nguồn thành nhiều tệp và biên dịch bằng Makefile.
# **2. Cấu trúc dự án**
- src/main.c: hàm main, gọi parse\_options() để phân tích tham số; nếu không có đường dẫn thì liệt kê thư mục hiện hành “.”, nếu có thì lần lượt xử lý các đối số đường dẫn.
- src/ls.c: cài đặt parse\_options() và list\_directory(). Hàm phân tích tùy chọn và hàm duyệt thư mục được tách riêng để dễ theo dõi.
- include/ls.h: tệp tiêu đề dùng để khai báo cấu trúc Options và nguyên mẫu hàm dùng chung giữa các mô-đun.
- Makefile: dùng gcc, bật cảnh báo với -Wall, tìm tệp tiêu đề qua -Iinclude, biên dịch src/main.c và src/ls.c thành chương trình my\_ls; có mục tiêu clean để xóa tệp đối tượng và chương trình đã biên dịch.
# **3. Các tính năng đã triển khai**
- Liệt kê thư mục mặc định: chạy ./my\_ls không có đường dẫn sẽ dùng “.”, tức thư mục làm việc hiện tại.
- Xử lý đường dẫn: nhận một hoặc nhiều đối số đường dẫn sau phần tùy chọn. Khi có nhiều đối số, chương trình in tên đường dẫn trước từng phần kết quả.
- Tùy chọn -a: bật show\_all để hiển thị cả các mục có tên bắt đầu bằng dấu chấm; mặc định, các mục này bị bỏ qua.
- Phân tích tùy chọn: hỗ trợ nhận diện các ký tự -a, -l, -R, -r và -t, kể cả khi ghép trong cùng một đối số, ví dụ -al.


# **4. Mô tả thuật toán**
## **4.1. Thuật toán chính trong main.c**
1. Bắt đầu chương trình và nhận argc, argv từ dòng lệnh.
1. Khởi tạo cấu trúc Options và gọi parse\_options() để phân tích các tùy chọn; hàm trả về vị trí đối số đường dẫn đầu tiên.
1. Nếu không còn đối số đường dẫn, gọi list\_directory(".", &opts) để liệt kê thư mục hiện hành.
1. Nếu có đường dẫn, lặp qua từng đường dẫn. Khi có nhiều đường dẫn, in nhãn đường dẫn rồi gọi list\_directory() cho từng mục; in dòng trống phân cách kết quả.
1. Kết thúc chương trình.
## **4.2. Thuật toán phân tích tùy chọn**
1. Đặt các cờ show\_all, long\_format, recursive, reverse và sort\_time về 0.
1. Duyệt các đối số từ argv[1]. Nếu đối số bắt đầu bằng '-' và không phải chuỗi chỉ có '-', duyệt từng ký tự phía sau dấu '-'.
1. Nếu ký tự là a, l, R, r hoặc t thì bật cờ tương ứng. Nếu gặp ký tự khác, in thông báo “invalid option” ra stderr và thoát với mã 1.
1. Khi gặp đối số không phải tùy chọn, dừng phân tích và xem vị trí đó là đường dẫn đầu tiên.
## **4.3. Thuật toán liệt kê thư mục**
1. Gọi opendir(path) để mở thư mục. Nếu mở thất bại, dùng perror("my\_ls") in lỗi và quay về.
1. Đọc lần lượt từng mục bằng readdir(dir).
1. Nếu tùy chọn -a chưa bật và tên mục bắt đầu bằng '.', bỏ qua mục đó; ngược lại, in tên mục theo sau bởi khoảng trắng.
1. Sau khi đọc hết mục, in ký tự xuống dòng và gọi closedir(dir) để đóng thư mục.
## **4.4. Giả mã tổng quát**
ĐỌC argc, argv

parse\_options(...) → opts, vị\_trí\_đường\_dẫn

NẾU không có đường dẫn: list\_directory('.', opts)

NGƯỢC LẠI: với mỗi đường dẫn, gọi list\_directory(đường\_dẫn, opts)

Trong list\_directory: opendir → readdir từng mục → lọc mục ẩn theo -a → in tên → closedir

KẾT THÚC


# **5. Xử lý lỗi và định dạng kết quả**
## **5.1. Xử lý lỗi**
Khi opendir() không mở được đường dẫn, chương trình gọi perror("my\_ls") để in thông báo lỗi hệ thống, chẳng hạn đường dẫn không tồn tại hoặc không đủ quyền truy cập. Khi gặp tùy chọn không được nhận diện, parse\_options() in thông báo “my\_ls: invalid option” ra luồng lỗi chuẩn và kết thúc với mã 1.
## **5.2. Định dạng đầu ra**
Tên các mục được in trên cùng dòng, mỗi tên cách nhau bằng hai khoảng trắng, sau đó xuống dòng khi kết thúc một thư mục. Nếu truyền nhiều đường dẫn, chương trình in tên đường dẫn làm tiêu đề trước kết quả của từng đường dẫn và chèn dòng trống giữa các nhóm.
# **6. Giới hạn hiện tại cần lưu ý**
Mã nguồn hiện phân tích các cờ -l, -R, -r và -t, nhưng hàm list\_directory() đang hiển thị tên mục theo dạng cơ bản; các cờ này chưa được áp dụng để định dạng chi tiết, duyệt đệ quy, đảo thứ tự hoặc sắp xếp theo thời gian. Vì vậy, báo cáo ghi nhận chúng là tùy chọn đã được nhận diện trong bước phân tích, không khẳng định chức năng tương ứng đã hoàn chỉnh.

Chương trình hiện xử lý đường dẫn đầu vào thông qua opendir(), do đó phù hợp với đường dẫn thư mục; đường dẫn trỏ trực tiếp đến tệp thông thường sẽ không được hiển thị như lệnh ls đầy đủ. Việc sắp xếp kết quả và kiểm tra đầy đủ các trường hợp biên có thể được bổ sung trong các phiên bản sau.
# **7. Cách biên dịch và chạy**
Mở terminal tại thư mục gốc của kho mã nguồn và chạy:

make

./my\_ls

./my\_ls -a

./my\_ls src

./my\_ls -a src include

make clean

Lệnh make biên dịch chương trình thành my\_ls theo cấu hình trong Makefile. Lệnh make clean xóa các tệp .o và chương trình my\_ls đã tạo.


# **8. Kiểm thử đề xuất**

|**Lệnh kiểm thử**|**Mục đích**|**Kết quả mong đợi**|
| :- | :- | :- |
|**./my\_ls**|Liệt kê thư mục hiện hành|In các mục không bắt đầu bằng dấu chấm.|
|**./my\_ls -a**|Hiển thị mục ẩn|Có cả các mục bắt đầu bằng dấu chấm.|
|**./my\_ls src include**|Nhiều đường dẫn|In tiêu đề từng đường dẫn và kết quả tương ứng.|
|**./my\_ls -z**|Tùy chọn sai|In thông báo tùy chọn không hợp lệ và thoát mã 1.|
|**./my\_ls no\_such\_dir**|Đường dẫn không tồn tại|In thông báo lỗi từ perror.|
# **9. Kết luận**
Dự án my\_ls đã xây dựng được nền tảng của một công cụ liệt kê thư mục: tách mô-đun phân tích tùy chọn và xử lý thư mục, sử dụng opendir()/readdir()/closedir(), hỗ trợ chế độ hiển thị mục ẩn và báo lỗi cơ bản. Makefile giúp tự động hóa quá trình biên dịch và dọn dẹp tệp sinh ra. Các bước phát triển tiếp theo gồm triển khai thực sự -l, -R, -r, -t; bổ sung sắp xếp, hỗ trợ đường dẫn là tệp thường và mở rộng kiểm thử.

Kho mã nguồn: https://github.com/thanhuyen1706/HuynhThiThanhUyen\_24IT301\_midterm
Báo cáo Midterm – my\_ls | Trang Báo cáo Midterm – my\_ls | Trang 1
