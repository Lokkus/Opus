/*
 * 25_konwersje_definiowane_przez_uzytkownika.cpp
 *
 *  Created on: 11 gru 2020
 *      Author:
 */

#include "main.h"

class Zespolona
{
    double re;
    double im;
public:
    //Zespolona(double r, double i):re(r), im(i){} // f. dodaj, gdybysmy mieli tylko ten konstruktor to nie bylibysmy w stanie dodac 2 liczb double
    Zespolona(double r = 0, double i = 0):re(r), im(i){} // gdybysmy postawili explicit, byloby tak samo jak wyzej
    double pobierz_re() const
    {
        return re;
    }
    double pobierz_im() const
    {
        return im;
    }

    void ustaw_re(double r)
    {
        re = r;
    }

    void ustaw_im(double i)
    {
        im = i;
    }
};

Zespolona dodaj(const Zespolona& a, const Zespolona& b)
{
    Zespolona temp(0, 0);
    temp.ustaw_re(a.pobierz_re() + b.pobierz_re());
    temp.ustaw_im(a.pobierz_im() + b.pobierz_im());
    return temp;
}

void zespolona_test()
{
    Zespolona a(1.1, 2.2);
    Zespolona b(3.3, 4.4);
    Zespolona t = dodaj(a, b);
    cout<<t.pobierz_re()<<endl;
    cout<<t.pobierz_im()<<endl;
    cout<<"___________________________"<<endl;
    Zespolona x = dodaj(12.4, 22.5);
    cout<<x.pobierz_re()<<endl;
    cout<<x.pobierz_im()<<endl;
}
/******************************************************************************/

class Numer;
class Wspolrzedne
{
    double x;
    double y;
public:
    Wspolrzedne(double x, double y): x(x), y(y){}
    Wspolrzedne(Numer);
    double daj_x()
    {
        return x;
    }
    double daj_y()
    {
        return y;
    }
};

class Numer
{
    double num;
    string opis;
    friend Wspolrzedne::Wspolrzedne(Numer);
public:
    Numer(double n, string s)
    {
        num = n;
        opis = s;
    }
};

Wspolrzedne::Wspolrzedne(Numer n)
{
    x = n.num; // bez tej linijki: friend Wspolrzedne::Wspolrzedne(Numer); ta operacja nie bylaby mozliwa
    y = 0;
}

void wspolrzedne_test()
{
    Wspolrzedne w1 (10, 20);
    Numer n1(12, "ala ma kota");
    Wspolrzedne w2(n1);
    Wspolrzedne w3(Numer(13, "Iza ma psa"));

    cout<<"Podaj x dla w2: "<<w2.daj_x()<<endl;
    cout<<"Podaj y dla w2: "<<w2.daj_y()<<endl;

    cout<<"Podaj x dla w3: "<<w3.daj_x()<<endl;
    cout<<"Podaj y dla w3: "<<w3.daj_y()<<endl;

}
/******************************************************************************/
class X
{
    int a;
    int b;
public:
    X(int aa, int bb): a(aa), b(bb){}
    operator int()
    {
        return a;
    }
};

void fun_for_testing_operator(int x)
{
    cout<<"Parametr przekazany jako argument: "<<x<<endl;
}
void operator_test()
{
    X x(10, 20);
    fun_for_testing_operator(123);
    fun_for_testing_operator(x); // bez funkcji operatorowej w klasie nie byloby to mozliwe
}
void konwersje_definiowane_test()
{
    //wspolrzedne_test();
    operator_test();
}

