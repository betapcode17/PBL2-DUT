#pragma once
#include <iostream>
#include "Book.h"
using namespace std;
class Customer {
protected:
    string ho_ten,Ma_KH,sdt_KH,dia_chi;
    int so_tien_da_mua,countCus;
public:
    Customer();
    Customer(string id, string name, string dia_chi, string sdt_KH, int so_tien_da_mua);
    ~Customer();
    string getHoTen()const;
    string getMaKH()const;
    string getSdtKH()const;
    string getDia_chi()const;
    int getSo_tien_da_mua()const;
    void setDia_chi(string);
    void setSTDM(int);
    void setHoTen(string);
    void setMaKH(string);
    void setSdtKH(string);
    // Friend class can access private members
    friend class LinkedList;
};