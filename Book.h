#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include <iomanip>
#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
using namespace std;
class Book {
protected:
    string  ten_sach, the_loai, tac_gia,Ma_Sach;
    int so_luong, gia_ban,nam_xuat_ban;
public:
   // Book(int=-1, string="", string="", string="", int=-1, int=-1, int=-1);
    Book();
    Book(string id, string name, string genre, string author, int pubYear, int qty, int price);
    ~Book();
    string getTen_sach()const;
    string getThe_loai()const;
    string getTac_gia()const;
    string getMa_Sach()const;
    int getNam_xuat_ban()const;
    int getSo_luong()const;
    int getGia_ban()const;
    void SetMa_Sach(string);
    void SetTen_sach(string);
    void SetThe_Loai(string);
    void SetTac_Gia(string);
    void SetNXB(int);
    void SetSo_Luong(int);
    void SetGia_Ban(int);
    // Friend class can access private members
    friend class LinkedList;
    friend class Customer;
};