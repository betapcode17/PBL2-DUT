#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Users.h"
#include "HeThong.h"
#include <algorithm> // For std::remove_if
#include <limits>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
using namespace std;

using namespace std;
wstring Users::getPassword()
{
    wstring password;
    char ch;
    while ((ch = _getch()) != '\r')
    { // Đọc cho đến khi nhấn Enter ('\r')
        if (ch == '\b' && password.length() > 0)
        { // Xử lý phím Backspace
            wcout << "\b \b";
            password.pop_back();
        }
        else if (ch != '\b')
        {                 // Nếu không phải Backspace, thêm vào mật khẩu
            wcout << '*'; // Hiển thị * thay vì ký tự thực
            password.push_back(ch);
        }
    }
    return password;
}

wstring Users::getName()
{
    wstring name;
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
bool Users::login()
{
    int role;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD savedAttributes;
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    savedAttributes = consoleInfo.wAttributes;

    display_login();

    while (true)
    {
        int x = 0, y = 0;
        setClick(x, y);
        // cout << x << y;
        // system("pause");
        // Check if the "forgot password" button is clicked
        if (x >= 59 && x <= 75 && y == 23)
        {
            forgot_password(); // Call forgot password and return to login
            display_login();
            continue; // Continue login loop after password recovery
        }
        // 47 --> 55
        else if (x >= 47 && x <= 55 && y == 23)
        {
            register_account(); // Call forgot password and return to login
            display_login();
            continue; // Continue login loop after password recovery
        }
        wstring username, password;

        // Get username
        while (true)
        {
            setClick(x, y);
            if (x >= 45 && x <= 75 && y >= 10 && y <= 13)
            {
                gotoXY(46, 11); // Assuming gotoXY is defined elsewhere
                username = getName();
                break;
            }
            if (x >= 59 && x <= 75 && y == 23)
            {
                forgot_password(); // Call forgot password and return to login
                display_login();
                continue;
            }
            else if (x >= 47 && x <= 55 && y == 23)
            {
                register_account(); // Call forgot password and return to login
                display_login();
                continue; // Continue login loop after password recovery
            }
        }
        while (true)
        {
            writeString(46, 11, username);
            setClick(x, y);
            if (x >= 45 && x <= 75 && y >= 15 && y <= 18)
            {
                gotoXY(46, 16);
                password = getPassword();
                break;
            }
            if (x >= 50 && x <= 60 && y == 23)
            {
                forgot_password(); // Call forgot password and return to login
                display_login();
                continue;
            }
            else if (x >= 47 && x <= 55 && y == 23)
            {

                register_account(); // Call forgot password and return to login
                display_login();
                login();
                break;
            }
        }
        // Validate login credentials
        wfstream infile("dangnhap.txt", ios_base::in);
        if (!infile.is_open())
        {
            menuTable(53, 10, 66, 4); // Assuming menuTable is defined elsewhere
            writeString(57, 12, L"Khong the mo tap tin");
            if (_getch())
                system("cls");
            return false;
        }

        int n, tempRole, i = 1;
        infile >> n;
        infile.ignore();

        bool loginSuccess = false;
        while (i <= n)
        {
            wstring fileUsername, filePassword;
            int fileRole;
            infile >> fileUsername >> filePassword >> fileRole;

            if (username == fileUsername && password == filePassword)
            {
                role = fileRole;
                loginSuccess = true;
                break;
            }
            i++;
        }
        infile.close();

        if (!loginSuccess)
        {
            SetConsoleTextAttribute(consoleHandle, 0x74);
            writeChar(55, 3, L"THONG TIN DANG NHAP KHONG CHINH XAC!!");
            SetConsoleTextAttribute(consoleHandle, savedAttributes);
            display_login(); // Re-display the login screen for another attempt
        }
        else
        {
            break; // Successful login
        }
    }
    return role;
}
void Users::setRole(int role)
{
    this->role = role;
}
void Users::forgot_password()
{
    system("cls");
    setTextColor(11);
    _setmode(_fileno(stdout), _O_U16TEXT);
    menuTable(45, 10, 40, 3);
    writeString(46, 11, L"Nhap ten dang nhap: ");
    wstring username_input;
    getline(wcin, username_input);
    wfstream infile("dangnhap.txt");
    if (!infile.is_open())
    {
        menuTable(53, 10, 70, 4);
        writeString(57, 12, L"KHÔNG THỂ MỞ TỆP TIN.");
        if (_getch())
            system("cls");
        return;
    }
    int n;
    infile >> n;
    infile.ignore();
    wfstream tempFile("temp.txt", ios::out);
    if (!tempFile.is_open())
    {
        menuTable(53, 10, 70, 4);
        writeString(57, 12, L"KHÔNG THỂ TẠO TỆP TẠM THỜI.");
        if (_getch())
            system("cls");
        return;
    }

    tempFile << n << endl; // Write the number of accounts first

    bool account_found = false;

    for (int i = 1; i <= n; i++)
    {
        wstring file_username;
        int file_password, field1; // Additional fields (e.g., role or flag)
        infile >> file_username >> file_password >> field1;
        if (username_input == file_username)
        {
            account_found = true;
            menuTable(45, 14, 40, 3);
            writeChar(46, 15, L"Nhap mat khau moi: ");
            int new_password;
            wcin >> new_password;
            tempFile << file_username << L" " << new_password << L" " << field1 << endl;
            writeChar(45, 18, L"Cap nhat mat khau thanh cong!");
        }
        else
        {
            tempFile << file_username << L" " << file_password << L" " << field1 << endl;
        }
    }
    infile.close();
    tempFile.close();
    if (account_found)
    {
        _wremove(L"dangnhap.txt");              // Remove old file
        _wrename(L"temp.txt", L"dangnhap.txt"); // Rename temp file to original file name
        while (true)
        {
            if (setKeyBoard() == 5)
            {
                system("cls");
                break;
            }
            // display_login();
            // login();
        }
    }
    else
    {
        writeString(45, 8, L"Khong ton tai tai khoan nay!!!");
        _wremove(L"temp.txt");
        while (true)
        {
            if (setKeyBoard() == 5)
            {
                system("cls");
                break;
            }
            // display_login();
            // login();
        }
    }
}
void Users::register_account()
{
    system("cls");
    setTextColor(11);
    _setmode(_fileno(stdout), _O_U16TEXT); // Enable Unicode output

    // Check for account count in file
    // Display title
    writeString(50, 8, L"THÊM TÀI KHOẢN ĐĂNG NHẬP");
    menuTable(45, 12, 40, 2);
    writeString(46, 13, L"NHẬP TÊN ĐĂNG NHẬP MỚI : ");
    // Input field for username
    menuTable(45, 16, 40, 2);
    writeString(46, 17, L"NHẬP PASSWORD : ");
    menuTable(45, 20, 40, 2);
    writeString(46, 21, L"NHẬP VAI TRÒ (ADMIN-0, USER-1) : ");
    // Validate and input username
    wstring username_input;
    bool valid_username = false;
    while (!valid_username)
    {
        gotoXY(70, 13);
        wcout << wstring(15, L' ');
        gotoXY(70, 13);
        getline(wcin, username_input);

        // Remove extra whitespace
        username_input.erase(remove_if(username_input.begin(), username_input.end(), iswspace), username_input.end());

        if (username_input.empty())
        {
            writeString(50, 24, L"TÊN ĐĂNG NHẬP KHÔNG ĐƯỢC ĐỂ TRỐNG. VUI LÒNG THỬ LẠI.");
            continue;
        }

        // Check if username already exists
        wifstream infile("dangnhap.txt");
        if (!infile.is_open())
        {
            writeString(50, 24, L"KHÔNG THỂ MỞ TỆP TIN ĐỂ KIỂM TRA.");
            return;
        }

        wstring file_line;
        bool account_exists = false;
        while (getline(infile, file_line))
        {
            wstring file_username, file_password;
            int file_role;
            wstringstream ss(file_line);
            ss >> file_username >> file_password >> file_role;

            // Trim spaces in file_username
            file_username.erase(remove_if(file_username.begin(), file_username.end(), iswspace), file_username.end());

            if (username_input == file_username)
            {
                account_exists = true;
                break;
            }
        }
        infile.close();

        if (account_exists)
        {
            writeString(40, 15, L"[TÊN ĐĂNG NHẬP ĐÃ TỒN TẠI. VUI LÒNG CHỌN TÊN KHÁC]");
        }
        else
        {
            valid_username = true;
        }
    }

    // Password input
    gotoXY(64, 17);
    wstring password_input;

    getline(wcin, password_input);

    // Role input with validation
    int Role;
    bool valid_role = false;
    while (!valid_role)
    {
        gotoXY(80, 21);
        wcout << wstring(15, L' ');
        gotoXY(80, 21);
        wcin >> Role;

        if (Role == 0 || Role == 1)
        {
            valid_role = true;
        }
        else
        {
            writeString(40, 19, L"[VAI TRÒ KHÔNG HỢP LỆ. VUI LÒNG NHẬP LẠI (ADMIN-0, USER-1)]");
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Append new account to file
    wofstream account_file("dangnhap.txt", ios::app);
    if (!account_file.is_open())
    {
        writeString(50, 24, L"KHÔNG THỂ MỞ TỆP TIN ĐỂ LƯU THÔNG TIN.");
        return;
    }
    account_file << username_input << L" " << password_input << L" " << Role << L"\n";
    account_file.close();
    int n = 0;
    wifstream infile("dangnhap.txt");
    if (!infile)
    {
        wcerr << L"Không thể mở tệp tin dangnhap.txt!" << endl;
        return;
    }
    infile >> n;
    infile.ignore();
    n += 1;
    std::ofstream outfile("dangnhap.txt", std::ios::in);
    // Update account count in file
    if (!outfile)
    {
        std::cerr << "File could not be opened for writing!" << std::endl;
        return;
    }
    outfile << n << "\n";
    outfile.seekp(0, std::ios::end);
    outfile.close();
    // Success message
    MessageBoxW(NULL, L"Bạn đã đăng ký tài khoản thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION);
}
