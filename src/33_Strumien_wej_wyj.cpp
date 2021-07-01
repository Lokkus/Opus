/*
 * 33_Strumien_wej_wyj.cpp
 *
 *  Created on: 20 sty 2021
 *      Author:
 */
#include "main.h"

void adres_wskaznika_char()
{
    char tab[] = "Napis";
    cout<<*tab<<endl; //N
    cout<<tab<<endl;  //Napis
    cout<<static_cast<void*>(tab)<<endl;
}

void wczytywanie()
{
    char tab[80];
    cin>>tab;
    cout<<tab;
}

struct A
{
    int a[10];
};

struct B
{
    int* ptr;
};

void temp()
{
    A a;
    B b;
    for (int i = 0; i < 10; i++)
    {
        a.a[i] = 10*(i+1);
    }
    b.ptr = (int*)(&a);
    for (int i = 0; i<10; i++)
        cout<<b.ptr[i]<<", ";
}


void strumien_wej_wyj_test()
{
    //adres_wskaznika_char();
    //wczytywanie();
    temp();
}

