#pragma once 
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <strsafe.h>
#include <chrono>
#include <io.h>
#include <fcntl.h>
using namespace std;
inline void gotoXY(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
inline void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
inline void drawBox(int x, int y, int width, int height) {
    gotoXY(x, y); cout << char(218); 
    gotoXY(x + width - 1, y); cout << char(191); 
    gotoXY(x, y + height - 1); cout << char(192); 
    gotoXY(x + width - 1, y + height - 1); cout << char(217); 

    for (int i = 1; i < width - 1; ++i) {
        gotoXY(x + i, y); cout << char(196); 
        gotoXY(x + i, y + height - 1); cout << char(196); 
    }

    for (int i = 1; i < height - 1; ++i) {
        gotoXY(x, y + i); cout << char(179); 
        gotoXY(x + width - 1, y + i); cout << char(179); 
    }
}

inline void Showcur(bool CursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    // Lấy thông tin con trỏ hiện tại
    GetConsoleCursorInfo(handle, &ConCurInf);

    // Thiết lập trạng thái hiển thị con trỏ
    ConCurInf.bVisible = CursorVisibility;
    
    // Thiết lập lại kích thước con trỏ (không cần thay đổi kích thước nếu bạn chỉ muốn hiển thị/ẩn con trỏ)
    ConCurInf.dwSize = 10; // Giá trị hợp lệ nằm trong khoảng từ 1 đến 100

    // Cập nhật thông tin con trỏ
    SetConsoleCursorInfo(handle, &ConCurInf);
}
inline void setcolor(int text_color, int background_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background_color << 4) | text_color);
}

//Ghi lỗi và thoát ra ( dùng trong bắt sự kiện chuột)
inline VOID WriteError(LPSTR lpszMessage) {
	printf("%s\n", lpszMessage);
	ExitProcess(0);
}
// Viết kí tự tại vị trí có tọa độ (x, y)
inline void writeChar(int x, int y, const wchar_t* z) {
    // Save the current mode
    int oldMode = _setmode(_fileno(stdout), _O_U16TEXT); 

    // Move the cursor to the specified position and print the wide character string
    gotoXY(x, y);
    wcout << z;

    // Restore the previous mode
    _setmode(_fileno(stdout), oldMode);
}
inline int setClick(int& a, int& b) {
    DWORD cNumRead;
    DWORD fdwMode;
    INPUT_RECORD irInBuf[128];
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE) {
        WriteError(const_cast<LPSTR>("GetStdHandle failed"));
        return 1;
    }

    // Set extended flags mode
    fdwMode = ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode)) {
        WriteError(const_cast<LPSTR>("SetConsoleMode failed (EXTENDED_FLAGS)"));
        return 1;
    }

    // Enable window and mouse input
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode)) {
        WriteError(const_cast<LPSTR>("SetConsoleMode failed (WINDOW_INPUT | MOUSE_INPUT)"));
        return 1;
    }

    bool clicked = false;

    while (!clicked) {
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            WriteError(const_cast<LPSTR>("ReadConsoleInput failed"));
            return 1;
        }

        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Check if it's a left button click event and not mouse movement
                if ((mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) && (mer.dwEventFlags == 0)) {
                    a = mer.dwMousePosition.X;
                    b = mer.dwMousePosition.Y;
                    clicked = true;
                    break;
                }
            }
        }
    }

    // Always return a value at the end
    return 0;
}
inline void menuTable(int x, int y, int m, int n)
{
	int i, j;
	//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(consoleHandle, 0x70);
	for (i = x; i <= x + m; i++)
		for (j = y; j <= y + n; j++)
		{
			if (i == x || i == x + m)
			{
				if (j == y && i != x + m)
					writeChar(i, j, L"╔");

				else if (j == y && i != x)
					writeChar(i, j, L"╗");
				else if (j == y + n && i != x + m)
					writeChar(i, j, L"╚");
				else if (j == y + n && i != x)
					writeChar(i, j, L"╝");
				else writeChar(i, j, L"║");
			}
			else if (j == y || j == y + n)
				writeChar(i, j, L"═");
		}
}
//sự kiện bàn phím
inline int setKeyBoard() {
    while (true) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            return 2; // lên
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            return 1; // xuống
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            return 3; // TRÁI
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            return 4; // PHẢI
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            return 5; // ESC
        }
    }
    return 0;
}
inline int batphim()
{
	int c=getch();
	if(c==8) //phim Backspace
		return 1;
	else if(c==9) //phim Tab
		return 2;
	else if(c==13) //phim Enter
		return 3;
	else if(c==27) //phim Esc
		return 4;
	else if(c==224)
	{
		c=getch();
		if(c==72) //Keyup
			return 5;
		else if(c==80) //KeyDown
			return 6;
		else if(c==75) //KeyLeft
			return 7;
		else if(c==77) //KeyRight
			return 8;
		else if(c==83) //Delete
			return 9;
	}
	else if(c==0)
	{
		c=getch();
		if(c==60) //F2
			return 12;
		if(c==62) //F4
			return 13;
	}
}
inline void writeString(int x, int y, const std::wstring& s) {
    // Set console mode to handle Unicode characters (UTF-16)
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);
    gotoXY(x, y);

    // Output the string with wcout
    std::wcout << s;
    _setmode(_fileno(stdout), _O_TEXT);
}

