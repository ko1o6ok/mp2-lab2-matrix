// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------
int main()
{
    TDynamicMatrix<int> a(5);
    int i, j;
    //TDynamicMatrix<int>::SET_ZERO(0);
    setlocale(LC_ALL, "Russian");
    cout << "Тестирование класс работы с матрицами"
         << endl;
    for (i = 0; i < 5; i++)
        for (j = i; j < 5; j++ )
            a[i][j] =  i * 10 + j;
    a[0][0] = 1;
    cout << "Matrix a = " << endl << a ;
    cout << "Compressed matrix a"<<endl;
    auto cmp = a.compress();
    for (const auto& m:cmp) {
        for (const auto& p:m) {
            cout << "("<<p.first <<","<<p.second<<")" ;
        }
        cout << endl;
    }
    auto b = a.transpose();
    cout << "Transposed matrix a = " << endl << b << endl;
}


