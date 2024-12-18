#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <windows.h>
#include "HeThong.h"
#include "linkedlist.h"
#include "Book.h"
#include "customer.h"
#include "condition.h"
#include <windows.h>
using namespace std;
static int count = 0;
bool LinkedList::isEmpty()
{
    if (this->bookHead == NULL)
        return true;
    return false;
}
LinkedList ::LinkedList()
{
    bookHead = NULL;
    customerHead = NULL;
}
LinkedList ::~LinkedList()
{
    // Clean up Book list
    BookNode *bookCurrent = bookHead;
    while (bookCurrent != NULL)
    {
        BookNode *bookNext = bookCurrent->next;
        delete bookCurrent;
        bookCurrent = bookNext;
    }

    // Clean up Customer list
    CustomerNode *customerCurrent = customerHead;
    while (customerCurrent != NULL)
    {
        CustomerNode *customerNext = customerCurrent->next;
        delete customerCurrent;
        customerCurrent = customerNext;
    }
}
int LinkedList::length_Of_List()
{
    int lenght = 0;
    BookNode *temp = this->bookHead;
    for (temp; temp != NULL; temp = temp->next)
    {
        ++lenght;
    }
    return lenght;
}
int lengthOfCustomerlist(CustomerNode *Customer)
{
    int length = 0;
    int sum;
    while (Customer != nullptr)
    {
        ++length;
        Customer = Customer->next;
    }
    if (length % 10 == 0)
    {
        sum = length / 10;
    }
    else
    {
        sum = length / 10 + 1;
    }
    return sum;
}
void LinkedList::outputCustomer(int x, int y, const Customer &customer)
{
    gotoXY(x + 10, y + 1);
    cout << customer.getMaKH();
    gotoXY(x + 30, y + 1);
    cout << customer.getHoTen();
    gotoXY(x + 60, y + 1);
    cout << customer.getDia_chi();
    gotoXY(x + 85, y + 1);
    cout << customer.getSdtKH();
    gotoXY(x + 104, y + 1);
    cout << customer.getSo_tien_da_mua();
}
void LinkedList::readCustomer(const string &fileName)
{
    ifstream infile(fileName);
    if (!infile.is_open())
    {
        cout << "Could not open the file " << fileName << endl;
        return;
    }

    int n; // Số lượng khách hàng
    infile >> n;
    infile.ignore(); // Bỏ qua ký tự xuống dòng sau số lượng khách hàng
    CustomerNode *temp = nullptr;
    for (int i = 0; i < n; ++i)
    {
        CustomerNode *newNode = new CustomerNode();

        // Đọc dữ liệu từ file theo định dạng
        getline(infile, newNode->data.Ma_KH, '|');
        getline(infile, newNode->data.ho_ten, '|');
        getline(infile, newNode->data.dia_chi, '|');
        getline(infile, newNode->data.sdt_KH, '|');
        infile >> newNode->data.so_tien_da_mua;
        infile.ignore(); // Bỏ qua ký tự xuống dòng sau số tiền

        newNode->next = nullptr;
        // Nếu danh sách rỗng, node mới trở thành đầu danh sách
        if (customerHead == nullptr)
        {
            customerHead = newNode;
        }
        else
        {
            // Liên kết node mới vào cuối danh sách
            temp->next = newNode;
        }
        temp = newNode;
    }
    infile.close(); // Đóng file
}
void LinkedList::displayCustomer()
{
    CustomerNode *temp = customerHead;
    int sum = lengthOfCustomerlist(temp);
    CustomerNode **first = new CustomerNode *[sum]; // Lưu node đầu trang
    int a = 0, page = 1, tam = 0;
    system("cls");
    const wchar_t *name = L"[ THÔNG TIN KHÁCH HÀNG ]";
    writeString(2, 2, name);
    menuDisplay2(2, 4, 23, page, sum); // In tiêu đề trang sách
    while (tam == 0)
    {
        while (temp != NULL)
        {
            for (int i = 1; i <= 10; i++)
            {
                if (temp != NULL)
                {
                    a = a + 2;
                    outputCustomer(2, a + 4, temp->data);
                    if (a == 2)
                    {
                        first[page] = temp;
                    }
                    temp = temp->next;
                }
            }
            if (setKeyBoard() == 4 && temp != NULL) // ấn qua phải
            {
                system("cls");
                writeString(2, 2, name);
                page++;
                menuDisplay(2, 4, 23, page, sum);
                a = 0;
            }
            else if (setKeyBoard() == 3 && temp != NULL && page - 1 > 0) // ấn qua trái
            {
                system("cls");
                writeString(2, 2, name);
                page--;
                menuDisplay(2, 4, 23, page, sum);
                temp = first[page];
                a = 0;
            }
            else if (setKeyBoard() == 4 && temp == NULL)
            {
                break;
            } // ấn qua phải ở trang cuối
            else if (setKeyBoard() == 3 && page - 1 <= 0)
            {
                break;
            } // ấn qua trái ở trang đầu
            else if (setKeyBoard() == 5)
            {
                system("cls");
                tam = 1;
                break;
            } // thoát
            else if (setKeyBoard() == 1 || setKeyBoard() == 2)
            {
                a = 0;
                system("cls");
                writeString(2, 2, name);
                menuDisplay(2, 4, 23, page, sum);
                temp = first[page];
            }
        }
        if (tam == 0)
        {
            int thu = 0;
            while (true)
            {
                if (setKeyBoard() == 5)
                {
                    system("cls");
                    tam = 1;
                    break;
                }
                else if (setKeyBoard() == 3 && page == sum && page != 1)
                {
                    system("cls");
                    writeString(2, 2, name);
                    menuDisplay(2, 4, 23, sum - 1, sum);
                    page--;
                    temp = first[sum - 1];
                    a = 0;
                    break;
                }
                else if (setKeyBoard() == 3 && page == 1 && page != sum)
                {
                    while (true)
                    {
                        if (setKeyBoard() == 4)
                        {
                            system("cls");
                            writeString(2, 2, name);
                            menuDisplay(2, 4, 23, 2, sum);
                            page = 2;
                            if (count == 0)
                            {
                                thu = 1;
                            }
                            else
                                temp = first[2];
                            a = 0;
                            break;
                        }
                        else if (setKeyBoard() == 5)
                        {
                            system("cls");
                            tam = 1;
                            break;
                        }
                    }
                }
                break;
            }
            if (thu == 1)
            {
                continue;
            }
        }
    }
}
// read
//  Tìm kiếm theo tên sách,thể loại,tên,tác giả
void LinkedList::outputBook(int x, int y, const Book &book)
{
    gotoXY(x + 5, y + 1);
    cout << book.getMa_Sach();
    gotoXY(x + 25, y + 1);
    cout << book.getTen_sach();
    gotoXY(x + 60, y + 1);
    cout << book.getThe_loai();
    gotoXY(x + 85, y + 1);
    cout << book.getTac_gia();
    gotoXY(x + 104, y + 1);
    cout << book.getNam_xuat_ban();
    gotoXY(x + 125, y + 1);
    cout << book.getSo_luong();
    gotoXY(x + 136, y + 1);
    cout << book.getGia_ban();
}
// Định nghĩa hàm đọc sách từ file
void LinkedList::readBook(const string &fileName)
{
    ifstream infile(fileName);
    if (!infile.is_open())
    {
        cout << "Could not open the file " << fileName << endl;
        return;
    }

    int n; // Số lượng sách
    infile >> n;
    infile.ignore(); // Bỏ qua ký tự xuống dòng sau số lượng sách
    BookNode *temp = nullptr;
    for (int i = 0; i < n; ++i)
    {
        BookNode *newNode = new BookNode();
        count++;
        // Sử dụng getline để lấy mã sách
        getline(infile, newNode->data.Ma_Sach, '|');

        getline(infile, newNode->data.ten_sach, '|');
        getline(infile, newNode->data.the_loai, '|');
        getline(infile, newNode->data.tac_gia, '|');
        infile >> newNode->data.so_luong;
        infile.ignore(1, '|'); // Bỏ qua ký tự '|' sau so_luong
        infile >> newNode->data.gia_ban;
        infile.ignore(1, '|');                // Bỏ qua ký tự '|' sau gia_ban
        infile >> newNode->data.nam_xuat_ban; // Đọc năm xuất bản
        infile.ignore();                      // Bỏ qua ký tự xuống dòng

        newNode->next = NULL;

        if (bookHead == NULL)
        {
            // Nếu danh sách rỗng, node mới trở thành đầu danh sách
            bookHead = newNode;
        }
        else
        {
            // Liên kết node mới vào cuối danh sách
            temp->next = newNode;
        }

        temp = newNode; // Cập nhật temp để trỏ đến node cuối
    }

    infile.close(); // Đóng file
}
int length(BookNode *book)
{
    int length = 0;
    int sum;
    while (book != nullptr)
    {
        ++length;
        book = book->next;
    }
    if (length % 10 == 0)
    {
        sum = length / 10;
    }
    else
    {
        sum = length / 10 + 1;
    }
    return sum;
}
int lengthOfCustomer(CustomerNode *Customer)
{
    int length = 0;
    int sum;
    while (Customer != nullptr)
    {
        ++length;
        Customer = Customer->next;
    }
    if (length % 10 == 0)
    {
        sum = length / 10;
    }
    else
    {
        sum = length / 10 + 1;
    }
    return sum;
}
void LinkedList::ShowAllBook(int i, BookNode *b)
{
    if (i == 1)
    {
        b = this->bookHead;
    }
    BookNode *temp = b;
    int sum = length(temp);
    BookNode **first = new BookNode *[sum]; // Lưu node đầu trang
    int a = 0, page = 1, tam = 0;
    system("cls");
    const wchar_t *name;
    if (i == 1)
    {
        name = L"[ THÔNG TIN SÁCH ]";
    }
    else if (i == 4)
    {
        name = L"[ Sắp xếp tăng dần theo giá bán ]";
    }
    else if (i == 5)
    {
        name = L"[ Sắp xếp giảm dần theo giá bán ]";
    }
    else if (i == 2)
    {
        name = L"[ Sắp xếp tăng dần theo số lượng ]";
    }
    else if (i == 3)
    {
        name = L"[ Sắp xếp giảm dần theo số lượng ]";
    }
    else if (i == 6)
    {
        name = L"[ Sắp xếp tăng dần theo năm xuất bản ]";
    }
    else if (i == 7)
    {
        name = L"[ Sắp xếp giảm dần theo năm xuất bản ]";
    }
    writeString(2, 2, name);
    menuDisplay(2, 4, 23, page, sum); // In tiêu đề trang sách
    while (tam == 0)
    {
        while (temp != NULL)
        {
            for (int i = 1; i <= 10; i++)
            {
                if (temp != NULL)
                {
                    a = a + 2;
                    outputBook(2, a + 4, temp->data);
                    if (a == 2)
                    {
                        first[page] = temp;
                    }
                    temp = temp->next;
                }
            }
            if (setKeyBoard() == 4 && temp != NULL) // ấn qua phải
            {
                system("cls");
                writeString(2, 2, name);
                page++;
                menuDisplay(2, 4, 23, page, sum);
                a = 0;
            }
            else if (setKeyBoard() == 3 && temp != NULL && page - 1 > 0) // ấn qua trái
            {
                system("cls");
                writeString(2, 2, name);
                page--;
                menuDisplay(2, 4, 23, page, sum);
                temp = first[page];
                a = 0;
            }
            else if (setKeyBoard() == 4 && temp == NULL)
            {
                break;
            } // ấn qua phải ở trang cuối
            else if (setKeyBoard() == 3 && page - 1 <= 0)
            {
                break;
            } // ấn qua trái ở trang đầu
            else if (setKeyBoard() == 5)
            {
                system("cls");
                tam = 1;
                break;
            } // thoát
            else if (setKeyBoard() == 1 || setKeyBoard() == 2)
            {
                a = 0;
                system("cls");
                writeString(2, 2, name);
                menuDisplay(2, 4, 23, page, sum);
                temp = first[page];
            }
        }
        if (tam == 0)
        {
            int thu = 0;
            while (true)
            {
                if (setKeyBoard() == 5)
                {
                    system("cls");
                    tam = 1;
                    break;
                }
                else if (setKeyBoard() == 3 && page == sum && page != 1)
                {
                    system("cls");
                    writeString(2, 2, name);
                    menuDisplay(2, 4, 23, sum - 1, sum);
                    page--;
                    temp = first[sum - 1];
                    a = 0;
                    break;
                }
                else if (setKeyBoard() == 3 && page == 1 && page != sum)
                {
                    while (true)
                    {
                        if (setKeyBoard() == 4)
                        {
                            system("cls");
                            writeString(2, 2, name);
                            menuDisplay(2, 4, 23, 2, sum);
                            page = 2;
                            if (count == 0)
                            {
                                thu = 1;
                            }
                            else
                                temp = first[2];
                            a = 0;
                            break;
                        }
                        else if (setKeyBoard() == 5)
                        {
                            system("cls");
                            tam = 1;
                            break;
                        }
                    }
                }
                break;
            }
            if (thu == 1)
            {
                continue;
            }
        }
    }
}
//--------------------------------------SORT BOOK-------------------------------//
bool TD(int a, int b)
{
    return a > b; // Sắp xếp giảm dần
}

