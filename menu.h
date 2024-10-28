#include <iostream>
#include <windows.h>
#include <conio.h>
#include "HeThong.h"
using namespace std;

// --- Variables ---
string menu[] = {
    "1> Quan li san Pham ",
    "2> Quan li Khach Hang",
    "3> Order",
    "4> Thong ke",
    "5> Thong tin",
    "6> Thoat   "};
int menuSize = sizeof(menu) / sizeof(menu[0]);
string menuUser[] = {
    "1> Xem thong tin san Pham ",
    "2> Xem thong tin Khach Hang",
    "3> Order",
    "4> Thong ke",
    "5> Thong tin",
    "6> Thoat   "};
int menuUserSize = sizeof(menuUser) / sizeof(menuUser[0]);
string menuCRUD[] = {
    "1> Xem thong tin cua sach",
    "2> Them sach moi",
    "3> Xoa sach",
    "4> Cap nhat sach",
    "5> Thoat"};
int menuCRUDSize = sizeof(menuCRUD) / sizeof(menuCRUD[0]);

string menuRead[] = {
    "1> Thong tin toan bo sach trong cua hang",
    "2> Tim kiem thong tin sach",
    "3> Sap xep thong tin sach",
    "4> Thoat"};
int menuReadSize = sizeof(menuRead) / sizeof(menuRead[0]);

string menuSearch[] = {
    "1> Tim kiem sach theo ten sach",
    "2> Tim kiem sach theo the loai",
    "3> Tim kiem sach theo tac gia",
    "4> Tim kiem sach theo nam xuat ban",
    "5> Thoat"};
int menuSearchSize = sizeof(menuSearch) / sizeof(menuSearch[0]);

string menuSort[] = {
    "1> Sap xep sach theo so luong",
    "2> Sap xep sach theo so tien",
    "3> Sap xep sach theo nam xuat ban",
    "4> Thoat"};
int menuSortSize = sizeof(menuSort) / sizeof(menuSort[0]);
string menuSortUpandDown[] = {
    "1> Sap xep tang dan",
    "2> Sap xep giam dan",
    "3> Thoat"};
int menuUpandDownSize = sizeof(menuSortUpandDown) / sizeof(menuSortUpandDown[0]);
string menuKhachHang[] = {
    "1> Nhap thong tin khach hang",
    "2> Quan li khach hang",
    "3> Thoat"};

// --- Functions ---
inline void thanh_sang(int x, int y, int w, int h, int b_color, string menuItems[], int currentItem)
{
    //_setmode(_fileno(stdout), _O_U16TEXT);
    setcolor(15, b_color); // Màu chữ trắng (15), màu nền tùy chọn
    for (int iy = y + 1; iy <= y + h - 1; iy++)
    {
        for (int ix = x + 1; ix <= x + w - 1; ix++)
        {
            gotoXY(ix, iy);
            cout << " ";
        }
    }
    gotoXY(x + 2, y + 1);
    cout << menuItems[currentItem]; // Hiển thị mục menu tương ứng

    // Reset màu trở lại màu mặc định sau khi in thanh sáng
    // Màu mặc định: chữ trắng, nền đen
}
inline int MENU(string menuItems[], int menuSize, int x, int y, int w, int h, int boxX, int boxY, int boxW)
{
    Showcur(0);
    int t_color = 11;
    int b_color = 0;
    int b_color_sang = 012;
    int currentItem = 0;

    // Draw box for menu
    menuTable(boxX, boxY, boxW, menuSize * 3 + 4);

    // Print all menu items with default color
    for (int i = 0; i < menuSize; i++)
    {
        gotoXY(x + 2, y + i * 3 + 1);
        setcolor(7, 0); // Default color
        cout << menuItems[i];
    }

    int xp = x, yp = y, xcu = xp, ycu = yp;
    bool kt = true;

    while (true)
    {
        if (kt == true)
        {
            // Reset previous item to default color
            thanh_sang(xcu, ycu, w, h, b_color, menuItems, (ycu - y) / 3);

            // Update current coordinates
            xcu = xp;
            ycu = yp;

            // Highlight new item
            thanh_sang(xcu, ycu, w, h, b_color_sang, menuItems, (yp - y) / 3);
            kt = false;
        }

        if (_kbhit())
        {
            char c = _getch();
            if (c == -32)
            { // Arrow keys
                kt = true;
                c = _getch();
                if (c == 72)
                { // Up arrow key
                    if (yp != y)
                        yp -= 3;
                    else
                        yp = y + 3 * (menuSize - 1); // Loop back to last item
                }
                else if (c == 80)
                { // Down arrow key
                    if (yp != y + 3 * (menuSize - 1))
                        yp += 3;
                    else
                        yp = y; // Loop back to first item
                }
            }
            else if (c == 13)
            {                        // Enter key
                setcolor(7, 0);      // Reset color to default before executing action
                return (yp - y) / 3; // Return the selected menu index
            }
            else if (c == 27)
            {                   // ESC key
                setcolor(7, 0); // Reset color to default on ESC
                return -1;      // Exit on ESC key press
            }
        }
    }

    // Reset color to default at the end
    setcolor(7, 0);
    gotoXY(0, 30);
    return -1;
}
inline void Thong_Tin()
{
    int x = 50, y = 5;
    while (true)
    {
        menuTable(x + 29, y + 2, 65, 19);
        writeString(x + 57, y + 3, L"PBL2");
        writeString(x + 37, y + 5, L"CHƯƠNG TRÌNH QUẢN LÍ CỬA HÀNG CHUYÊN VỀ SÁCH");
        writeString(x + 33, y + 9, L"Sinh viên thực hiện: Trần Quốc Đạt  Lớp: 23T_NHAT2");
        writeString(x + 33, y + 11, L"Sinh viên thực hiện: Cao Minh Đức   Lớp: 23T_NHAT2");
        writeString(x + 33, y + 13, L"Giáo viên hướng dẫn: Thầy Võ Đức Hoàng");
        writeString(x + 33, y + 15, L"Cảm ơn: Các thầy, cô giáo trong bộ môn đã giúp đỡ chúng em");
        if (setKeyBoard() == 5)
        {
            break;
        }
    }
}