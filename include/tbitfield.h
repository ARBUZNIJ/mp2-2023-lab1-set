// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <bit>
#include <numeric>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
  int  BitLen; // длина битового поля - макс. к-во битов
  TELEM *pMem; // память для представления битового поля
  int  MemLen; // к-во эл-тов Мем для представления бит.поля
  const int BitsPerEl = sizeof(TELEM) * 8; //сколько бит в каждой ячейке памяти
  const int shr = int(log(BitsPerEl-1) / log(2)) + 1; //сдвиг, равносильный делению на BitsPerEl. Не удалось использовать bit_width(BitsPerEl)!
  // методы реализации
  int   GetMemIndex(const int n) const; // индекс в pМем для бита n       (#О2)
  TELEM GetMemMask (const int n) const; // битовая маска для бита n       (#О3)
public:
  TBitField(int len);                //конструктор по умолчанию           (#О1)
  TBitField(const TBitField &bf);    //конструктор копирования            (#П1)
  ~TBitField();                      // ~                                  (#С)

  // доступ к битам
  int GetLength(void) const noexcept;     // получить длину (к-во битов)   (#О)
  int GetMemLen(void) const noexcept;	  // получить к-во эл-тов Мем
  void SetBit(const int n);       // установить бит                       (#О4)
  void ClrBit(const int n);       // очистить бит                         (#П2)
  int  GetBit(const int n) const; // получить значение бита               (#Л1)

  // битовые операции
  int operator==(const TBitField &bf) const noexcept; // сравнение                 (#О5)
  int operator!=(const TBitField &bf) const noexcept; // сравнение
  TBitField& operator=(const TBitField &bf); // присваивание              (#П3)
  TBitField  operator|(const TBitField &bf); // операция "или"            (#О6)
  TBitField  operator&(const TBitField& bf); // операция "и"              (#Л2)
  TBitField  operator~(void);                // отрицание                  (#С)

  friend istream &operator>>(istream &istr, TBitField &bf);       //      (#О7)
  friend ostream &operator<<(ostream &ostr, const TBitField &bf); //      (#П4)
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2

#endif