bool GD(int a, int b)
{
    return a < b; // Sắp xếp tăng dần
}

void Swap(Book &a, Book &b)
{
    Book temp = a;
    a = b;
    b = temp;
}
void LinkedList::Sort(bool (*q)(int, int), int k, BookNode *b)
{

    for (BookNode *i = b; i != nullptr; i = i->next)
    {
        for (BookNode *j = i->next; j != nullptr; j = j->next)
        {
            // So sánh theo thuộc tính k với hàm con trỏ q
            switch (k)
            {
            case 1: // Sắp xếp theo Giá bán
                if ((*q)(i->data.getSo_luong(), j->data.getSo_luong()))
                {
                    Swap(i->data, j->data);
                }
                break;
            case 2: // Sắp xếp theo Số lượng
                if ((*q)(i->data.getGia_ban(), j->data.getGia_ban()))
                {
                    Swap(i->data, j->data);
                }
                break;
            case 3: // Sắp xếp theo Năm xuất bản
                if ((*q)(i->data.getNam_xuat_ban(), j->data.getNam_xuat_ban()))
                {
                    Swap(i->data, j->data);
                }
                break;
            }
        }
    }
}
BookNode *LinkedList::CloneList(BookNode *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    BookNode *newHead = new BookNode(head->data);
    BookNode *current = newHead;
    BookNode *original = head->next;
    while (original != nullptr)
    {
        current->next = new BookNode(original->data);
        current = current->next;
        original = original->next;
    }

    return newHead;
}
void LinkedList::DeleteList(BookNode *head)
{
    while (head != nullptr)
    {
        BookNode *temp = head;
        head = head->next;
        delete temp;
    }
}
void LinkedList::Sort_BookUporDown(int i, int t)
{
    BookNode *temp = CloneList(bookHead); // Use a temporary pointer to avoid modifying bookHead
    int sum = length(temp);               // Not sure if 'sum' is needed, but it's left here as in your code
    system("cls");                        // Clear screen once before sorting and displaying
    // Check which sorting criteria the user wants (price, quantity, or year)
    if (i == 1)
    {
        if (t == 0)
        {
            Sort(TD, 1, temp);    // Sort by price descending
            ShowAllBook(2, temp); // Display sorted result
        }
        else if (t == 1)
        {
            Sort(GD, 1, temp);    // Sort by price ascending
            ShowAllBook(3, temp); // Display sorted result
        }
    }
    else if (i == 2)
    {
        if (t == 0)
        {
            Sort(TD, 2, temp);    // Sort by quantity descending
            ShowAllBook(4, temp); // Display sorted result
        }
        else if (t == 1)
        {
            Sort(GD, 2, temp);    // Sort by quantity ascending
            ShowAllBook(5, temp); // Display sorted result
        }
    }
    else if (i == 3)
    {
        if (t == 0)
        {
            Sort(TD, 3, temp);    // Sort by year descending
            ShowAllBook(6, temp); // Display sorted result
        }
        else if (t == 1)
        {
            Sort(GD, 3, temp);    // Sort by year ascending
            ShowAllBook(7, temp); // Display sorted result
        }
    }
    DeleteList(temp);
}
//------------------------------SEARCH BOOK----------------------------------------------//
string getinput()
{
    string name;
    char ch;
    while ((ch = _getch()) != '\r')
    { // Đọc cho đến khi nhấn Enter ('\r')
        if (ch == '\b' && name.length() > 0)
        { // Xử lý phím Backspace
            wcout << "\b \b";
            name.pop_back();
        }
        else if (ch != '\b')
        {                // Nếu không phải Backspace, thêm vào mật khẩu
            wcout << ch; // Hiển thị * thay vì ký tự thực
            name.push_back(ch);
        }
    }
    return name;
}
void LinkedList::search_book(int x)
{
    int sum;
    string search;
    BookNode *temp = nullptr;
    // const wchar_t* name = L"[ THÔNG TIN SÁCH ]";

    const wchar_t *name;
    if (x == 1)
        name = L"[ Nhập tên sách ]";
    else if (x == 2)
        name = L"[ Nhập tên thể loại ]";
    else if (x == 3)
        name = L"[ Nhập tên tác giả: ]";
    else if (x == 4)
        name = L"[ Nhập năm xuất bản ]";
    if (x == 1)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->read(search, x);

            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = length(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    else if (x == 2)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->read(search, x);

            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = length(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    else if (x == 3)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->read(search, x);

            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = length(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    else if (x == 4)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->read(search, x);

            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = length(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    int tam = 0;
    int currentPage = 0;
    const int itemsPerPage = 5;

    while (tam != 5)
    {
        int length = 0;
        BookNode *current = temp; // Dùng con trỏ khác để duyệt danh sách

        // Tính độ dài của danh sách
        for (; current != NULL; current = current->next)
        {
            ++length;
        }

        // Kiểm tra nếu length > 5 mới thực hiện phân trang
        if (length > 5)
        {
            // Vòng lặp phân trang
            while (true)
            {
                system("cls"); // Xóa màn hình trước khi hiển thị lại dữ liệu mới
                writeString(2, 2, name);
                menuTable(2, 3, 30, 2);
                gotoXY(4, 4);
                cout << search;

                // Tính tổng số trang
                int totalPages = (length + itemsPerPage - 1) / itemsPerPage;

                // Đặt con trỏ về đầu danh sách và đến đúng trang
                current = temp;
                for (int i = 0; i < currentPage * itemsPerPage && current != NULL; ++i)
                {
                    current = current->next;
                }

                // Hiển thị các sách trong trang hiện tại
                writeString(2, 7, L"[ THÔNG TIN SẢN PHẨM ]");
                bangsanpham(2, 8, itemsPerPage + 5);

                int a = 8;
                for (int i = 1; i <= itemsPerPage && current != NULL; ++i)
                {
                    a += 2;
                    outputBook(2, a, current->data);
                    current = current->next;
                }

                // Hiển thị điều hướng nếu có nhiều hơn 1 trang
                writeString(2, 2, name);
                menuTable(2, 3, 30, 2);
                gotoXY(4, 4);
                cout << search;
                gotoXY(100, 6);
                cout << "Trang " << currentPage + 1 << " / " << totalPages;
                writeString(2, 25, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!");
                // Nhận phím từ người dùng
                tam = setKeyBoard();

                // Điều hướng trái/phải qua các trang
                if (tam == 4 && currentPage < totalPages - 1)
                {
                    currentPage++; // Sang trang tiếp theo
                }
                else if (tam == 3 && currentPage > 0)
                {
                    currentPage--; // Quay lại trang trước
                }
                else if (tam == 5)
                {          // Nếu nhấn ESC (giá trị 27)
                    break; // Thoát khỏi vòng lặp phân trang
                }
            }
        }

        else
        {
            // Nếu danh sách <= 5, hiển thị bình thường
            current = temp;
            writeString(2, 7, L"[ THÔNG TIN SẢN PHẨM ]");
            bangsanpham(2, 8, length + 5);

            int a = 8;
            for (int i = 1; i <= length && current != NULL; ++i)
            {
                a += 2;
                outputBook(2, a, current->data);
                current = current->next;
            }

            // Không cần phân trang, chỉ thoát khi người dùng nhấn phím
            tam = setKeyBoard();
            if (tam == 5)
            {
                return; // Thoát
            }
        }
    }
}
BookNode *LinkedList::read(string str, int i)
{
    BookNode *newBook = nullptr; // Head of the new list
    BookNode *tail = nullptr;    // Tail pointer to append nodes
    BookNode *temp = this->bookHead;
    int NXB;
    if (i == 4 || i == 0)
        NXB = stoi(str);

    // Iterate through the linked list
    while (temp != nullptr)
    {
        bool match = false; // Flag to track if a match is found

        // Determine what to search based on the value of i
        if (i == 1 && temp->data.ten_sach.find(str) != string::npos)
        {
            match = true; // Search in `ten_sach`
        }
        else if (i == 2 && temp->data.the_loai.find(str) != string::npos)
        {
            match = true; // Search in `the_loai`
        }
        else if (i == 3 && temp->data.tac_gia.find(str) != string::npos)
        {
            match = true; // Search in `tac_gia`
        }
        else if (i == 4 && temp->data.nam_xuat_ban == NXB)
        {
            match = true; // Search in `nam_xuat_ban`
        }

        // If a match is found, create a new node
        if (match)
        {
            BookNode *newNode = new BookNode;
            newNode->data = temp->data;
            newNode->next = nullptr;

            // Append to the list
            if (newBook == nullptr)
            {
                newBook = newNode; // Set as head
                tail = newNode;    // Set as tail
            }
            else
            {
                tail->next = newNode;
                tail = newNode; // Move the tail to the last node
            }
        }

        // Move to the next node
        temp = temp->next;
    }

    // If no matches are found, return nullptr
    if (newBook == nullptr)
    {
        return nullptr;
    }

    // Return the newBook list containing matched books
    return newBook;
}
//--------------------------------------- UPDATE BOOK-------------------------------------
int LinkedList::find_Node(const string &ma_sach)
{
    BookNode *temp = this->bookHead;
    int position = 1;

    for (temp; temp != NULL; temp = temp->next)
    {
        if (temp->data.Ma_Sach == ma_sach)
        {
            return position;
        }
        ++position;
    }

    return -1; // Trả về -1 nếu không tìm thấy
}
int LinkedList::find_Node(Book a)
{
    BookNode *temp = this->bookHead;
    int position = 0; // Bắt đầu từ vị trí 0 (hoặc 1 tùy theo cách bạn muốn)

    while (temp != NULL)
    {
        if (temp->data.getMa_Sach() == a.getMa_Sach())
        {
            return position; // Trả về vị trí hiện tại nếu tìm thấy sách
        }
        temp = temp->next;
        ++position; // Tăng vị trí sau mỗi lần duyệt qua node
    }

    return -1; // Trả về -1 nếu không tìm thấy sách
}
Book LinkedList::getNodeBook(int position)
{
    int k = 1;
    BookNode *temp = this->bookHead;
    while (k != position && temp != NULL)
    {
        temp = temp->next;
        ++k;
    }
    return temp->data;
}
bool LinkedList::delete_Node(Book a)
{
    int position = find_Node(a); // Tìm vị trí của node chứa sách cần xóa
    if (this->bookHead == NULL || position == -1)
    {
        return false; // Nếu danh sách rỗng hoặc không tìm thấy sách, trả về false
    }

    BookNode *temp = this->bookHead;

    // Trường hợp xóa node đầu tiên
    if (position == 0)
    {
        this->bookHead = this->bookHead->next; // Chuyển con trỏ đầu đến node tiếp theo
        delete temp;                           // Xóa node đầu tiên
    }
    else
    {
        // Duyệt danh sách đến vị trí node trước node cần xóa
        int k = 0;
        BookNode *prev = nullptr;
        while (temp != NULL && k != position)
        {
            prev = temp; // Lưu lại node trước đó
            temp = temp->next;
            ++k;
        }

        if (temp != NULL)
        {
            prev->next = temp->next; // Bỏ qua node cần xóa
            delete temp;             // Xóa node cần xóa
        }
    }

    return true; // Xóa thành công
}
bool LinkedList::UpdateBook()
{
    const wchar_t *name = L"[ Nhập Mã sách ]";
    writeString(10, 2, name);
    menuTable(27, 1, 30, 2);
    gotoXY(28, 2);
    string number = getinput();
    writeString(50, 7, L"[Click chuột ra ngoài bảng để kết thúc chỉnh sửa]");

    int position = find_Node(number); // Tìm vị trí sách
    if (position == -1)
    {
        writeString(55, 12, L"Không tồn tại sách có mã như trên.");
        return false;
    }

    // Lấy thông tin sách
    Book update = getNodeBook(position);

    // Xóa sách tại vị trí cũ
    // Hiển thị bảng sản phẩm để cập nhật
    bangsanpham(3, 8, 2);
    int x = 4, y = 10;
    writeString(x + 1, y - 4, L"[ THÔNG TIN SẢN PHẨM ]");

    // Hiển thị thông tin hiện tại của sách
    gotoXY(x + 10, y + 1);
    cout << update.getMa_Sach();
    gotoXY(x + 30, y + 1);
    cout << update.getTen_sach();
    gotoXY(x + 60, y + 1);
    cout << update.getThe_loai();
    gotoXY(x + 85, y + 1);
    cout << update.getTac_gia();
    gotoXY(x + 104, y + 1);
    cout << update.getNam_xuat_ban();
    gotoXY(x + 125, y + 1);
    cout << update.getSo_luong();
    gotoXY(x + 136, y + 1);
    cout << update.getGia_ban();
    delete_Node(update);
    // Bảng sửa sản phẩm
    writeString(x + 1, y + 6, L"[ SỬA SẢN PHẨM ]");
    bangsanpham(3, 18, 2);
    // Vòng lặp chỉnh sửa trực tiếp
    int x_click, y_click;
    string new_TenSach, new_TheLoai, new_TacGia;
    while (true)
    {
        gotoXY(x + 10, y + 12);
        cout << update.getMa_Sach();
        setClick(x_click, y_click);

        if (23 <= x_click && x_click <= 52 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Tên Sách
            while (true)
            {
                writeString(50, y + 6, L" Tên sách phải dài ít nhất 4 ký tự! ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 30, y + 12);
                new_TenSach = getinput(); // Dùng getline để nhập tên sách, có thể chứa khoảng trắng
                if (new_TenSach.length() >= 4 && isAlphaString(new_TenSach))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 30, y + 12, new_TenSach);
                }
            }
            update.SetTen_sach(new_TenSach);
            gotoXY(x + 30, y + 12);
            cout << new_TenSach;
        }
        else if (52 <= x_click && x_click <= 82 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Thể Loại
            while (true)
            {
                writeString(50, y + 6, L"[ Thể loại phải dài ít nhất 3 ký tự! ]");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 60, y + 12);
                new_TheLoai = getinput(); // Dùng getline để nhập thể loại
                if (new_TheLoai.length() >= 3 && isAlphaString(new_TheLoai))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 60, y + 4, new_TheLoai);
                }
            }
            update.SetThe_Loai(new_TheLoai);
            gotoXY(x + 60, y + 12);
            cout << new_TheLoai;
        }
        else if (82 <= x_click && x_click <= 102 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Tác Giả
            while (true)
            {
                writeString(50, y + 6, L"Tên tác giả phải dài ít nhất 4 ký tự!");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 85, y + 12);
                new_TacGia = getinput(); // Dùng getline để nhập tên tác giả
                if (new_TacGia.length() >= 4 && isAlphaString(new_TacGia))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 85, y + 12, new_TacGia);
                }
            }
            update.SetTac_Gia(new_TacGia);
            gotoXY(x + 85, y + 12);
            cout << new_TacGia;
        }
        else if (102 <= x_click && x_click <= 122 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Năm Xuất Bản
            string nam_xuat_ban;
            while (true)
            {

                writeString(50, y + 6, L"  Năm xuất bản phải có 4 kí tự!      ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 104, y + 12);
                nam_xuat_ban = getinput(); // Dùng getline để nhập năm xuất bản
                if (isValidYear(nam_xuat_ban))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 104, y + 4, nam_xuat_ban);
                }
            }
            int year;
            year = stoi(nam_xuat_ban);
            update.SetNXB(year);
            gotoXY(x + 104, y + 12);
            cout << nam_xuat_ban;
        }
        else if (122 <= x_click && x_click <= 132 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Số Lượng
            string quantity;
            while (true)
            {

                writeString(50, y + 6, L"  Số lượng phải nhỏ hơn 999!         ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 125, y + 12);
                quantity = getinput(); // Dùng getline để nhập số lượng
                if (isValidQuantity(quantity))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 125, y + 12, quantity);
                }
            }
            int so_luong;
            so_luong = stoi(quantity);
            update.SetSo_Luong(so_luong);
            gotoXY(x + 125, y + 12);
            cout << so_luong;
        }
        else if (132 <= x_click && x_click <= 152 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Giá Bán
            string price;
            while (true)
            {

                writeString(50, y + 6, L"  Giá sách phải lớn hơn 1000!        ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 136, y + 12);
                price = getinput(); // Dùng getline để nhập giá sách
                if (isValidPrice(price))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 136, y + 12, price);
                }
            }
            int gia_ban;
            gia_ban = stoi(price);
            update.SetGia_Ban(gia_ban);
            gotoXY(x + 136, y + 12);
            cout << gia_ban;
        }
        else
        {
            break; // Kết thúc cập nhật
        }
    }

    // Thêm lại sách vào vị trí cũ
    Insert_NodeMiddle(update, position - 1);

    return true;
}

