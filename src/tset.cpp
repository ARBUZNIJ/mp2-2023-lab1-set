// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    if (mp <= 0)
        throw out_of_range("Uncorrect quanity of elements");
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)          
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const noexcept// получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element is out of the set");
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element is out of the set");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element is out of the set");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание               
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return (*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField==s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tmp(BitField | s.BitField);
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem<0 || Elem >= MaxPower)
        throw out_of_range("Element is out of the universe");
    else {
        TSet tmp(*this);
        tmp.InsElem(Elem);
        return tmp;
    }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element is out of the universe");
    else {
        TSet tmp(*this);
        tmp.DelElem(Elem);
        return tmp;
    }
}

TSet TSet::operator*(const TSet &s) // пересечение                   
{
    TSet tmp(BitField & s.BitField);
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(~BitField);
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод. Форма ввода - интексы элементов, принадлежащих множеству, по окончании ввода - Ctrl+Z, Enter
{
    int tmp;
    while(!istr.eof())
    {
        istr >> tmp;
        if (istr) {
            if (tmp >= s.MaxPower || tmp < 0)
                throw out_of_range("Element is out of the set");
            s.InsElem(tmp);
        }
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    int i=0;
    for (int i = 0; i < s.MaxPower;i++)
    {
        if (s.IsMember(i))
            ostr << i << ' ';
    }
    return ostr;
}