inline void display_login() {
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    setTextColor(11);
   menuTable(40, 5, 40, 20);
    writeChar(45, 8,L"Username");
   menuTable(45, 10 , 30, 2);
    writeChar(45, 14,L"Password");
   menuTable(45, 15, 30, 2); 
    writeChar(45, 18,L"Press Tab to show/hide password.");
   menuTable(45, 20, 30, 2); 
    writeChar(57, 21,L"Login");
    writeString(53, 23, L"\033[4mForgot password\033[0m");
}
inline void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);  // Lấy handle của console
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);  // Lấy thông tin hiện tại của con trỏ chuột
    cursorInfo.bVisible = FALSE;  // Đặt trạng thái hiển thị của con trỏ thành FALSE để ẩn con trỏ
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);  // Cập nhật thông tin mới của con trỏ chuột
}
inline void menuDisplay(int x, int y, int sl, int number = 1, int sum = 1) {
 int i, j;
    int c = 150;
    for (i = x; i <= x + c; i++) {
    for (j = y; j <= y + sl; j++) {
        if (i == x || i == x + 20 || i == x + 50 || i == x + 80 || i == x + 100 ||
            i == x + 120 || i == x + 130|| i == x + c) {

            // Drawing corners and intersections for clean table look
            if (j == y && i != x && i != x + c)
                writeChar(i, j, L"┬");
            else if (j == y && i == x)
                writeChar(i, j, L"┌");
            else if (j == y && i == x + c)
                writeChar(i, j, L"┐");
            else if (j == y + 2 && i != x && i != x + c)
                writeChar(i, j, L"┼");
            else if (j == y + 2 && i == x)
                writeChar(i, j, L"├");
            else if (j == y + 2 && i == x + c)
                writeChar(i, j, L"┤");
            else if (j == y + sl && i != x && i != x + c)
                writeChar(i, j, L"┴");
            else if (j == y + sl && i == x)
                writeChar(i, j, L"└");
            else if (j == y + sl && i == x + c)
                writeChar(i, j, L"┘");
            else
                writeChar(i, j, L"│");
        } else if (j == y || j == y + 2 || j == y + sl) {
            writeChar(i, j, L"─");
        }
    }
    }
writeString(x + 8, y + 1, L"Mã Sách");
writeString(x + 30, y + 1, L"Tên Sách");
writeString(x +60, y + 1, L"Thể Loại");
writeString(x + 85, y + 1, L"Tên Tác Giả");
writeString(x + 104, y + 1, L"Năm xuất bản");
writeString(x + 125, y + 1, L"SL");
writeString(x + 136, y + 1, L"Giá Bán");
	//writeString(x + 40, y - 1, L"Nhấn ESC để quay trở lại ");
    if(sum>1){
	writeString(x + 3, y + 24, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!");
	writeString(x + 135, y - 2, L"Trang: ");
	wcout << number << L"/" << sum;
    }
}
inline void bangsanpham(int x, int y, int sl)
{ 
    int i, j;
    int c = 150;
    sl=sl+3;
    for (i = x; i <= x + c; i++) {
    for (j = y; j <= y + sl; j++) {
        if (i == x || i == x + 20 || i == x + 50 || i == x + 80 || i == x + 100 ||
            i == x + 120 || i == x + 130|| i == x + c) {

            // Drawing corners and intersections for clean table look
            if (j == y && i != x && i != x + c)
                writeChar(i, j, L"┬");
            else if (j == y && i == x)
                writeChar(i, j, L"┌");
            else if (j == y && i == x + c)
                writeChar(i, j, L"┐");
            else if (j == y + 2 && i != x && i != x + c)
                writeChar(i, j, L"┼");
            else if (j == y + 2 && i == x)
                writeChar(i, j, L"├");
            else if (j == y + 2 && i == x + c)
                writeChar(i, j, L"┤");
            else if (j == y + sl && i != x && i != x + c)
                writeChar(i, j, L"┴");
            else if (j == y + sl && i == x)
                writeChar(i, j, L"└");
            else if (j == y + sl && i == x + c)
                writeChar(i, j, L"┘");
            else
                writeChar(i, j, L"│");
        } else if (j == y || j == y + 2 || j == y + sl) {
            writeChar(i, j, L"─");
        }
    }
    }
writeString(x + 5, y + 1, L"Mã Sách");
writeString(x + 30, y + 1, L"Tên Sách");
writeString(x +60, y + 1, L"Thể Loại");
writeString(x + 85, y + 1, L"Tên Tác Giả");
writeString(x + 104, y + 1, L"Năm xuất bản");
writeString(x + 125, y + 1, L"SL");
writeString(x + 136, y + 1, L"Giá Bán");
}
inline void menuDisplay2(int x, int y, int sl, int number = 1, int sum = 1) {
 int i, j;
    int c = 120;
    for (i = x; i <= x + c; i++) {
    for (j = y; j <= y + sl; j++) {
        if (i == x || i == x + 20 || i == x + 50 || i == x + 80 || i == x + 100 ||
             i == x + c) {

            // Drawing corners and intersections for clean table look
            if (j == y && i != x && i != x + c)
                writeChar(i, j, L"┬");
            else if (j == y && i == x)
                writeChar(i, j, L"┌");
            else if (j == y && i == x + c)
                writeChar(i, j, L"┐");
            else if (j == y + 2 && i != x && i != x + c)
                writeChar(i, j, L"┼");
            else if (j == y + 2 && i == x)
                writeChar(i, j, L"├");
            else if (j == y + 2 && i == x + c)
                writeChar(i, j, L"┤");
            else if (j == y + sl && i != x && i != x + c)
                writeChar(i, j, L"┴");
            else if (j == y + sl && i == x)
                writeChar(i, j, L"└");
            else if (j == y + sl && i == x + c)
                writeChar(i, j, L"┘");
            else
                writeChar(i, j, L"│");
        } else if (j == y || j == y + 2 || j == y + sl) {
            writeChar(i, j, L"─");
        }
    }
    }
writeString(x + 10, y + 1, L"Mã KH");
writeString(x + 30, y + 1, L"Họ và tên");
writeString(x +60, y + 1, L"Địa chỉ");
writeString(x + 85, y + 1, L"SĐT");
writeString(x + 104, y + 1, L"số tiền đã mua");
	writeString(x + 40, y - 1, L"Nhấn ESC để quay trở lại ");
    if(sum>1){
	writeString(x + 3, y + 24, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!");
	writeString(x + 135, y - 2, L"Trang: ");
	wcout << number << L"/" << sum;
    }
}
inline void Ordertable(int x, int y, int sl)
{
    int i, j;
    int c = 100;
    sl=sl+3;
    for (i = x; i <= x + c; i++) {
    for (j = y; j <= y + sl; j++) {
        if (i == x ||  i == x + 10 ||i == x + 40 || i == x + 60 || i == x + 80 || i == x + 100 || i == x + c) {

            // Drawing corners and intersections for clean table look
            if (j == y && i != x && i != x + c)
                writeChar(i, j, L"┬");
            else if (j == y && i == x)
                writeChar(i, j, L"┌");
            else if (j == y && i == x + c)
                writeChar(i, j, L"┐");
            else if (j == y + 2 && i != x && i != x + c)
                writeChar(i, j, L"┼");
            else if (j == y + 2 && i == x)
                writeChar(i, j, L"├");
            else if (j == y + 2 && i == x + c)
                writeChar(i, j, L"┤");
            else if (j == y + sl && i != x && i != x + c)
                writeChar(i, j, L"┴");
            else if (j == y + sl && i == x)
                writeChar(i, j, L"└");
            else if (j == y + sl && i == x + c)
                writeChar(i, j, L"┘");
            else
                writeChar(i, j, L"│");
        } else if (j == y || j == y + 2 || j == y + sl) {
            writeChar(i, j, L"─");
        }
    }
    }
writeString(x + 2, y + 1, L"STT");
writeString(x + 15, y + 1, L"Tên sách");
writeString(x + 45, y + 1, L"Số lượng");
writeString(x +65, y + 1, L"Đơn giá");
writeString(x + 85, y + 1, L"Thành tiền");
}