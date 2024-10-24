#include "Book.h"
#include "customer.h"
#include <iostream>
using namespace std;

Customer::Customer()
{
}
Customer::Customer(string id, string name, string dia_chi, string sdt_KH, int so_tien_da_mua)
{
    this->Ma_KH = id;
    this->ho_ten = name;
    this->dia_chi = dia_chi;
    this->sdt_KH = sdt_KH;
    this->so_tien_da_mua = so_tien_da_mua;
}
Customer::~Customer()
{
}
string Customer::getHoTen()const
{
    return this->ho_ten;
}
string Customer::getMaKH()const
{
    return this->Ma_KH;
}
string Customer::getSdtKH()const
{
    return this->sdt_KH;
}

string Customer::getDia_chi()const
{
    return this->dia_chi;
}

int Customer::getSo_tien_da_mua()const
{
    return this->so_tien_da_mua;
}

void Customer::setDia_chi(string newDiaChi)
{
    this->dia_chi = newDiaChi;
}

void Customer::setSTDM(int newSTDM)
{
  this->so_tien_da_mua = newSTDM;
}

void Customer::setHoTen(string newHoTen)
{
    this->ho_ten=newHoTen;
}

void Customer::setMaKH(string newMaKH)
{
    this->Ma_KH = newMaKH;
}

void Customer::setSdtKH(string newSDTKH)
{
    this->sdt_KH = newSDTKH;
}
