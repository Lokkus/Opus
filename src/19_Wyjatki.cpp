/*
 * 19_Wyjatki.cpp
 *
 *  Created on: 12 pa? 2020
 *      Author:
 */

#include "main.h"

struct Blad
{
    void co()
    {
        cout<<"Promien nie moze byc ujemny"<<endl;
    }
};
void oblicz_promien_kola(double r);

void przyklad_try()
{
    try
    {
        oblicz_promien_kola(10);
        oblicz_promien_kola(-10);
    }
    catch(Blad& b)
    {
        b.co();
    }
}

void oblicz_promien_kola(double r)
{
    if (r < 0)
    {
        cout<<"Wyjatek!"<<endl;
        Blad blad;
        throw blad;
    }
    else
    {
        cout<<"Promien kola wynosi: "<<3.1415*r*r<<endl;
    }
}
/**********************************************************************/
// przyklad z klasami - czesc 1
struct TError
{
    virtual string opis() = 0;
    virtual ~TError(){};
};

// dziedziczymy
class K1 : public TError
{
public:
    K1() = default;
    string opis()
    {
        return "Opis z klasy K1";
    }
    ~K1(){};
};

class K2 : public TError
{
public:
    K2() = default;
    string opis()
    {
        return "Opis z klasy K2";
    }

};

// jakas funkcja rzucajaca wyjatek
void funkcja_rzucaja_wyjatek(int a)
{
    if(a > 1 and a < 10)
    {
        throw K1();
    }
    if (a >= 10 and a < 20)
    {
        throw K2();
    }
}

void test_funkcja_rzucaja_wyjatek(int b)
{
    try
    {
        funkcja_rzucaja_wyjatek(b);
    }
    catch(TError& e)
    {
        cout<<e.opis()<<endl;
    }
}
// hierarchie wyjatkow

struct A
{
    string info()
    {
        return "F z klasy A";
    }
};

struct B : public A // to dziedziczenie sprawi ze wywola sie pierwszy catch, bez tego wywola sie drugi
{
    string info()
    {
        return "F z klasy B";
    }
};

void hierarchie_test()
{
    try
    {
        throw new B;
    }
    catch(A* a)
    {
        cout<<a->info()<<endl;
    }
    catch(B* b)
    {
        cout<<b->info()<<endl;
    }
}

/*******************************************************************************/
// przyklad programu do rzucania wyjatkami
// sprawdzamy w stringu symulujacym plik wartosc: klucz wartosc
// jesli klucz jest znaleziony to wtedy git, jak nie to rzucamy wyjatek

// tworzymy klasy bledow
struct TInvalid_arg
{
    string info;
};
struct TOut_of_range
{
    string info;
};

// tworzymy funkcje do ogarniecia pliku
size_t znajdz_slowo_kluczowe(string plik, string slowo)
{
    size_t pos = plik.find(slowo);
    if (pos == string::npos)
    {
        TInvalid_arg e;
        e.info = "Nie ma takiego slowa kluczowego: " + slowo;
        throw e;
    }
    return pos + slowo.size();
}
double wczytaj_parametr(string plik, string slowo)
{
    size_t pos = znajdz_slowo_kluczowe(plik, slowo);
    string pomocniczy = plik.substr(pos);
    try
    {
        double w = stod(pomocniczy);
        return w;
    }
    catch(invalid_argument& i)
    {
        TInvalid_arg e;
        e.info = "Blad wczytania wartosci liczbowej po slowie kluczowym "+slowo;
        throw e;
    }
    catch(out_of_range& o)
    {
        TOut_of_range out;
        out.info = "Blad zakresu po slowie kluczowym "+slowo;
        throw out;
    }
}

// to jest symulacja naszego maina
void rzucanie_wyjatkow_praktyczny_program()
{
    // przygotowywuje string z danymi
    string plik = R"(   Marcin      -1
                        Lukasz      234.678
                        Dorota      444.765
                        Ula         888.555
                        Dawid       109.664
                        Wiesiu      976.091)";

    // jedziemy
    double a, b, c;
    try
    {
        a = wczytaj_parametr(plik, "Marcin");
        cout<<"Wartosc a : "<<a<<endl;
        b = wczytaj_parametr(plik, "Lukasz");
        cout<<"Wartosc b : "<<b<<endl;
        c = wczytaj_parametr(plik, "Ula");
        cout<<"Wartosc c : "<<c<<endl;
        c = wczytaj_parametr(plik, "Ela");
    }
    catch(TInvalid_arg& e)
    {
        cout<<e.info<<endl;
    }

    catch(TOut_of_range& out)
    {
        cout<<out.info<<endl;
    }
}


// z tym noexcept ponizej to chodzi o to ze
// rzucenie wyjatku sprawi ze funkcja wywola terminate a nie obsluzy wyjatek
// czyli ryzykowna sytuacja nie zostanie obsluzona w catch
//  stosuje sie to wtedy zeby kod wygenerowany przez kompilator byl optymalny
void noexcept_przyklad(int a) noexcept
{
    if (a > 0 and a < 10)
    {
        TInvalid_arg i;
        i.info = "Komunikat, argument nie spelnia warunkow";
        throw i;
    }
}

void noexcept_przyklad_lapania()
{
    try
    {
        noexcept_przyklad(8);
    }
    catch(TInvalid_arg& s)
    {
        cout<<s.info;
    }
}



void wyjatki_test()
{
    //przyklad_try();
    //test_funkcja_rzucaja_wyjatek(21);
    //hierarchie_test();
    //rzucanie_wyjatkow_praktyczny_program();
    noexcept_przyklad_lapania();
}