bool LinkedList::DeleteBook()
{
    int position;
    while (true)
    {
        const wchar_t *name = L"[ Nhập Mã sách ]";
        writeString(10, 2, name);
        menuTable(27, 1, 30, 2);
        gotoXY(28, 2);

        string searchmasach = getinput();
        position = find_Node(searchmasach); // Tìm vị trí sách bằng cách tìm mã sách

        if (position == -1)
        {
            writeString(55, 12, L"Không tồn tại sách có mã như trên.");
        }
        else
        {
            break;
        }
    }
    Book DeleteBook = getNodeBook(position);

    // Hiển thị thông tin sách cần xóa
    bangsanpham(3, 8, 2);
    int x = 4, y = 10;
    writeString(x + 1, y - 4, L"[ THÔNG TIN SẢN PHẨM ]");
    gotoXY(x + 10, y + 1);
    cout << DeleteBook.getMa_Sach();
    gotoXY(x + 30, y + 1);
    cout << DeleteBook.getTen_sach();
    gotoXY(x + 60, y + 1);
    cout << DeleteBook.getThe_loai();
    gotoXY(x + 85, y + 1);
    cout << DeleteBook.getTac_gia();
    gotoXY(x + 104, y + 1);
    cout << DeleteBook.getNam_xuat_ban();
    gotoXY(x + 125, y + 1);
    cout << DeleteBook.getSo_luong();
    gotoXY(x + 136, y + 1);
    cout << DeleteBook.getGia_ban();

    // Xác nhận việc xóa sách
    int response = MessageBoxW(NULL, L"Bạn có chắc chắn muốn xóa sách này không?", L"Xác nhận", MB_OKCANCEL | MB_ICONQUESTION);
    if (response == IDOK)
    {
        delete_Node(DeleteBook); // Xóa sách nếu người dùng nhấn OK
        return true;
    }
    else
    {
        writeString(30, 22, L"Hủy bỏ việc xóa sách.");
        return false;
    }
}
bool LinkedList::Insert_NodeLast(Book B)
{
    if (this->isEmpty())
    {
        bookHead = new BookNode();
        bookHead->data = B;
        bookHead->next = NULL;
    }
    else if (this->find_Node(B) == -1)
    {
        BookNode *temp = bookHead;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        BookNode *newNode = new BookNode();
        newNode->data = B;
        newNode->next = NULL;
        temp->next = newNode;
    }
    else
    {
        return false; // Node already exists
    }
    return true;
}
bool LinkedList::Insert_NodeMiddle(Book B, int position)
{
    // Tạo một node mới để chứa dữ liệu sách
    BookNode *newNode = new BookNode();
    newNode->data = B;
    newNode->next = NULL;

    // Trường hợp danh sách rỗng hoặc vị trí là đầu danh sách
    if (this->isEmpty() || position <= 0)
    {
        newNode->next = bookHead;
        bookHead = newNode;
    }
    else
    {
        BookNode *temp = bookHead;
        int index = 0;

        // Duyệt danh sách đến vị trí trước vị trí chỉ định
        while (temp != NULL && index < position - 1)
        {
            temp = temp->next;
            index++;
        }

        // Trường hợp vị trí chỉ định vượt quá số phần tử hiện tại
        if (temp == NULL)
        {
            delete newNode; // Xóa node mới vì không thể chèn vào vị trí ngoài phạm vi
            return false;
        }

        // Chèn node mới vào vị trí chỉ định
        newNode->next = temp->next;
        temp->next = newNode;
    }

    return true;
}

