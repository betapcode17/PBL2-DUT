#include "linkedlist.h"
#include "Book.h"
#include "Users.h"
#include "HeThong.h"
#include "menu.h"
LinkedList L;
Users users;
using namespace std;
void Start()
{
    L.readBook("books.txt");
    L.readCustomer("customers.txt");
}
void ShowMenuAdmin()
{
    int choice;
    bool exitFlag = false;

    while (!exitFlag)
    {
        system("cls");
        choice = MENU(menu, menuSize, 41, 9, 28, 2, 40, 7, 30);
        switch (choice)
        {
        case 0:
        {
            bool crudMenuExit = false;
            while (!crudMenuExit)
            {
                system("cls");
                int i = MENU(menuCRUD, menuCRUDSize, 41, 9, 30, 2, 40, 7, 40);
                switch (i)
                {
                case 0:
                { // "Xem thong tin cua sach"
                    bool readMenuExit = false;
                    while (!readMenuExit)
                    {
                        system("cls");
                        int b = MENU(menuRead, menuReadSize, 41, 9, 30, 2, 40, 7, 45);

                        switch (b)
                        {
                        case 0:
                        {
                            BookNode *book;
                            L.ShowAllBook(1, book);
                            break;
                        }
                        case 1:
                        { // tìm kiếm sách
                            bool searchMenuExit = false;
                            while (!searchMenuExit)
                            {
                                system("cls");
                                int s = MENU(menuSearch, menuSearchSize, 41, 9, 30, 2, 40, 7, 40);

                                switch (s)
                                {
                                case 0:
                                    // tìm kiếm sách theo tên
                                    system("cls");
                                    L.search_book(1);
                                    break;
                                case 1:
                                    // tìm kiếm sách theo thể loại
                                    system("cls");
                                    L.search_book(2);
                                    break;
                                case 2:
                                    // tìm kiếm sách theo tác giả
                                    system("cls");
                                    L.search_book(3);
                                    break;
                                case 3:
                                    // tìm kiếm sách theo năm xuất bản
                                    system("cls");
                                    L.search_book(4);
                                    break;
                                case 4:
                                    searchMenuExit = true;
                                    break;
                                }
                            }
                            break;
                        }
                        case 2:
                        { // Sap xep sach
                            bool sortMenuExit = false;
                            while (!sortMenuExit)
                            {
                                system("cls");
                                int s = MENU(menuSort, menuSortSize, 41, 9, 30, 2, 40, 7, 40);

                                switch (s)
                                {
                                case 0:
                                case 1:
                                case 2:
                                {
                                    bool sortUpandDown = false;
                                    while (!sortUpandDown)
                                    {
                                        system("cls");
                                        int t = MENU(menuSortUpandDown, menuUpandDownSize, 41, 9, 30, 2, 40, 7, 40);

                                        switch (t)
                                        {
                                        case 0:
                                            L.Sort_BookUporDown(s + 1, 0); // Sort ascending
                                            system("cls");
                                            break;
                                        case 1:
                                            L.Sort_BookUporDown(s + 1, 1); // Sort descending
                                            system("cls");
                                            break;
                                        case 2:
                                            system("cls");
                                            sortUpandDown = true;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 3:
                                    sortMenuExit = true;
                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                            readMenuExit = true;
                            break;
                        }
                    }
                    break;
                }
                case 1:
                {
                    system("cls");
                    L.CreateBook();
                    break;
                }
                case 2:
                {
                    system("cls");
                    L.DeleteBook();
                    break;
                }
                case 3:
                {
                    system("cls");
                    L.UpdateBook();
                    break;
                }
                case 4:
                    crudMenuExit = true;
                    system("cls");
                    break;
                }
            }
            break;
        }
        case 1:
        {
            L.displayCustomer();
            break;
        }
        case 2:
        {
            system("cls");
            L.Order();
            break;
        }
        case 3:
        {
            // thống kê
            system("cls");
            L.statistical();
            break;
        }
        case 4:
            // thoát
            exitFlag = true;
            break;
        }
    }
}
void ShowMenuUser()
{
    int choice;
    bool exitFlag = false;
    while (!exitFlag)
    {
        system("cls");
        choice = MENU(menuUser, menuUserSize, 41, 9, 28, 2, 40, 7, 30);
        
        switch (choice)
        {
        case 0:
        { // "Xem thong tin cua sach"
            bool readMenuExit = false;
            while (!readMenuExit)
            {
                system("cls");
                int b = MENU(menuRead, menuReadSize, 41, 9, 30, 2, 40, 7, 45);

                switch (b)
                {
                case 0:
                {
                    BookNode *book;
                    L.ShowAllBook(1, book);
                    break;
                }
                case 1:
                { // tìm kiếm sách
                    bool searchMenuExit = false;
                    while (!searchMenuExit)
                    {
                        system("cls");
                        int s = MENU(menuSearch, menuSearchSize, 41, 9, 30, 2, 40, 7, 40);

                        switch (s)
                        {
                        case 0:
                            // tìm kiếm sách theo tên
                            system("cls");
                            L.search_book(1);
                            break;
                        case 1:
                            // tìm kiếm sách theo thể loại
                            system("cls");
                            L.search_book(2);
                            break;
                        case 2:
                            // tìm kiếm sách theo tác giả
                            system("cls");
                            L.search_book(3);
                            break;
                        case 3:
                            // tìm kiếm sách theo năm xuất bản
                            system("cls");
                            L.search_book(4);
                            break;
                        case 4:
                            searchMenuExit = true;
                            break;
                        }
                    }
                    break;
                }
                case 2:
                { // Sap xep sach
                    bool sortMenuExit = false;
                    while (!sortMenuExit)
                    {
                        system("cls");
                        int s = MENU(menuSort, menuSortSize, 41, 9, 30, 2, 40, 7, 40);

                        switch (s)
                        {
                        case 0:
                        case 1:
                        case 2:
                        {
                            bool sortUpandDown = false;
                            while (!sortUpandDown)
                            {
                                system("cls");
                                int t = MENU(menuSortUpandDown, menuUpandDownSize, 41, 9, 30, 2, 40, 7, 40);

                                switch (t)
                                {
                                case 0:
                                    L.Sort_BookUporDown(s + 1, 0); // Sort ascending
                                    system("cls");
                                    break;
                                case 1:
                                    L.Sort_BookUporDown(s + 1, 1); // Sort descending
                                    system("cls");
                                    break;
                                case 2:
                                    system("cls");
                                    sortUpandDown = true;
                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                            sortMenuExit = true;
                            break;
                        }
                    }
                    break;
                }
                case 3:
                    readMenuExit = true;
                    break;
                }
            }
            break;
        }
        case 1:
        {
            L.displayCustomer();
            break;
        }
        case 2:
        {
            system("cls");
            L.Order();
            break;
        }
        case 3:
        {
            // thống kê
            system("cls");
            L.statistical();
            break;
        }
        case 4:
            // thoát
            exitFlag = true;
            system("cls");
            break;
        }
    }
}
void Process()
{
    int login = users.login();
    system("cls");
    if(login==1){
    	system("cls");
    	ShowMenuAdmin();
	}else{
		system("cls");
		ShowMenuUser();
	}
    
}
int main()
{
	Start();
   //Process();
    
    // BookNode* book;
     L.UpdateBook();
//    Process();
    //system("pause");
    
	//Start();
    //L.Order();
    // menuDisplay(2,10,2,1,1);
    //	Start();
    //L.CreateBook();
   // ShowMenuAdmin();
    // Ordertable(2, 2, 10);
    // order();
    // listBook.XoaSach(2);
    // listBook.search_book(3);
    // listBook.UpdateBook();
    // system("pause");
    // bangsanpham(2, 2,6);
    // system("pause");
    // listBook.CreateBook();
}
