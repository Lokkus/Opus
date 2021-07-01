/*
 * 30_Lambda.cpp
 *
 *  Created on: 11 sty 2021
 *      Author:
 */
#include "main.h"

void prosty_przyklad_lambdy()
{
    vector<int> vint {1,2,3,4,5,6,7,8,9};
    int ile = count_if(vint.begin(), vint.end(), [](int liczba){return (liczba % 2);});
    cout<<"Ilosc liczb nieparzystych: "<<ile<<endl;

    // jezeli chcemy przesylac jakies zmienne ze swiata do lambdy
    for (int i = 3; i<6; i++)
    {
        ile = count_if(vint.begin(), vint.end(), [i](int l){return (l > i);});
        cout<<"Liczb > "<<i<<" jest "<<ile<<endl;
    }
}

void wychwytywanie()
{
    int a = 12;
    int b = 23;

    [a, b]() mutable{ // bez mutabla by sie nie skompilowalo bo wychwycone parametry maja const niejawnie
      a++;
      b++;
      cout<<"W lambda: "<<a<<", "<<b<<endl;
    }
    ();
    cout<<"Poza lambda: "<<a<<", "<<b<<endl;
}

/*
 * Lambda uzyta w f skladowej klasy
 */

class Lambda
{
    int a;
    int b;
    int c;
public:
    Lambda(int aa=0, int bb=0, int cc=0): a(aa), b(bb), c(cc){}
    void f_skladowa();
};

void Lambda::f_skladowa()
{
    vector<int> vint {1,2,3,5};
    int res = count_if(vint.begin(), vint.end(), [this](int j) {
        a++;
        b++;
        c++;
        cout<<"a: "<<a<<endl;
        cout<<"b: "<<b<<endl;
        cout<<"c: "<<c<<endl;
        cout<<"j: "<<j<<endl;
        return(j < (a + this->b));
        }
    );
    cout<<"Res: "<<res<<endl;
}

void lambda_f_skladowa_test()
{
    Lambda l(1,1,1);
    l.f_skladowa();
}
/*
 * Tworzenie lambdy slowem kluczowym auto
 */

void lambda_auto_test()
{
    auto wypisz = [](int l){cout<<l<<", ";};
    vector<int> vint {1,2,3,4,5,6};
    for_each(vint.begin(), vint.end(), wypisz);

}

void lambda_typ_rezultatu()
{
    function<void(double)> kwadrat =
            [](double x)
            {
                cout<<"Kwadrat "<<x<<" = "<<x*x<<endl;
            };
    vector<double> vdbl {12.3, 23.5, 44.6};
    for_each(vdbl.begin(), vdbl.end(), kwadrat);
}

void lambda_rekurencja_test()
{
    vector<int> vint {1,2,3,4,5,6,7,8,9};
    function<void(int)> dwojkowy =
            [&dwojkowy](int i)
            {
                int reszta = i % 2;
                if(i > 1)
                {
                    dwojkowy(i/2);
                }
                cout<<reszta;
                return;
            };
    dwojkowy(8);
}

/*
 * Rzucanie wyjatkow z lambdy
 */

class Wyjatek
{
public:
    string info;
    int liczba;
    Wyjatek(string i, int l):info(i), liczba(l){}
};

void lambda_rzucanie_wyjatkow_test()
{
    vector<int> vint {1, 4, 9, 16, 25};
    vector<double> pierw;
    pierw.resize(vint.size());
    try
    {
        transform(
                vint.begin(), vint.end(),
                pierw.begin(),
                [](int dana) throw(Wyjatek)
                {
                    cout<<""<<dana<<", "<<flush;
                    if (dana < 0)
                    {
                        throw Wyjatek("Niedozwolona wartosc ujemna", dana);
                    }
                    return sqrt(dana);
                }
        );
        cout<<endl;
        for(auto d: pierw)
        {
            cout<<d<<", "<<flush;
        }
    }
    catch(Wyjatek& ex)
    {
        cout<<"Obliczenia przerwane bo: "<<ex.info<<" "<<ex.liczba<<endl;
    }
}

void lambda_test()
{
    //prosty_przyklad_lambdy();
    //wychwytywanie();
    //lambda_f_skladowa_test();
    //lambda_auto_test();
    //lambda_typ_rezultatu();
    //lambda_rekurencja_test();
    lambda_rzucanie_wyjatkow_test();
}
