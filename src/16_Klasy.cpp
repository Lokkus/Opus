/*
 * 16_Klasy.cpp
 *
 *  Created on: 6 pa? 2020
 *      Author:
 */


#include "main.h"

class TKlasa
{
    int a;
public:
    TKlasa(int aa=2):a(aa){}
    int getParam()
    {
        return a;
    }
    void setParam(int a)
    {
        this->a = a;
    }
    ~TKlasa()
    {
        cout<<"Destruktor: a = "<<a<<endl;
    }
};

constexpr double pole_kola(const int promien)
{
    return 3.14 * promien * promien;
}

// tutaj przyklady jak mozna pracowac ze statycznymi skladnikami klasy
class TKlasaStatic
{
public:

    // uwaga ooglna
    // mozna opuszczac definicje statycznych skladnikow w klasie ale nie mozna
    // potem korzystac z tych zmiennych przeslanych przed adres

    static int a; //definicja poza cialem klasy
    static const int b = 4; //  w tym przypadku mozna zainicjalizowac skladnik w klasie bo ma const
    static constexpr int c = 100; // to trzeba zdefiniowac w klasie bo ma constexpr poza tym musi to byc typ literalny
    static constexpr double d = 12.44;

    // przyklady niewlasciwych definicji
    // static const double z = 12.4; //musi byc typ calkowity
    static constexpr double trzy_pola = 3 * pole_kola(5); // to jest ok pod warunkiem ze funkcjia pole_kola bedzie typu constexpr
};

//definiujemy skladnik statyczny "normalny"
int TKlasaStatic::a = 123;

// stalu obiekt (const)

class TKlasaConst
{
public:
    const int a = 4;
    mutable int b = 0;
    int pobierz() const
    {
        b++; // bez slowa mutable przy zmiennej b, to sie nie skompiluje
        return a;
    }
    void zwykla_fukcja()
    {
        cout<<"Zwykla funkcja"<<endl;
    }
};

void testowanie_obiektu_const()
{
    const TKlasaConst obj;
    cout<<obj.pobierz();
    // ale
    // obj.zwykla_fukcja(); //  to sie nie skompiluje

    TKlasaConst obj_nie_const;
    cout<<obj_nie_const.pobierz()<<endl;
    obj_nie_const.zwykla_fukcja();
}

// klasa bedaca agregatem

class TKlasaAgregat
{
public:
    // w agregacie wszystkie dane musza byc publiczne
    string nazwa;
    int n;
    void pokaz_dane()
    {
        cout<<"Nazwa: "<<nazwa<<" dana: "<<n<<endl;
    }
};

void test_agregatu()
{
    TKlasaAgregat obj1 {"Obj 1", 123};
    TKlasaAgregat obj2 = {"Obj_2", 333};

    vector<TKlasaAgregat*> ptr_agr;
    ptr_agr.push_back(&obj1);
    ptr_agr.push_back(&obj2);
    for (auto a : ptr_agr)
    {
        a->pokaz_dane();
    }
}

void sposoby_tworzenia_obiektow()
{

    TKlasa k1;
    TKlasa k2 = TKlasa(); // ale bez nawiasow sie nie da
    TKlasa k3(123);
    TKlasa k4 = TKlasa(234);

    // mozna tez uzyc wskaznikow do definicji obiektow na stercie
    TKlasa* ptr_k1 = new TKlasa;
    TKlasa* ptr_k2 = new TKlasa();
    TKlasa* ptr_k3 = new TKlasa(555);

    delete ptr_k1;
    delete ptr_k2;
    delete ptr_k3;

    // mozna jeszcze uzywac konstruktorow kopiujacych i kopiujacych operatorw przypisania - pozniej
}

// funkcje constexpr w klasach

class TKlasaConstexpr
{
public:
    int x, y;
    constexpr TKlasaConstexpr przesun(int dx, int dy) const
    {
        return {x + dy, y + dy};
    }
    constexpr bool czy_pozycja(TKlasaConstexpr punkt) const
    {
        return (x == punkt.x && y == punkt.y) ? true : false;
    }
};

void test_constexpr()
{
    constexpr TKlasaConstexpr obj1 {1,1};
    constexpr TKlasaConstexpr obj2 = obj1.przesun(1, 4);
    cout<<"Czy takie same? "<<obj2.czy_pozycja(obj1);

}

void klasy_test()
{
    //sposoby_tworzenia_obiektow();
    //testowanie_obiektu_const();
    //test_agregatu();
    test_constexpr();
}

