// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz{};
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0)
        throw length_error("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw length_error("Vector size shouldn't be bigger than 10^8");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) // конструктор копирования
  {
      sz = v.sz;
      pMem = new T[sz](); // Выделили свежую
      for (int i = 0; i < sz; ++i)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept // Знаменитый вектор векторов
  {
      sz = v.sz;
      if (sz == 0)
          throw length_error("Vector size should be greater than zero");
      pMem = new T[sz](); // Это перепроверить
      for (int i = 0; i < sz; ++i)
          pMem[i] = v.pMem[i];
  }
  ~TDynamicVector() // Очистка памяти. ВАЖНО!
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v) // Оператор присваивания. Добавить обработку самоприсваивания!!!
  {
      if (this != &v){
        delete[] pMem;
        sz = v.sz;
        pMem = new T[sz]();
        for (int i = 0; i < sz; ++i){
            pMem[i] = v.pMem[i];
        }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept // Присваивание вектора векторов
  {
      if (this != &v){
          delete[] pMem;
          sz = v.sz;
          pMem = new T[sz](); // Это перепроверить
          for (int i = 0; i < sz; ++i){
              pMem[i] = v.pMem[i];
          }

      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if((ind<0)||(ind>=sz))
          throw length_error("AAAA");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      return &pMem[ind];
  }
  const T& at(size_t ind) const
  {
      return &pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if(sz != v.sz)
          return false;
      for (int i = 0; i < sz; ++i)
          if(pMem[i] != v[i])
              return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if(sz != v.sz)
          return true;
      for (int i = 0; i < sz; ++i)
          if(pMem[i] != v[i])
              return true;
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      for (int i = 0; i < sz; ++i)
          pMem[i] += val;
      return *this;
  }
  TDynamicVector operator-(double val)
  {
      for (int i = 0; i < sz; ++i)
          pMem[i] -= val;
      return *this;
  }
  TDynamicVector operator*(double val)
  {
      for (int i = 0; i < sz; ++i)
          pMem[i] *= val;
      return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if(sz != v.sz)
          throw length_error("Sizes don't match!");
      auto t = TDynamicVector<T>(*this);
      for (int i = 0; i < sz; ++i)
          t.pMem[i] += v[i];
      return t;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if(sz != v.sz)
          throw length_error("Sizes don't match!");
      auto t = TDynamicVector<T>(*this);
      for (int i = 0; i < sz; ++i)
          t.pMem[i] -= v[i];
      return t;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T())) - вынужден это закомментить, чтобы бросать exception-ы для тестов
  {
      if(sz != v.sz)
          throw length_error("Sizes don't match!");
      T S = pMem[0]*v[0];
      for (int i = 1; i < sz; ++i)
          S += pMem[i]*v[i];
      return S;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s>MAX_MATRIX_SIZE)
          throw length_error("Too large of a matrix");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if(sz!=m.sz)
          return false;
      for (int i = 0; i < sz; ++i)
          if(pMem[i]!=m[i])
              return false;
      return true;
  }
    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        if(sz!=m.sz)
            return true;
        for (int i = 0; i < sz; ++i)
            if(pMem[i]!=m[i])
                return true;
        return false;
    }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {

      for (int i = 0; i < sz; ++i)
          pMem[i] = pMem[i] * val;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
//      if(sz!=v.sz)
//          throw length_error("Sizes don't match!");
      auto t = TDynamicVector<T>(sz);
      for (int i = 0; i < sz; ++i)
          t[i] = pMem[i] * v;
      return t;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if(sz!=m.sz)
          throw length_error("Sizes don't match!");
      auto t = TDynamicMatrix<T>(*this);
      for (int i = 0; i < sz; ++i)
          t.pMem[i] = t.pMem[i] + m.pMem[i];
      return t;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if(sz!=m.sz)
          throw length_error("Sizes don't match!");
      auto t = TDynamicMatrix<T>(*this);
      for (int i = 0; i < sz; ++i)
          t.pMem[i] = t.pMem[i] - m.pMem[i];
      return t;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if(sz!=m.sz)
          throw length_error("Sizes don't match!");
      auto t = TDynamicMatrix<T>(sz);
      // Классический метод за O(n^3)
      for (int i = 0; i < sz; ++i){
          for (int j = 0; j < sz; ++j){
              T S = pMem[i][0] * m.pMem[0][j];
              for (int k = 1; k < sz; ++k) {
                  S += pMem[i][k]*m.pMem[k][j];
              }
              t[i][j] = S;
          }
      }
      return t;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      cout << "Пожалуйста, вводите матрицу построчно:" << endl;
      cout << "В каждой строке "<< v.sz <<" элементов"<< endl;
      for (int i = 0; i < v.sz; ++i)
          istr >> v[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; ++i)
          ostr << v[i] << endl;
      return ostr;
  }
};

#endif
