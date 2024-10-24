#include "Book.h"
Book::Book()
{
}
Book::Book(string id, string name, string genre, string author, int pubYear, int qty, int price)
{
    this->Ma_Sach = id;
    this->ten_sach = name;
    this->the_loai = genre;
    this->tac_gia = author;
    this->nam_xuat_ban = pubYear;
    this->so_luong = qty;
    this->gia_ban = price;
}
Book::~Book()
{
}
string Book::getTen_sach() const
{
    return this->ten_sach;
}

string Book::getThe_loai() const
{
    return this->the_loai;
}

string Book::getTac_gia() const
{
    return this->tac_gia;
}

string Book::getMa_Sach() const
{
    return this->Ma_Sach;
}

int Book::getNam_xuat_ban() const
{
    return this->nam_xuat_ban;
}

int Book::getSo_luong() const
{
    return this->so_luong;
}

int Book::getGia_ban() const
{
    return this->gia_ban;
}
void Book::SetMa_Sach(string newMa_Sach)
{
     this->Ma_Sach = newMa_Sach;
}
void Book::SetTen_sach(string newTen_sach)
{
    this->ten_sach = newTen_sach;
}

void Book::SetThe_Loai(string newThe_loai)
{
    this->the_loai = newThe_loai;
}

void Book::SetTac_Gia(string newTac_gia)
{
    this->tac_gia = newTac_gia;
}

void Book::SetNXB(int newNXB)
{
    this->nam_xuat_ban = newNXB;
}

void Book::SetSo_Luong(int newSo_Luong)
{
    this->so_luong = newSo_Luong;
}

void Book::SetGia_Ban(int newGia_Ban)
{
    this->gia_ban = newGia_Ban;
}
