/*
 * 06_Funkcje.cpp
 *
 *  Created on: 30 wrz 2020
 *      Author:
 */


#include "main.h"

// alternatywny sposob deklarowania funkcji
auto fun(int a, int b) -> decltype(a)
{
    return a + b;
}

//rwartosc
void fun_rvalue(int&& zmienna)
{
    cout<<"Parametr wejsciowy przed zmiana: "<<zmienna<<endl;
    ++zmienna;
    cout<<"Parametr wejsciowy po zmianie: "<<zmienna<<endl;
}

void test_rvalue()
{
    int&& rval1 = (80+1);
    fun_rvalue(move(rval1)); // bez move to nie zadziala
    fun_rvalue(13+2);
}

void referencje_porownanie(const double& a, const double& b)
{
    cout<<((&a == &b)? "Adresy sa identyczne" : "Adresy sa rozne")<<endl;
}
void test_referencje_wytworzone_przez_auto()
{
    double x = 12.22;
    double& ref_x = x;
    const double& c_ref_x = x;

    auto v1 = x;
    auto v2 = ref_x;
    auto v3 = c_ref_x;

    x = -40;

    // w tym przypadku adresy beda rozne bo nie dalismy auto &
    referencje_porownanie(v1, x);
    referencje_porownanie(v2, ref_x);
    referencje_porownanie(v3, c_ref_x);

    auto& v4 = x;
    auto& v5 = ref_x;
    auto& v6 = c_ref_x;

    x = -40;

    // w tym przypadku adresy beda identyczne
    referencje_porownanie(v4, x);
    referencje_porownanie(v5, ref_x);
    referencje_porownanie(v6, c_ref_x);

    ref_x = 123;
    //c_ref_x = 444; to sie nie skompiluje


}
void funkcje_test()
{
    // cout<<fun(12,12);
    // test_rvalue();
    test_referencje_wytworzone_przez_auto();
}