//--------------------- create_book-----------------
// viết thêm các hàm kiểm tra có nhập đúng hay không
// nhấn enter để tiếp tục nhập nhấn esc để thoát
// Function to validate input, ensuring that only alphabetic characters are allowed
// các điều kiện
bool LinkedList::isUniqueBookID(const string &bookID)
{
    BookNode *current = this->bookHead; // Bắt đầu từ đầu danh sách sách
    while (current != nullptr)
    {
        if (current->data.Ma_Sach == bookID)
        {
            return false;
        }
        current = current->next;
    }
    return true;
}
// -------------------------------------------------------------------------------------------
bool LinkedList::CreateBook()
{
    ShowCursor(TRUE);
    int x = 2, y = 2;
    string bookID, bookName, bookGenre, bookAuthor, publicationYear, quantity, price;
    menuTable(x + 18, y + 28, 50, 2);
    writeString(x + 20, y + 29, L"[ENTER]  CONTINUE");
    writeString(x + 40, y + 29, L"[ESC]  SAVE & EXIT");
    writeString(x, y, L"[ THÊM SẢN PHẨM ]");
    bangsanpham(x, y + 1, 20);
    if (this->bookHead != nullptr)
    {
        BookNode *book = this->bookHead;
        while (book->next != nullptr)
        {
            book = book->next;
        }
        bookID = book->data.getMa_Sach();
        // Tách phần số từ chuỗi và tăng lên 1
        int numberPart = std::stoi(bookID.substr(4)) + 1;
        // Chuyển đổi lại thành chuỗi với định dạng mã mới
        bookID = "BOOK" + std::string(3 - std::to_string(numberPart).length(), '0') + std::to_string(numberPart);
    }
    else
    {
        // If there are no books in the list, start with BOOK001
        bookID = "BOOK001";
    }
    do
    {
        gotoXY(x + 4, y + 4);
        cout << bookID;
        while (true)
        {
            writeString(37, 2, L"[ Tên sách phải dài ít nhất 4 ký tự! ]");
            gotoXY(x + 25, y + 4);
            getline(cin, bookName); // Dùng getline để nhập tên sách, có thể chứa khoảng trắng
            if (bookName.length() >= 4 && isAlphaString(bookName))
            {
                break;
            }
            else
            {
                trolaisua(x + 25, y + 4, bookName);
            }
        }

        while (true)
        {
            writeString(37, 2, L"[ Thể loại phải dài ít nhất 3 ký tự! ]");
            gotoXY(x + 60, y + 4);
            getline(cin, bookGenre); // Dùng getline để nhập thể loại
            if (bookGenre.length() >= 3 && isAlphaString(bookGenre))
            {
                break;
            }
            else
            {
                trolaisua(x + 60, y + 4, bookGenre);
            }
        }

        while (true)
        {
            writeString(37, 2, L"Tên tác giả phải dài ít nhất 4 ký tự!");
            gotoXY(x + 85, y + 4);
            getline(cin, bookAuthor); // Dùng getline để nhập tên tác giả
            if (bookAuthor.length() >= 4 && isAlphaString(bookAuthor))
            {
                break;
            }
            else
            {
                trolaisua(x + 85, y + 4, bookAuthor);
            }
        }

        while (true)
        {
            writeString(37, 2, L"  Năm xuất bản phải có 4 kí tự!      ");
            gotoXY(x + 104, y + 4);
            getline(cin, publicationYear); // Dùng getline để nhập năm xuất bản
            if (isValidYear(publicationYear))
            {
                break;
            }
            else
            {
                trolaisua(x + 104, y + 4, publicationYear);
            }
        }

        while (true)
        {
            writeString(37, 2, L"  Số lượng phải nhỏ hơn 999!         ");
            gotoXY(x + 125, y + 4);
            getline(cin, quantity); // Dùng getline để nhập số lượng
            if (isValidQuantity(quantity))
            {
                break;
            }
            else
            {
                trolaisua(x + 125, y + 4, quantity);
            }
        }

        while (true)
        {
            writeString(37, 2, L"  Giá sách phải lớn hơn 1000!         ");
            gotoXY(x + 136, y + 4);
            getline(cin, price); // Dùng getline để nhập giá sách
            if (isValidPrice(price))
            {
                break;
            }
            else
            {
                trolaisua(x + 136, y + 4, price);
            }
        }
        Book newBook(bookID, bookName, bookGenre, bookAuthor, stoi(publicationYear), stoi(quantity), stoi(price));
        Insert_NodeLast(newBook);
        int numberPart = std::stoi(bookID.substr(4)) + 1;
        bookID = "BOOK" + std::string(3 - std::to_string(numberPart).length(), '0') + std::to_string(numberPart);
        // system("cls");
        // cout<<bookID;
        // system("pause");
        int key = batphim();
        if (key == 3)
        {
            y += 2;
            continue;
        }
        else if (key == 4)
        {
            break;
        }
    } while (true);
    return true;
}
int LinkedList::find_NodeCustomer(Customer a)
{
    CustomerNode *temp = this->customerHead;
    int position = 0;

    while (temp != NULL)
    {
        if (temp->data.getMaKH() == a.getMaKH())
        {
            return position;
        }
        temp = temp->next;
        ++position;
    }

    return -1;
}
bool LinkedList::Add_Customer(Customer B)
{
    if (this->isEmpty())
    {
        customerHead = new CustomerNode();
        customerHead->data = B;
        customerHead->next = nullptr;
    }
    else if (this->find_NodeCustomer(B) == -1)
    {
        CustomerNode *temp = customerHead;

        // Duyệt đến cuối danh sách
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        // Tạo nút mới và thêm vào cuối danh sách
        CustomerNode *newNode = new CustomerNode();
        newNode->data = B;
        newNode->next = nullptr;
        temp->next = newNode;
    }
    else
    {
        return false; // Khách hàng đã tồn tại
    }

    return true;
}
Book *LinkedList::getNode(int position)
{
    int k = 1;
    BookNode *temp = this->bookHead;

    // Duyệt danh sách đến vị trí cần tìm
    while (k != position && temp != NULL)
    {
        temp = temp->next;
        ++k;
    }

    // Nếu tìm thấy vị trí, trả về con trỏ đến dữ liệu, nếu không trả về nullptr
    if (temp != NULL)
    {
        return &(temp->data); // Trả về địa chỉ của đối tượng Book
    }
    else
    {
        return nullptr; // Nếu vị trí không hợp lệ
    }
}

