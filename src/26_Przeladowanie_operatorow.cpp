/*
 * 26_Przeladowanie_operatorow.cpp
 *
 *  Created on: 5 sty 2021
 *      Author:
 */

#include "main.h"

class Wektor
{
    int a;
    int b;
    int c;
public:
    Wektor(int aa = 0, int bb = 0, int cc = 0):a(aa), b(bb), c(cc){}
    Wektor operator ++()
    {
        Wektor temp(*this);
        cout<<"Dziala wersja bez inta"<<endl;
        a++;
        b++;
        c++;
        return temp;
    }
    Wektor operator ++(int)
    {
        Wektor temp(*this);
        cout<<"Dziala wersja z int"<<endl;
        a++;
        b++;
        c++;
        return temp;
    }

    void pokaz()
    {
        cout<<a<<endl;
        cout<<b<<endl;
        cout<<c<<endl;
    }
};

void przeladowanie_pre_post_inkrementacja()
{
    Wektor temp(1,2,3);
    temp.pokaz();
    temp++;
    temp.pokaz();

    Wektor t2(5,6,7);
    t2.pokaz();
    ++t2;
    t2.pokaz();
}
/*************************************************************************/
constexpr size_t operator"" _KB(unsigned long long kilabajtow)
{
    return kilabajtow * 1024;
}

void stale_doslowne()
{
    cout<<"500 Kilobajtow to dokladnie "<<500_KB<<" bajtow"<<endl;
}
/*************************************************************************/
class Osoba
{
    char* imie;
    char* nazwisko;
public:
    Osoba(char* i, char* n){
        imie = new char[strlen(i) + 1];
        nazwisko = new char [strlen(n) + 1];
        strcpy(imie, i);
        strcpy(nazwisko, n);
    }
    Osoba& operator=(const Osoba& wzor);
    Osoba(const Osoba& o);
    void pokaz()
    {
        cout<<"Imie: "<<imie<<endl;
        cout<<"Nazwisko: "<<nazwisko<<endl;
    }
};

Osoba& Osoba::operator =(const Osoba& wzor)
{
    if (&wzor != this)
    {
        cout<<"Dziala operator przypisania"<<endl;
        delete[] imie;
        delete[] nazwisko;

        imie = new char[strlen(wzor.imie)+1];
        nazwisko = new char [strlen(wzor.nazwisko) + 1];
    }
    return *this;
}

Osoba::Osoba(const Osoba& o)
{
    cout<<"Dziala konstruktor kopiujacy"<<endl;
    imie = new char[strlen(o.imie) + 1];
    nazwisko = new char[strlen(o.nazwisko) + 1];
    strcpy(imie, o.imie);
    strcpy(nazwisko, o.nazwisko);
}
void operator_przypisania_test()
{
    Osoba o(const_cast<char*>("Marcin"), const_cast<char*>("Mediator"));
    o.pokaz();
    Osoba o1(const_cast<char*>("Lukasz"), const_cast<char*>("Iksinski"));
    //o1 = o;

    Osoba o2 = o1;
    o2.pokaz();

}
/*************************************************************************/
/*
 * przyklad operatora kopiujacego
 */
#define JEST_PRZENOSZACY true
#define JEST_PRZYPISANIA true
class OpCopy
{
    string* nazwa;
public:

    OpCopy(string n);
    OpCopy(const OpCopy& wzor);
    OpCopy& operator=(const OpCopy& wzor);
#if JEST_PRZENOSZACY
    OpCopy(OpCopy&& wzor);
#endif
    ~OpCopy();
    void info();
#if JEST_PRZYPISANIA
    OpCopy& operator=(OpCopy&& wzor);
#endif
    void swap(OpCopy& wzor)
    {
        OpCopy temp = std::move(*this);
        *this = std::move(wzor);
        wzor = std::move(temp);
    }
};

OpCopy::OpCopy(string n)
{
    nazwa = new string(n);
}
OpCopy::OpCopy(const OpCopy& wzor)
{
    nazwa = new string;
    *nazwa = *(wzor.nazwa);
}
#if JEST_PRZENOSZACY
OpCopy::OpCopy(OpCopy&& wzor)
{
    cout<<"Dziala kon przenoszacy"<<endl;
    nazwa = wzor.nazwa; // przenosimy
    wzor.nazwa = nullptr; // trzeba ustawic wskazniki z wzorowego obiektu na nulle
}
#endif
OpCopy::~OpCopy()
{
    delete nazwa;
}

void OpCopy::info()
{
    cout<<nazwa<<endl;
}
// kopiujacy operator przypisania
OpCopy& OpCopy::operator=(const OpCopy& wzor)
{
    if(&wzor != this) // unikamy przypisania wzor=wzor
    {
        delete nazwa;
        nazwa = new string;
        *nazwa = *(wzor.nazwa);
    }
    return *this;
}
#if JEST_PRZYPISANIA
OpCopy& OpCopy::operator =(OpCopy&& wzor)
{
    cout<<"Dziala op przenoszacy"<<endl;
    if (&wzor != this)
    {
        delete nazwa;
        nazwa = wzor.nazwa;
        wzor.nazwa = nullptr;
    }
    return *this;
}
#endif

void przeladowanie_operator_przenoszacy_test()
{
    time_t czas_startu = time(NULL);
    vector<OpCopy> spis;
    for(int i = 0; i < 3; i++)
    {
        string nazwa = "Mediator_" + to_string(i);
        spis.insert(spis.begin(), OpCopy(nazwa));
    }
    int trwalo = time(nullptr) - czas_startu;
    cout<<"Wstawanie wizytowek na poczatek wektora trwalo: "<<trwalo<<" s"<<endl;

    czas_startu = time(nullptr);
    OpCopy imie("Marcin");
    OpCopy nazwisko ("Mediator");

    for (auto x = 1; x< 100000000; x++)
    {
        imie.swap(nazwisko);
    }
    cout<<"swap zajelo: "<<time(nullptr) - czas_startu<<" s"<<endl;
}


void przeladowanie_opearatorow_test()
{
    //przeladowanie_pre_post_inkrementacja();
    stale_doslowne();
    //operator_przypisania_test();
    //przeladowanie_operator_przenoszacy_test();
}


