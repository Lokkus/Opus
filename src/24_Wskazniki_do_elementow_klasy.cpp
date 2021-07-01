/*
 * 24_Wskazniki_do_elementow_klasy.cpp
 *
 *  Created on: 11 gru 2020
 *      Author:
 */

#include "main.h"

class Przykladowa
{
    double re;
    double im;
public:
    Przykladowa():re(0), im(0){}

    // funkcje ktorych adresy bedziemy umieszczac w tablicy
    double fun1()
    {
        cout<<"fun1"<<endl;
        return 1.0;
    }
    double fun2()
    {
        cout<<"fun2"<<endl;
        return 2.0;
    }
    double fun3()
    {
        cout<<"fun3"<<endl;
        return 3.0;
    }

    // definicja tablicy wskaznikow do funkcji
    using tab_wskaz = decltype(&Przykladowa::fun1);
    tab_wskaz tab[3];

    // definicja wektora wskaznikow
    vector<decltype(&Przykladowa::fun2)> vec_wskaz;

    void wypelnij_tablice();
    void wypelnij_wektor();
    void wywolaj_funkcje(int nr)
    {
        cout<<"Wywolujemy z tablicy wskaznikow"<<endl;
        (this->*tab[nr])();
        cout<<"Wywolujemy z wektora wskaxnikow"<<endl;
        (this->*vec_wskaz[nr])();
    }
};

void Przykladowa::wypelnij_tablice()
{
    tab[0] = &Przykladowa::fun1;
    tab[1] = &Przykladowa::fun2;
    tab[2] = &Przykladowa::fun3;
}

void Przykladowa::wypelnij_wektor()
{
   vec_wskaz.push_back(&Przykladowa::fun1);
   vec_wskaz.push_back(&Przykladowa::fun2);
   vec_wskaz.push_back(&Przykladowa::fun3);
}


void wskazniki_do_funkcji_skladowych_test()
{
    Przykladowa p;
    p.wypelnij_tablice();
    p.wypelnij_wektor();
    p.wywolaj_funkcje(1);
}