Customer *LinkedList::getNodeCustomer(int position)
{
    int k = 1;
    CustomerNode *temp = this->customerHead;

    // Duyệt danh sách đến vị trí cần tìm
    while (k != position && temp != NULL)
    {
        temp = temp->next;
        ++k;
    }

    // Nếu tìm thấy vị trí, trả về con trỏ đến dữ liệu, nếu không trả về nullptr
    if (temp != NULL)
    {
        return &(temp->data); // Trả về địa chỉ của đối tượng Book
    }
    else
    {
        return nullptr; // Nếu vị trí không hợp lệ
    }
}
int LinkedList::find_NodeCustomer(const string &CusCode)
{
    CustomerNode *temp = this->customerHead;
    int position = 1;

    for (temp; temp != NULL; temp = temp->next)
    {
        if (temp->data.Ma_KH == CusCode)
        {
            return position;
        }
        ++position;
    }

    return -1;
}
void outputInvoice(int x, int y, string maHoaDon, string makhachhang, string ngayLap, int soLuong, int tongTien)
{
    gotoXY(x + 5, y + 1); // Position for Mã HĐ
    cout << maHoaDon;
    gotoXY(x + 25, y + 1); // Position for Mã KH
    cout << makhachhang;
    gotoXY(x + 45, y + 1); // Position for Ngày lập hóa đơn
    cout << ngayLap;
    gotoXY(x + 70, y + 1); // Position for Số lượng
    cout << soLuong;
    gotoXY(x + 90, y + 1); // Position for Tổng tiền
    cout << tongTien;
}
void displayInvoice(int n, string maHoaDonArr[], string makhachhangArr[], string ngayLapArr[], int soLuongArr[], int tongTienArr[])
{
    int page = 1;
    int totalPages = (n + 4) / 5; // Tổng số trang, mỗi trang 10 hóa đơn
    int tam = 0;
    while (tam == 0)
    {
        system("cls");
        const wchar_t *title = L"[ THÔNG TIN HÓA ĐƠN ]";
        writeString(2, 2, title);
        Bill_Table(2, 4, 23, page, totalPages);
        // In hóa đơn trên trang hiện tại
        int start = (page - 1) * 10;
        int end = min(start + 10, n);

        int y = 6;
        for (int i = start; i < end; ++i)
        {
            outputInvoice(2, y, maHoaDonArr[i], makhachhangArr[i], ngayLapArr[i], soLuongArr[i], tongTienArr[i]);
            y += 2;
        }

        int key = setKeyBoard();
        if (key == 4 && page < totalPages)
        { // Ấn qua phải để sang trang tiếp theo
            page++;
        }
        else if (key == 3 && page > 1)
        { // Ấn qua trái để quay lại trang trước
            page--;
        }
        else if (key == 5)
        { // Ấn thoát
            system("cls");
            tam = 1;
            break;
        }
    }
}
void LinkedList::statistical()
{
    int x = 30, y = 5;
    int thang, nam;
    int sum_products = 0;
    int sum_capital = 0;
    int num_customers = 0;
    int total_revenue = 0;
    int count_books = 0;

    // Initial statistics
    BookNode *tempBook = bookHead;
    while (tempBook != nullptr)
    {
        sum_products += tempBook->data.so_luong;
        sum_capital += tempBook->data.gia_ban;
        count_books++;
        tempBook = tempBook->next;
    }

    // Customer statistics
    CustomerNode *tempCustomer = customerHead;
    while (tempCustomer != nullptr)
    {
        num_customers++;
        total_revenue += tempCustomer->data.so_tien_da_mua;
        tempCustomer = tempCustomer->next;
    }

    int selectedOption = 0;
    char key;
    while (true)
    {
        system("cls");
        menuTable(x, y - 3, 60, 2);
        writeString(x + 15, y - 2, L"[THỐNG KÊ THÔNG TIN CỬA HÀNG]");
        menuTable(x, y, 60, 20);
        writeString(x + 2, y + 2, L"Tổng số mặt hàng sách trong cửa hàng:");
        gotoXY(x + 40, y + 2);
        cout << count_books;
        writeString(x + 2, y + 5, L"Tổng số lượng sách:");
        gotoXY(x + 25, y + 5);
        cout << sum_products;
        writeString(x + 2, y + 7, L"Vốn nhập hàng:");
        gotoXY(x + 16, y + 7);
        cout << sum_capital;
        writeString(x + 2, y + 9, L"Tổng số khách hàng mua hàng:");
        gotoXY(x + 30, y + 9);
        cout << num_customers;
        gotoXY(x + 2, y + 12);
        cout << "Tổng tiền thu được: " << total_revenue;
        writeString(x + 2, y + 18, selectedOption == 0 ? L"[ CHI TIẾT ]" : L"  CHI TIẾT  ");
        writeString(x + 30, y + 18, selectedOption == 1 ? L"[ TRO VE ]" : L"  TRO VE  ");
        key = batphim();

        if (key == 8)
        {
            if (selectedOption < 2)
            {
                selectedOption++;
            }
        }
        else if (key == 7)
        {
            if (selectedOption > 0)
            {
                selectedOption--;
            }
        }
        else if (key == 3)
        {
            if (selectedOption == 0)
            {
                bool detailMenu = true;
                while (detailMenu)
                {
                    system("cls");
                    string year, month;
                    bool found = false;

                    writeString(x, y, L"Nhập Năm cần thống kê");
                    menuTable(x + 25, y - 1, 20, 2);
                    gotoXY(x + 26, y);
                    getline(cin, year);

                    if (!isValidYear(year))
                    {
                        trolaisua(x + 26, y, year);
                        continue;
                    }

                    writeString(x, y + 4, L"Nhập Tháng cần thống kê");
                    menuTable(x + 25, y + 3, 20, 2);
                    gotoXY(x + 27, y + 4);
                    getline(cin, month);

                    if (!isValidMonth(month))
                    {
                        trolaisua(x + 27, y + 4, month);
                        continue;
                    }

                    ifstream infile("bill.txt");
                    if (!infile)
                    {
                        cout << "Khong the mo file!" << endl;
                        return;
                    }

                    int sum_productsdetail = 0, sum_capitaldetail = 0, sum_cusDetail = 0, sum_BookDetail = 0;
                    int n;
                    infile >> n;
                    int count = 0; // Biến đếm số lượng hóa đơn hợp lệ
                    infile.ignore();
                    string maHoaDonArr[1000]; // Giả sử số hóa đơn không quá 1000
                    string makhachhangArr[1000];
                    string ngayLapArr[1000];
                    int soLuongArr[1000];
                    int tongTienArr[1000];
                    for (int i = 1; i <= n; ++i)
                    {
                        string maHoaDon, ngayLap, makhachhang;
                        int soLuong, tongTien, ngay, thang_hoa_don, nam_hoa_don;
                        getline(infile, maHoaDon, '|');
                        getline(infile, makhachhang, '|');
                        getline(infile, ngayLap, '|');
                        infile >> soLuong;
                        infile.ignore(1);
                        infile >> tongTien;
                        infile.ignore(1);
                        sscanf(ngayLap.c_str(), "%d-%d-%d", &nam_hoa_don, &thang_hoa_don, &ngay);
                        if (thang_hoa_don == stoi(month) && nam_hoa_don == stoi(year))
                        {
                            maHoaDonArr[count] = maHoaDon;
                            makhachhangArr[count] = makhachhang;
                            ngayLapArr[count] = ngayLap;
                            soLuongArr[count] = soLuong;
                            tongTienArr[count] = tongTien;

                            sum_productsdetail += soLuong;
                            sum_capitaldetail += tongTien;
                            sum_cusDetail++;
                            sum_BookDetail++;
                            found = true;
                            count++; // Tăng biến đếm
                        }
                    }
                    infile.close();

                    if (found)
                    {
                        int Sub_selectedOption = 0;
                        while (true)
                        {
                            system("cls");
                            menuTable(x, y - 3, 60, 2);
                            writeString(x + 15, y - 2, L"[THỐNG KÊ CHI TIẾT TRONG THÁNG]");
                            menuTable(x, y, 60, 15);
                            writeString(x + 2, y + 2, L"Tổng số mặt hàng sách bán trong tháng:");
                            gotoXY(x + 40, y + 2);
                            cout << sum_BookDetail;
                            writeString(x + 2, y + 4, L"Tổng số lượng sách đã bán:");
                            gotoXY(x + 30, y + 4);
                            cout << sum_productsdetail;
                            writeString(x + 2, y + 6, L"Doanh thu trong tháng:");
                            gotoXY(x + 40, y + 6);
                            cout << sum_capitaldetail << " VND";
                            writeString(x + 2, y + 8, L"Số lượng khách hàng:");
                            gotoXY(x + 30, y + 8);
                            cout << sum_cusDetail;
                            writeString(x + 2, y + 18, Sub_selectedOption == 0 ? L"[ CHI TIẾT ]" : L"  CHI TIẾT  ");
                            writeString(x + 30, y + 18, Sub_selectedOption == 1 ? L"[ TRO VE ]" : L"  TRO VE  ");

                            int Sub_key = batphim();
                            if (Sub_key == 8) // Right arrow
                            {
                                if (Sub_selectedOption < 1)
                                {
                                    Sub_selectedOption++;
                                }
                            }
                            else if (Sub_key == 7) // Left arrow
                            {
                                if (Sub_selectedOption > 0)
                                {
                                    Sub_selectedOption--;
                                }
                            }
                            else if (Sub_key == 3) // Enter key
                            {
                                if (Sub_selectedOption == 0)
                                {
                                    displayInvoice(count, maHoaDonArr, makhachhangArr, ngayLapArr, soLuongArr, tongTienArr);
                                }
                                else if (Sub_selectedOption == 1)
                                {
                                    detailMenu = false; // Exit to main statistics view
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        system("cls");
                        writeString(x + 1, y + 4, L"Không tồn tại năm, tháng như đã nhập");
                        menuTable(x, y + 3, 42, 2);
                        if (setKeyBoard() == 5)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                return;
            }
        }
    }
}

void LinkedList::Order()
{
    int i = 0;
    string check;
    int x = 2, y = 2, a = 2;
    Book *foundBook;
    int position;
    int soluong, count;
    string masach, temp;
    int types = 0;
    Book **bookCode = new Book *[1000];
    int *bookCount = new int[1000];
    Add_Product(&bookCode, &bookCount, types);
    confirm(bookCode, bookCount, types);
    if (bookCode[i]->getSo_luong() == 0)
    {
        int position = find_Node(bookCode[i]->getMa_Sach());
        Book DeleteBook = getNodeBook(position);
        delete_Node(DeleteBook); // Tìm vị trí sách bằng cách tìm mã sách
    }
    delete[] bookCount;
    delete[] bookCode;
    return;
}
void LinkedList::Add_Product(Book ***bookCode, int **bookCount, int &types)
{
    system("cls");
    int x = 2, y = 2, a = 2;
    int soluong;
    string masach;
    Book *foundBook;
    int position;

    writeString(x, y, L"[Nhập mã sách cần bán]");
    menuTable(x + 23, y - 1, 25, 2);
    writeString(x + 70, y, L"[Nhập số lượng:]");
    menuTable(x + 90, y - 1, 25, 2);
    writeString(x + 1, y + 4, L"[ THÔNG TIN SẢN PHẨM ]");
    menuDisplay(x + 1, y + 6, 20, 1, 1);

    while (true)
    {
        // Xóa nội dung cũ tại vị trí nhập mã sách và số lượng
        gotoXY(x + 24, y);
        cout << string(20, ' '); // Xóa nội dung trong ô nhập mã sách
        gotoXY(x + 102, y);
        cout << string(10, ' '); // Xóa nội dung trong ô nhập số lượng

        // Nhập mã sách
        while (true)
        {
            gotoXY(x + 24, y);
            cout << string(20, ' ');
            gotoXY(x + 24, y);
            cin >> masach;

            position = find_Node(masach);
            if (position != -1)
            {
                break;
            }
            else
            {
                writeString(x + 23, y + 2, L"[Không tồn tại mã sách như trên]");
            }
        }

        foundBook = getNode(position); // Lấy con trỏ đến đối tượng sách

        // Nhập số lượng
        while (true)
        {
            gotoXY(x + 102, y);
            cout << string(10, ' ');
            gotoXY(x + 102, y);
            cin >> soluong;

            // Kiểm tra số lượng hợp lệ
            if (cin.fail() || soluong <= 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                writeString(x + 70, y + 2, L"[Số lượng không hợp lệ. Vui lòng nhập lại]");
            }
            else if (soluong > foundBook->getSo_luong())
            {
                writeString(x + 70, y + 2, L"[ Số lượng vượt quá số lượng hiện có. Vui lòng nhập lại]");
            }
            else
            {
                break;
            }
        }

        // Thêm sản phẩm vào mảng
        (*bookCode)[types] = foundBook;
        (*bookCount)[types] = soluong;
        types++;

        // Hiển thị thông tin sách đã chọn
        gotoXY(x + 10, a + 9);
        cout << (*bookCode)[types - 1]->getMa_Sach();
        gotoXY(x + 30, a + 9);
        cout << (*bookCode)[types - 1]->getTen_sach();
        gotoXY(x + 60, a + 9);
        cout << (*bookCode)[types - 1]->getThe_loai();
        gotoXY(x + 85, a + 9);
        cout << (*bookCode)[types - 1]->getTac_gia();
        gotoXY(x + 104, a + 9);
        cout << (*bookCode)[types - 1]->getNam_xuat_ban();
        gotoXY(x + 125, a + 9);
        cout << (*bookCount)[types - 1];
        gotoXY(x + 136, a + 9);
        cout << (*bookCode)[types - 1]->getGia_ban();

        // Xác nhận có chọn thêm sản phẩm không
        int response = MessageBoxW(NULL, L"Bạn có muốn chọn thêm sản phẩm không?", L"Xác nhận", MB_OKCANCEL | MB_ICONQUESTION);
        if (response == IDOK)
        {
            a += 2; // Điều chỉnh vị trí cho lần nhập tiếp theo
        }
        else
        {
            break;
        }
    }
}
void LinkedList::confirm(Book **bookCode, int *bookCount, int types)
{
    string billDay, cusCode, newNameCus, newCusAddress, newCusSdt;
    int sum = 0;
    int x = 20, y = 2;
    int a = 5;
    int selectedOption = 0; // 0 = "Xóa sản phẩm", 1 = "Sửa sản phẩm", 2 = "Tiếp tục thanh toán"
    int selectedProduct;
    int keyInput;
    system("cls");
    writeString(x, y, L"[ DANH SÁCH SẢN PHẨM ĐÃ CHỌN ]");
    Ordertable(x, y + 4, 20);
    // Menu items positions
    int menuX = x, menuY = y + 30;
    while (true)
    {
        // Clear the screen and redraw menu
        system("cls");
        writeString(x, y, L"[ DANH SÁCH SẢN PHẨM ĐÃ CHỌN ]");
        Ordertable(x, y + 4, 20);
        a = 5;
        for (int i = 0; i < types; i++)
        {
            gotoXY(x + 5, a + 5);
            cout << i + 1;
            gotoXY(x + 20, a + 5);
            cout << bookCode[i]->getTen_sach();
            gotoXY(x + 50, a + 5);
            cout << bookCount[i];
            gotoXY(x + 70, a + 5);
            cout << bookCode[i]->getGia_ban();
            gotoXY(x + 85, a + 5);
            cout << bookCode[i]->getGia_ban() * bookCount[i];
            a = a + 2;
        }
        menuTable(menuX, menuY, 110, 2); // Tăng chiều rộng menu cho phù hợp với 4 mục
        writeString(menuX + 5, menuY + 1, selectedOption == 0 ? L"[ Xóa sản phẩm ]" : L"  Xóa sản phẩm");
        writeString(menuX + 30, menuY + 1, selectedOption == 1 ? L"[ Sửa sản phẩm ]" : L"  Sửa sản phẩm");
        writeString(menuX + 55, menuY + 1, selectedOption == 2 ? L"[ Thêm sản phẩm ]" : L"  Thêm sản phẩm");
        writeString(menuX + 80, menuY + 1, selectedOption == 3 ? L"[ Tiếp tục thanh toán ]" : L"  Tiếp tục thanh toán");
        // Chờ nhận phím từ hàm batphim
        keyInput = batphim();
        // Di chuyển trong menu dựa trên phím mũi tên
        if (keyInput == 8) // RIGHT key (sang phải)
        {
            if (selectedOption < 3) // Bây giờ có 4 lựa chọn (0-3)
            {
                selectedOption++;
            }
        }
        else if (keyInput == 7) // LEFT key (sang trái)
        {
            if (selectedOption > 0)
            {
                selectedOption--;
            }
        }
        else if (keyInput == 3) // Khi nhấn phím Enter
        {
            system("cls"); // Xóa màn hình khi chọn một mục
            if (selectedOption == 0)
            {
                // Xử lý "Xóa sản phẩm"
                writeString(x, y, L"[ Chọn sản phẩm cần xóa ]");
                writeString(x, y, L"[ Chọn sản phẩm cần xóa ]");
                menuTable(x + 25, y - 1, 20, 2);
                Ordertable(x, y + 4, 20);
                for (int i = 0; i < types; i++)
                {
                    gotoXY(x + 5, a + 3);
                    cout << i + 1;
                    gotoXY(x + 20, a + 3);
                    cout << bookCode[i]->getTen_sach();
                    gotoXY(x + 50, a + 3);
                    cout << bookCount[i];
                    gotoXY(x + 70, a + 3);
                    cout << bookCode[i]->getGia_ban();
                    gotoXY(x + 85, a + 3);
                    cout << bookCode[i]->getGia_ban() * bookCount[i];
                    a = a + 2;
                }
                gotoXY(x + 28, y);
                cin >> selectedProduct;
                if (selectedProduct >= 1 && selectedProduct <= types)
                {
                    // Show confirmation message
                    int response = MessageBoxW(
                        NULL,
                        L"Bạn có chắc chắn muốn xóa sản phẩm?",
                        L"Xác nhận",
                        MB_OKCANCEL | MB_ICONQUESTION);

                    // If the user confirms, delete the product
                    if (response == IDOK)
                    {
                        // Remove the product from the list
                        for (int i = selectedProduct - 1; i < types - 1; i++)
                        {
                            bookCode[i] = bookCode[i + 1];
                            bookCount[i] = bookCount[i + 1];
                        }
                        types--;
                    }
                    else
                    {
                        writeString(x, y + 2, L"Hủy bỏ thao tác xóa.");
                    }
                }
                else
                {
                    writeString(x, y + 2, L"Mã sản phẩm không hợp lệ.");
                }
            }
            else if (selectedOption == 1)
            {
                // Xử lý "Sửa sản phẩm"
                writeString(x, y, L"[ Chọn sản phẩm cần sửa ]");
                menuTable(x + 25, y - 1, 15, 2);
                Ordertable(x, y + 4, 20);
                for (int i = 0; i < types; i++)
                {
                    gotoXY(x + 5, a + 3);
                    cout << i + 1;
                    gotoXY(x + 20, a + 3);
                    cout << bookCode[i]->getTen_sach();
                    gotoXY(x + 50, a + 3);
                    cout << bookCount[i];
                    gotoXY(x + 70, a + 3);
                    cout << bookCode[i]->getGia_ban();
                    gotoXY(x + 85, a + 3);
                    cout << bookCode[i]->getGia_ban() * bookCount[i];
                    a = a + 2;
                }
                gotoXY(x + 28, y);
                cin >> selectedProduct;
                if (selectedProduct >= 1 && selectedProduct <= types)
                {
                    int newQuantity;
                    writeString(x + 50, y, L"[ Nhập số lượng mới ]");
                    menuTable(x + 80, y - 1, 15, 2);
                    gotoXY(x + 83, y);
                    cin >> newQuantity;
                    if (newQuantity > 0 && newQuantity <= bookCode[selectedProduct - 1]->getSo_luong())
                    {
                        bookCount[selectedProduct - 1] = newQuantity;
                        writeString(x, y, L"Đã sửa số lượng sản phẩm thành công.");
                    }
                    else
                    {
                        writeString(x, y + 2, L"Số lượng không hợp lệ.");
                    }
                }
                else
                {
                    writeString(x, y + 2, L"Mã sản phẩm không hợp lệ.");
                }
            }
            else if (selectedOption == 2)
            {
                // Xử lý "Thêm sản phẩm"
                Add_Product(&bookCode, &bookCount, types);
            }
            else if (selectedOption == 3)
            {
                // Xử lý "Tiếp tục thanh toán"
                for (int i = 0; i < types; i++)
                {
                    bookCode[i]->SetSo_Luong(bookCode[i]->getSo_luong() - bookCount[i]);
                }
                break; // Thoát khỏi vòng lặp menu để tiếp tục thanh toán
            }
        }
    }
    bill(bookCode, bookCount, types);
}
void LinkedList::bill(Book **bookCode, int *bookCount, int types)
{
    int x = 20, y = 5;
    int a = 5;
    string billDay, cusCode, newNameCus, newCusAddress, newCusSdt, newCusCode;
    int day, month, year;
    int sum = 0;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Input
    writeString(x + 6, y, L"[Nhập thông tin hóa đơn]");
    menuTable(x, y + 1, 45, 25);
    // Input for bill details
    writeString(x + 6, y + 2, L"[ Nhập ngày lập hóa đơn ]");
    menuTable(x + 6, y + 3, 30, 2);
    writeString(x + 6, y + 7, L"[ Nhập tên khách hàng ]");
    menuTable(x + 6, y + 8, 30, 2);
    writeString(x + 6, y + 12, L"[ Nhập địa chỉ khách hàng ]");
    menuTable(x + 6, y + 13, 30, 2);
    writeString(x + 6, y + 17, L"[ Nhập số điện thoại khách hàng ]");
    menuTable(x + 6, y + 18, 30, 2);

    // Validate bill day
    bool validDate = false;
    while (!validDate)
    {
        gotoXY(x + 7, y + 4);
        getline(cin, billDay);

        if (sscanf(billDay.c_str(), "%d/%d/%d", &day, &month, &year) == 3 && chuantime(day, month, year))
        {
            validDate = true;
        }
        else
        {
            gotoXY(x + 7, y + 6);
            trolaisua(x + 7, y + 4, billDay);
        }
    }
    billDay = formatDate(billDay);

    // Validate customer name
    while (true)
    {
        gotoXY(x + 7, y + 9);
        getline(cin, newNameCus);
        if (isAlphaString(newNameCus))
            break;
        else
            trolaisua(x + 7, y + 9, newNameCus);
    }

    // Validate customer address
    while (true)
    {
        gotoXY(x + 7, y + 14);
        getline(cin, newCusAddress);
        if (isAlphaString(newCusAddress))
            break;
        else
            trolaisua(x + 7, y + 14, newCusAddress);
    }

    // Validate customer phone number
    while (true)
    {
        gotoXY(x + 7, y + 19);
        getline(cin, newCusSdt);
        if (isPhoneNumber(newCusSdt))
            break;
        else
            trolaisua(x + 7, y + 19, newCusSdt);
    }

    // Calculate the total sum of the order
    sum = this->Calculator(bookCode, bookCount, types);
    // Generate a new customer code
    CustomerNode *cus = this->customerHead;
    bool customerExists = false;

    // Check if customer already exists
    while (cus != NULL)
    {
        if (cus->data.getSdtKH() == newCusSdt && cus->data.getDia_chi() == newCusAddress && cus->data.getSdtKH() == newCusSdt)
        {
            // Customer exists, add sum to existing customer's amount
            cus->data.setSTDM(cus->data.getSo_tien_da_mua() + sum);
            customerExists = true;
            break;
        }
        cus = cus->next;
    }

    if (!customerExists)
    {
        // Generate a new customer code
        cus = this->customerHead;
        std::string cusCode;
        while (cus != NULL)
        {
            cusCode = cus->data.getMaKH();
            cus = cus->next;
        }

        if (cusCode.length() > 2)
        {
            int numberPart = std::stoi(cusCode.substr(2)) + 1;
            cusCode = "KH" + std::to_string(numberPart).insert(0, 3 - std::to_string(numberPart).length(), '0');
        }
        else
        {
            cusCode = "KH001"; // Default customer code if none exists
        }

        // Create and add a new customer
        Customer newCus(cusCode, newNameCus, newCusAddress, newCusSdt, sum);
        Add_Customer(newCus);
        newCusCode = cusCode;
        std::ifstream infile("customers.txt");
        if (!infile)
        {
            std::cerr << "File could not be opened!" << std::endl;
            return;
        }

        int n;
        infile >> n;
        infile.ignore();
        n += 1;
        std::ofstream outfile("customers.txt", std::ios::in);
        if (!outfile)
        {
            std::cerr << "File could not be opened for writing!" << std::endl;
            return;
        }
        outfile << n << "\n";
        outfile.seekp(0, std::ios::end);
        for (int i = 0; i < types; i++)
        {
            outfile << "\n"
                    << cusCode << "|" << newNameCus << "|" << newCusAddress << "|" << newCusSdt
                    << "|" << sum;
        }
        outfile.close();
        // Read the number of records
    }
    system("cls");
    y = 3;
    writeString(x + 28, y, L"[ HÓA ĐƠN BÁN HÀNG ]");
    writeString(x, y + 2, L"Tên khách hàng:");
    gotoXY(x + 20, y + 2);
    cout << newNameCus;
    writeString(x + 40, y + 2, L"Ngày lập hóa đơn:");
    gotoXY(x + 60, y + 2);
    cout << billDay;
    writeString(x, y + 4, L"Địa chỉ:");
    gotoXY(x + 20, y + 4);
    cout << newCusAddress;
    writeString(x, y + 6, L"Số điện thoại:");
    gotoXY(x + 20, y + 6);
    cout << newCusSdt;

    // Display the order table
    Ordertable(x, y + 8, 18);
    for (int i = 0; i < types; i++)
    {
        gotoXY(x + 5, a + 9);
        cout << i + 1;
        gotoXY(x + 20, a + 9);
        cout << bookCode[i]->getTen_sach();
        gotoXY(x + 50, a + 9);
        cout << bookCount[i];
        gotoXY(x + 70, a + 9);
        cout << bookCode[i]->getGia_ban();
        gotoXY(x + 85, a + 9);
        cout << bookCode[i]->getGia_ban() * bookCount[i];
        a += 2;
    }
    writeString(x + 80, y + 30, L"[ TỔNG TIỀN ]");
    gotoXY(x + 96, y + 30);
    cout << Calculator(bookCode, bookCount, types);
    std::string maHoaDon, ngayLap, makhachhang;
    int soLuong, tongTien;
    std::ifstream infile("bill.txt");
    if (!infile)
    {
        std::cerr << "File could not be opened!" << std::endl;
        return;
    }

    int n;
    infile >> n; // Read the number of records
    infile.ignore();
    // Read the existing records (if necessary)
    for (int i = 1; i <= n; ++i)
    {
        getline(infile, maHoaDon, '|');
        getline(infile, makhachhang, '|');
        getline(infile, ngayLap, '|');
        infile >> soLuong;
        infile.ignore(1);
        infile >> tongTien;
        infile.ignore(1);
    }
    infile.close();
    n += 1;
    int numberPart = std::stoi(maHoaDon.substr(2)) + 1;
    maHoaDon = "HD" + std::string(3 - std::to_string(numberPart).length(), '0') + std::to_string(numberPart);
    std::ofstream outfile("bill.txt", std::ios::in);
    if (!outfile)
    {
        std::cerr << "File could not be opened for writing!" << std::endl;
        return;
    }
    outfile << n << "\n";
    outfile.seekp(0, std::ios::end);
    for (int i = 0; i < types; i++)
    {
        outfile << "\n"
                << maHoaDon << "|" << newCusCode << "|" << billDay << "|" << bookCount[i]
                << "|" << bookCode[i]->getGia_ban() * bookCount[i];
    }
    outfile.close();
    // Wait for Esc to exit
    while (true)
    {
        if (setKeyBoard() == 5) // ASCII code for Esc
        {
            break;
        }
    }
}

long long LinkedList::Calculator(Book **bookCode, int *bookCount, int types)
{
    long long sum = 0;
    for (int i = 0; i < types; i++)
    {
        if (!bookCode[i]->getMa_Sach().empty())
        {
            sum += bookCode[i]->getGia_ban() * bookCount[i];
        }
    }
    return sum;
}
