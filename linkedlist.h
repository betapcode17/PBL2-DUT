#pragma once
#include <iostream>
#include "book.h"
#include "customer.h"
using namespace std;
class BookNode
{
public:
    Book data;
    BookNode *next;
    BookNode(const Book &book) : data(book), next(nullptr) {}
    BookNode() : next(NULL) {}
};
class CustomerNode
{
public:
    Customer data;
    CustomerNode *next;
    CustomerNode() : next(NULL) {}
};
class LinkedList
{
private:
    BookNode *bookHead;
    CustomerNode *customerHead;

public:
    LinkedList();
    ~LinkedList();
    bool isEmpty();
    void readBook(const string &fileName);
    void search_book(int);
    void readCustomer(const string &fileName);
    void displayCustomer();
    int length_Of_List();
    void outputBook(int, int, const Book &);
    void outputCustomer(int, int, const Customer &);
    int find_Node(const string &);
    Book getNodeBook(int);
    int find_Node(Book);
    bool delete_Node(Book);
    void DeleteList(BookNode *);
    BookNode *CloneList(BookNode *);
    void Sort(bool (*q)(int, int), int i, BookNode *);
    void Sort_BookUporDown(int i, int t);
    void ShowAllBook(int, BookNode *);
    BookNode *read(string, int);
    bool UpdateBook();
    bool DeleteBook();
    bool isUniqueBookID(const string &bookID);
    string getValidInput(int x, int y);
    bool CreateBook();
    bool Insert_NodeLast(Book);
    bool Insert_NodeMiddle(Book, int);
    void statistical();
    int find_NodeCustomer(Customer);
    bool Add_Customer(Customer);
    Book *getNode(int position);
    Customer *getNodeCustomer(int position);
    int find_NodeCustomer(const string &);
    void Order();
    void Add_Product(Book ***bookCode, int **bookCount, int &types);
    void confirm(Book **bookCode, int *bookCount, int types);
    void bill(Book **bookCode, int *bookCount, int types);
    long long Calculator(Book **bookCode, int *bookCount, int types);
};