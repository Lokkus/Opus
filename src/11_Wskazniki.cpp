/*
 * 11_Wskazniki.cpp
 *
 *  Created on: 1 pa? 2020
 *      Author:
 */

#include "main.h"
struct S1
{
    int x;
    int y;
    int z;
};

struct S2
{
    char x;
    char y;
    char z;
};

struct S3
{
    void* ptr;
};


void void_ptr()
{
    S2 s2;
    S3 s3;

    s2.x = 'a';
    s2.y = 'b';
    s2.z = 'c';

    s3.ptr = &s2;
    // wysylamy to gdzies w kosmoc
    // interpretujemy to w ten sposob
    S2* s2_ptr = reinterpret_cast<S2*>(s3.ptr);
    cout<<s2_ptr->x<<endl;
}

void new_delete()
{
    // tworzymy tablice 2d

    int** tab2d;
    int w = 5;
    int k = 6;
    tab2d = new int*[w];
    for (int i = 0; i<k; i++)
    {
        tab2d[i]= new int[k];
    }
    for (int i = 0; i<w; i++)
    {
        for(int j=0; j<k; j++)
        {
            tab2d[i][j] = 100;
        }
    }
    for (int i = 0; i<w; i++)
    {
        for(int j=0; j<k; j++)
        {
            cout<<tab2d[i][j]<<"\t";
        }
        cout<<endl;
    }
    // inny przyklad
    auto* tab = new int[w][6];
    delete [] tab;
}

void new_umiejscawiajacy()
{
    int* tab = new int[9];
    int* a = new(&tab[0])int[3]; // w ten sposob mozna umiejscawiac new (new (gdzie) co) gdzie musi byc z & bo chodzi o adres
    int* b = new(&tab[3])int[3];
    int* c = new(&tab[6])int[3];
    for (int i = 0; i<3; i++)
    {
        a[i] = 200;
        b[i] = 300;
        c[i] = 400;
    }

    for(int i = 0; i<9; i++)
    {
        cout<<tab[i]<<"\t";
    }

}
long rez;
void test_new_handler_f_obslugujaca()
{
    cout<<"Pamieci zabraklo przy "<<rez<<endl;
    throw bad_alloc();
}

void test_set_new_handler()
{
    set_new_handler(test_new_handler_f_obslugujaca);
    try
    {
        for (rez = 1;; rez++)
        {
            new int[1000];
        }
    }
    catch(bad_alloc & e)
    {
        cout<<"Zlapany wyjatek "<<e.what()<<endl;
    }

}

void podwojny_wskaznik_fun(char** temp)
{
    for (int i=0; i<2; i++)
    {
        cout<<temp[i]<<endl;
    }
}

void podwojny_wskaznik()
{
    const char* t[] =
    {
            {"Ala ma kota"},
            {"Iza ma psa"}
    };

    podwojny_wskaznik_fun(const_cast<char**>(t));
}

void fun_1()
{
    cout<<"Oto fun_1"<<endl;
}
void fun_2()
{
    cout<<"Oto fun_2"<<endl;
}
void fun_3()
{
    cout<<"Oto fun_3"<<endl;
}

// wskazniki na funkcje
// mamy zwrocic wskaznik do dwuelementowej tablicy elementow typu int
int (*fun_tab())[2]
{
    static int tab[2][2] = {{1,2}, {3,4}};
    static int (*ptr_tab)[2] = tab;
    for (int i = 0; i<2; i++)
    {
        for (int j = 0; j<2; j++)
        {
            cout<<ptr_tab[i][j]<<"\t";
        }
        cout<<endl;
    }
    return ptr_tab;
}

//to samo co wyzej ale z wykorzystaniem auto i decltype
// to moze nie przejsc w c++11
auto fun_tab_2()
{
    static int tab[2][2] = {{12, 13}, {14, 15}};
    static int (*ptr_tab)[2] = tab; //wskaznik na 2 elementowa tab z elem int
    for (int i = 0; i<2; i++)
    {
        for (int j = 0; j<2; j++)
        {
            cout<<ptr_tab[i][j]<<"\t";
        }
        cout<<endl;
    }
    return ptr_tab;
}

void test_wskaznik_na_funkcje()
{

    // deklarujemy sobie wskaznik na piechote
    int(*(*ptr_to_fun)())[2] = fun_tab;
    // wolamy funkcje
    ptr_to_fun();

    // wykorzystujemy pozostale mechanizmy c++11
    using ptr_array_t = int(*(*)())[2]; // mozna to zrobic tak
    ptr_array_t ptr_array = fun_tab_2;
    ptr_array();
    cout<<"Inny sposob"<<endl;
    // albo tak
    using ptr_array2_t = decltype(&fun_tab_2); // tutaj MUSI BYC ten & bo funkcja zwraca wskaznik
    ptr_array2_t ptr_array2 = fun_tab_2;
    ptr_array2();

}
void tablica_wskaznikow_do_funkcji()
{
    using ptr_fun = void(*)(); // pierwszy sposob deklarowania aliasu
    // typedef void (*ptr_fun)();
    ptr_fun tab_fun[3] { &fun_1, &fun_2, fun_3};
    // wolamy
    for (auto a : tab_fun)
    {
        a();
    }
}



void wskazniki_test()
{
    //void_ptr();
    //new_delete();
    //new_umiejscawiajacy();
    //test_set_new_handler();
    //podwojny_wskaznik();
    //test_wskaznik_na_funkcje();
    //tablica_wskaznikow_do_funkcji();
}


