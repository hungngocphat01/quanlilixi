# Quản lí lì xì
## Code khá thô bằng C++

Tự nhiên lục github phát hiện ra cái quần này viết từ hồi sinh viên năm nhất nên public ra cho vui vậy. Thực tế nó chả làm được cái quái gì ra hồn sất 🐧

## I. Hướng dẫn cài đặt
* Đầu tiên tải source code tại ở [đây]() *(link cho vui, chưa hoàn tất nên chưa up code)*.
### 1. Trên máy tính
* Ném vào Visual Studio, Code::Blocks hoặc compile trên command line bằng gcc, ..., nói chung là bất cứ cái quần què gì có thể compile được C++. Mà chắc test cho vui vì chả ai quản lí tiền lì xì bằng máy tính. Không lẽ đi chơi Tết mà phải vác cái laptop đi để tính tiền :) 
### 2. Trên Android
* Tải Cxxdroid về từ Play Store. Mở file source code lên bằng cách nhấn vào biểu tượng thư mục ở trên góc phải, sau đó điều hướng đến và mở file source code vừa tải về.
* Nhấn vào nút có biểu tượng **Play** ở góc dưới bên phải để chạy chương trình. 
* Bạn chỉ cần mở file ở lần chạy đầu tiên vì những lần chạy sau Cxxdroid sẽ tự mở file gần nhất lên cho các bạn. Các bạn chỉ việc nhấn nút **Play** để chạy code.
* Không khuyến khích sử dụng Dcoder vì tốc độ thực thi chậm.
### 3. Trên iOS
* Nah, mình không dùng iOS. Các bạn tự nghiên cứu đi <(")
## II. Hướng dẫn sử dụng
### 1. Cấu trúc lưu trữ dữ liệu của chương trình
* Chương trình lưu trữ từng entry của người dùng nhập vào bằng một kiểu dữ liệu cấu trúc tự định nghĩa.

    ```c++
    struct nguoi{
        string ten;
        int sotien;
        string danhmuc;
        int mung;
    }
    ```
* Trong đó:
    * **ten**: tên của người lì xì.
    * **sotien**: số tiền được lì xì.
    * **danhmuc**: danh mục (xếp loại) người đó. Vd: nhà nội, nhà ngoại, bạn ba, bạn mẹ, ... Cái này chương trình sẽ để user tự định nghĩa.
    * **mung**: mùng (mồng) nhận được tiền lì xì từ người đó.
* Những thông tin này sẽ được lưu trong một file có tên mặc định là *data.txt*.
* Một đối tượng **nguoi** sẽ được lưu trữ trên 4 dòng, tương ứng với 4 thuộc tính của đối tượng đó.
    * Giả sử, ta có 2 người sau:
        * Nguyen Van A, lì xì 100k, là người bên họ nội, lì xì vào mùng 1.
        * Bui Van B, lì xì 200k, là người bên họ ngoại, lì xì vào mùng 2.
    * Chương trình sẽ lưu dưới cấu trúc như sau:

    ```
    Nguyen Van A
    100
    Noi
    1
    Bui Van B
    200
    Ngoai
    2
    ```
* Khi chạy lên, chương trình sẽ đọc tập tin *data.txt* vào một mảng động.

    ```c++
    vector<nguoi> danhsach;
    ```
* Mọi thao tác liệt kê, lọc dữ liệu, ghi, chỉnh sửa sẽ được thực hiện ngay trên mảng này trước khi được ghi xuống tập tin ở cuối mỗi quá trình xử lí dữ liệu.
* Thông tin người dùng nhập vào sẽ được tự động chuẩn hóa trước khi lưu vào mảng này, và sau đó ghi xuống tập tin (không có kí tự khoảng trắng ở đầu hay cuối chuỗi, mỗi từ cách nhau một khoảng trắng, kí tự đầu tiên của một từ là in hoa, còn lại in thường).

### 2. Khởi tạo tập tin mới
* Khi chạy chương trình lên, chương trình sẽ kiểm tra file *data.txt* đã được khởi tạo hay chưa. Nếu chưa, chương trình sẽ hỏi người dùng liệu có muốn chương trình tự khởi tạo hay không.
* Nhập số 0 nếu không muốn và 1 nếu có.

    ```
    Chuong trinh quan li tien li xi
    By Ngoc Phat
    Version 1.5
    OS: Windows
    =======================================================
    Loi doc file. Vui long kiem tra lai!
    Tao tap tin moi? (0/1) =>
    ```
### 3. Menu chính của chương trình
* Cách sử dụng khá đơn giản. Muốn chọn tính năng nào thì ta chọn tính năng đó. Thế thôi.

    ```
    Chuong trinh quan li tien li xi
    By Ngoc Phat
    Version 1.5
    OS: Windows
    =======================================================
    Hay chon 1 trong cac tinh nang sau:
    1. In danh sach thong ke
    2. Nhap thong tin moi
    3. Chinh sua danh sach
    0. Thoat khoi chuong trinh
    =>
    ```
### 4. Nhập dữ liệu cho chương trình
* Chọn số 2 ở menu chính để nhập dữ liệu cho chương trình.
* Chương trình sẽ yêu cầu nhập danh mục và mùng trước. Bởi vì, tại một thời điểm ta thường chỉ thăm hoặc nhà nội, hoặc nhà ngoại, ..., nên chương trình sẽ bắt nhập danh mục trước để tránh phải nhập nhiều lần gây phiền phức. Tương tự với mùng.
* Trong ví dụ dưới đây, danh mục được nhập là "Noi" (nội).
* Chương trình sẽ tiến hành chuẩn hóa chuỗi khi ghi dữ liệu nên bạn không cần phải lo về vấn đề này.

    ```
    Nhap danh muc: Ngoai
    Nhap mung: 1
    ```
* Sau đó đến bước nhập thông tin cho từng người. Khá đơn giản, bạn chỉ việc nhập tên và số tiền người đó lì xì cho bạn thôi. Lưu ý là nhập không dấu nhé.
* Để kết thúc, nhập tên là // (2 dấu xẹt "sắc"), chương trình sẽ thoát.

    ```
    Nhap ten la // de ket thuc

    Nhap ten: Co A
    Nhap so tien: 100

    Nhap ten: Co B
    Nhap so tien: 120

    Nhap ten: Bac C
    Nhap so tien: 200

    Nhap ten: Bac F
    Nhap so tien: 100

    Nhap ten: Co E
    Nhap so tien: 90

    Nhap ten: // <- Kết thúc
    ```
* Chương trình sẽ hỏi bạn có muốn tiếp tục hay không. Nếu bạn chọn có (1), chương trình sẽ trở lại menu chính, còn không (0) thì chương trình sẽ thoát.
* Dù chọn có hay không, dữ liệu vẫn sẽ được ghi xuống tập tin.

    ```
    Tiep tuc? (0/1) =>
    ```

### 5. Xuất danh sách thống kê
* Chọn 1 ở menu chính để xuất danh sách thống kê.
* Chương trình hỗ trợ lọc dữ liệu khi xuất danh sách, bao gồm lọc theo danh mục và lọc theo mùng.

    ```
    Chuong trinh quan li tien li xi
    By Ngoc Phat
    Version 1.5
    OS: Windows
    =======================================================
    Dieu kien loc danh sach:
    0 = Khong loc
    1 = Loc theo danh muc
    2 = Loc theo mung co dinh
    3 = Loc theo khoang mung
    =>
    ```
* Chọn 0 để in toàn bộ danh sách thống kê
* Chọn 1 để lọc theo danh mục. Sau khi chọn chương trình sẽ bắt nhập danh mục vào.
* Chọn 2 để lọc theo 1 mùng cố định. Hữu ích để bạn xem thử bạn "kiếm" được bao nhiêu tiền trong 1 ngày nào đó. Vd như mùng 1, mùng 2, ... Lưu ý chỉ nhập số nguyên dương (bạn vẫn có thể nhập số âm vì kiểu dữ liệu là ```int``` nhưng well, chả có cái gọi là mùng 0 hay mùng số âm).
* Chọn 3 để lọc theo khoảng mùng. Hữu ích để bạn xem thử trong vòng từ ngày nào đó đến ngày nào đó, bạn "kiếm" được bao nhiêu tiền. Vd như từ mùng 1 đến mùng 2, từ mùng 2 đến mùng 3, ...
    * Dữ liệu nhập vào là 2 số nguyên dương biểu thị cho mùng bắt đầu và mùng kết thúc, cách nhau 1 khoảng trắng.

    ```
    Chuong trinh quan li tien li xi
    By Ngoc Phat
    Version 1.5
    OS: Windows
    =======================================================

    STT               Ten     Stien      Dmuc   Mung
    --------------------------------------------------
    1                Co A       100       Noi      1
    2                Co B       120       Noi      1
    3             Duong C       200       Noi      1
    4               Bac F       100       Noi      1
    5                Co E        90       Noi      1
    --------------------------------------------------
                    Tong:       610

    =======================================================
    Tiep tuc? (0/1) =>
    ```

