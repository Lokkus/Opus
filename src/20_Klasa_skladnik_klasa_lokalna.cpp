/*
 * 20_Klasa_skladnik_klasa_lokalna.cpp
 *
 *  Created on: 14 pa? 2020
 *      Author:
 */

#include "main.h"

class TGlowna
{
    class TZagniezdzona
    {
        int skl_a;
        int skl_b;
        int skl_c;
    public:
        TZagniezdzona(int a = 0, int b = 0, int c = 0): skl_a(a), skl_b(b), skl_c(c){}
        void odczytaj_skladniki()
        {
            cout<<"skl_a: "<<skl_a<<endl;
            cout<<"skl_b: "<<skl_b<<endl;
            cout<<"skl_c: "<<skl_c<<endl;
        }
    };
    vector<TZagniezdzona> vec;
    TGlowna::TZagniezdzona pobierz_obiekt(int pos)
    {
        TZagniezdzona tz;
        tz = vec.at(pos);
        return tz;
    }
public:


    void zapisz_obiekt(int a, int b, int c)
    {
        TZagniezdzona tz(a, b, c);
        vec.push_back(tz);
    }
    void pokaz_obiekt(int pos)
    {
        TZagniezdzona tz = pobierz_obiekt(pos);
        tz.odczytaj_skladniki();
    }
};

void kl_sk_test()
{
    TGlowna tg;
    tg.zapisz_obiekt(1,2,3);
    tg.zapisz_obiekt(4,5,6);
    try
    {
        tg.pokaz_obiekt(1);
    }
    catch(out_of_range& e)
    {
        cout<<e.what()<<endl;
    }

}

void klasa_skladnik_test()
{
    kl_sk_test();
}


