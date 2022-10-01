/*
 * 04_Operatory.cpp
 *
 *  Created on: 29 wrz 2020
 *      Author:
 */
#include "main.h"

//zmien 11 na liczbe parzysta a program sie nie skompiluje
constexpr int zmienna = 11;
//testowanie static_assert

void static_assert_switch(int nr)
{
    switch(nr)
    {
        case 1: break;
        case 2:
            //zmien 4 na liczbe inna a program sie nie skompiluje
            static_assert(sizeof(int) == 4, "Sizeof(int) musi byc = 4");
            break;
        default: break;
    }
}

void static_assert_test()
{
    static_assert((zmienna % 2) != 0, "Zmienna musi byc parzysta");

}

//operator alignof
void operatory_sprawdzenie_wyrownania()
{
    int wyrownanie = alignof(int);
    cout<<"Wyrowanie = "<<wyrownanie<<endl;
    alignas(32) int a[4] = {1,2,3,4};
    for (int i = 0; i < 4; i++)
    {
        cout<<"Adres a ["<<i<<"] = "<<&a[i]<<endl;
    }

    struct alignas(32) t
    {
        int a[1];
    };
    t tt;
    t tt2;

    cout<<"Adres of tt: "<<&tt<<endl;
    cout<<"Adres of tt2: "<<&tt2<<endl;

}

// static_cast oraz reinterpret_cast
void operatory_rzutowania()
{
    // static_cast i //reinterpret_cast
    uint32_t x = 0x04030201;
    uint8_t* ptr = reinterpret_cast<uint8_t*>(&x);
    for (int i = 0; i<4; i++)
    {
        cout<<static_cast<int>(*ptr)<<endl;
        ptr++;
    }

    // const_cast w ten sposob mozna uzmiennic wskaznik ale nie stala
    const int stala = 100;
    const int* ptr_stala = &stala;
    int* ptr_zwykly = nullptr;

    cout<<"Stala przed zmiana= "<<stala<<endl;
    // zmieniamy stala
    ptr_zwykly = const_cast<int*>(ptr_stala);
    *ptr_zwykly = 0;
    cout<<"Stala po zmianie= "<<*ptr_stala<<endl;// ??
    cout<<"Stala po zmianie= "<<stala<<endl;

}

// reinterpret_cast jeszcze raz - przyklad z klasami
void reinterpret_cast_przyklad()
{
    class Osoba
    {
        char imie[30];
        int wiek;
    public:
        Osoba(const char* i, int w): wiek(w){
            strcpy(imie, i);
        }
        void info()
        {
            cout<<"Imie: "<<imie<<" wiek: "<<wiek<<endl;
        }
    };

    const size_t size = sizeof(Osoba);
    Osoba marcin("Marcin", 38);
    Osoba lukasz ("Lukasz", 42);


    ofstream out("Osoba.ob"); // tworzymy plik
    out.write(reinterpret_cast<char*>(&marcin), size); // zapisujemy to w sposob nieformatowany do pliku
    out.write(reinterpret_cast<char*>(&lukasz), size);
    // out.write((char*)(&marcin), size); // to samo  tylko w starym stylu
    out.close();

    char* buff1 = new char[size];
    char* buff2 = new char[size];

    ifstream in ("Osoba.ob");
    in.read(buff1, size); // przepisujemy z pliku Osoba.ob do stworzonego wczesniej bufora
    in.read(buff2, size);
    in.close();

    Osoba* os1 = reinterpret_cast<Osoba*>(buff1);
    Osoba* os2 = reinterpret_cast<Osoba*>(buff2);

    os1->info();
    os2->info();

    delete[] buff1;
    delete[] buff2;
}


// to bedzie wolane w main
void operatory_test()
{
    //operatory_sprawdzenie_wyrownania();
    operatory_rzutowania();
    //reinterpret_cast_przyklad();
}



