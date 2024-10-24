#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Users.h"
#include "HeThong.h"
using namespace std;
wstring Users::getPassword() {
	wstring password;
	char ch;
	while ((ch = _getch()) != '\r') { // Đọc cho đến khi nhấn Enter ('\r')
		if (ch == '\b' && password.length() > 0) { // Xử lý phím Backspace
			wcout << "\b \b";
			password.pop_back();
		}
		else if (ch != '\b') { // Nếu không phải Backspace, thêm vào mật khẩu
			wcout << '*'; // Hiển thị * thay vì ký tự thực
			password.push_back(ch);
		}
	}
	return password;
}

wstring Users::getName() {
	wstring name;
	char ch;
	while ((ch = _getch()) != '\r') { // Đọc cho đến khi nhấn Enter ('\r')
		if (ch == '\b' && name.length() > 0) { // Xử lý phím Backspace
			wcout << "\b \b";
			name.pop_back();
		}
		else if (ch != '\b') { // Nếu không phải Backspace, thêm vào mật khẩu
			wcout << ch; // Hiển thị * thay vì ký tự thực
			name.push_back(ch);
		}
	}
	return name;
}
bool Users::login() {
    int role;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD savedAttributes;
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    savedAttributes = consoleInfo.wAttributes;
    
    display_login();
    
    while (true) {
        int x = 0, y = 0;
        setClick(x, y);

        // Check if the "forgot password" button is clicked
        if (x >= 50 && x <= 60 && y == 23) {
            forgot_password(); // Call forgot password and return to login
            display_login();
            continue; // Continue login loop after password recovery
        }

        wstring username, password;

        // Get username
        while (true) {
            setClick(x, y);
            if (x >= 45 && x <= 75 && y >= 10 && y <= 13) {
                gotoXY(46, 11);   // Assuming gotoXY is defined elsewhere
                username = getName();
                break;
            }
            if (x >= 50 && x <= 60 && y == 23) {
                forgot_password(); // Call forgot password and return to login
                display_login();
                continue;
            }
        }
        while (true) {
             writeString(46,11, username);
            setClick(x, y);
            if (x >= 45 && x <= 75 && y >= 15 && y <= 18) {
                gotoXY(46, 16);
                password = getPassword();
                break;
            }
            if (x >= 50 && x <= 60 && y == 23) {
                forgot_password(); // Call forgot password and return to login
                display_login();
                continue;
            }
        }

        // Validate login credentials
        wfstream infile("dangnhap.txt", ios_base::in);
        if (!infile.is_open()) {
            menuTable(53, 10, 66, 4); // Assuming menuTable is defined elsewhere
            writeString(57, 12, L"Khong the mo tap tin");
            if (_getch()) system("cls");
            return false;
        }

        int n, tempRole, i = 1;
        infile >> n;
        infile.ignore();

        bool loginSuccess = false;
        while (i <= n) {
            wstring fileUsername, filePassword;
            int fileRole;
            infile >> fileUsername >> filePassword >> fileRole;

            if (username == fileUsername && password == filePassword) {
                role = fileRole;
                loginSuccess = true;
                break;
            }
            i++;
        }
        infile.close();

        if (!loginSuccess) {
            SetConsoleTextAttribute(consoleHandle, 0x74);
            writeChar(55, 3, L"THONG TIN DANG NHAP KHONG CHINH XAC!!");
            SetConsoleTextAttribute(consoleHandle, savedAttributes);
            display_login(); // Re-display the login screen for another attempt
        } else {
            break; // Successful login
        }
    } 
    return role;
}
void Users::setRole(int role)
{
    this->role=role;
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
    if (!infile.is_open()) {
        menuTable(53, 10, 70, 4);
        writeString(57, 12, L"KHÔNG THỂ MỞ TỆP TIN.");
        if (_getch()) system("cls");
        return;
    }
    int n;
    infile >> n;
    infile.ignore(); 
    wfstream tempFile("temp.txt", ios::out);
    if (!tempFile.is_open()) {
        menuTable(53, 10, 70, 4);
        writeString(57, 12, L"KHÔNG THỂ TẠO TỆP TẠM THỜI.");
        if (_getch()) system("cls");
        return;
    }

    tempFile << n << endl; // Write the number of accounts first

    bool account_found = false;

    for (int i = 1; i <= n; i++) {
        wstring file_username;
        int file_password, field1; // Additional fields (e.g., role or flag)
        infile >> file_username >> file_password >> field1;
        if (username_input == file_username) {
            account_found = true;
             menuTable(45, 14, 40, 3);
            writeChar(46, 15, L"Nhap mat khau moi: ");
            int new_password;
            wcin >> new_password;
            tempFile << file_username << L" " << new_password << L" " << field1 << endl;
            writeChar(45, 18, L"Cap nhat mat khau thanh cong!");
        } else {
            tempFile << file_username << L" " << file_password << L" " << field1 << endl;
        }
    }
    infile.close();
    tempFile.close();
    if (account_found) {
        _wremove(L"dangnhap.txt"); // Remove old file
        _wrename(L"temp.txt", L"dangnhap.txt"); // Rename temp file to original file name
        while (true) {
            if (setKeyBoard() == 5) {
                system("cls");
                break;
            }
            //display_login();
            //login();
        }
    } else {
        writeString(45, 8, L"Khong ton tai tai khoan nay!!!");
        _wremove(L"temp.txt");
        while (true) {
            if (setKeyBoard() == 5) {
                system("cls");
                break;
            }
            //display_login();
            //login();
        }
    }
}
