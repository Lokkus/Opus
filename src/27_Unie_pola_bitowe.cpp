/*
 * 27_Unie_pola_bitowe.cpp
 *
 *  Created on: 11 sty 2021
 *      Author:
 */

#include "main.h"


/*
 * przyklad uni majacej skladniki z konstruktorami i destruktorami
 */
struct Szuflada
{
    union
    {
        vector<double> zestaw;
        string tekst;
    };
    enum Typ_wariantu {tryb_wektorowy, tryb_tekstowy};
    Typ_wariantu wyroznik;
public:
    Szuflada();
    ~Szuflada();
    void co_teraz_w_uni();
    Szuflada& operator=(const vector<double>& wartosc);
    Szuflada& operator=(const string& napis);
};
Szuflada::Szuflada()
{
    new(&zestaw) vector<double>;
    wyroznik = tryb_wektorowy;
}

Szuflada::~Szuflada()
{
    if(wyroznik == tryb_tekstowy)
    {
        tekst.~string();
        cout<<"destrukcja stringu"<<endl;
    }
    else
    {
        zestaw.~vector<double>();
        cout<<"destrukcja wektora"<<endl;
    }
}

void Szuflada::co_teraz_w_uni()
{
    switch(wyroznik)
    {
        case tryb_wektorowy:
            cout<<"W uni jest wektor liczb"<<endl;
            for (auto n : zestaw)
            {
                cout<<n<<", ";
            }
            cout<<endl;
            break;

        case tryb_tekstowy:
            cout<<"W uni jest tekst: "<<tekst<<endl;
            break;
    }
}
Szuflada& Szuflada::operator=(const string& napis)
{
    if (wyroznik == tryb_tekstowy)
    {
        tekst = napis;
    }
    else if(wyroznik == tryb_wektorowy)
    {
        zestaw.~vector<double>();
        new(&tekst) string(napis);
        wyroznik = tryb_tekstowy;
    }
    return *this;
}

Szuflada& Szuflada::operator =(const vector<double>& wek)
{
    if (wyroznik == tryb_wektorowy)
    {
        zestaw = wek;
    }
    else if(wyroznik == tryb_tekstowy)
    {
        tekst.~string();
        new(&zestaw) vector<double>(wek);
        wyroznik = tryb_wektorowy;
    }
    return *this;
}

void unie_test()
{
    Szuflada sz;
    sz.co_teraz_w_uni();
    sz.zestaw.push_back(3.3);
    sz.zestaw.push_back(2.2);
    sz.co_teraz_w_uni();

    sz = "Jakis sobie dlugi tekst";
    sz.co_teraz_w_uni();

    const vector<double> x = {1.1, 1.5, 1.7};
    sz = x;
    sz.zestaw[2] = 33.4;
    sz.co_teraz_w_uni();

}

/*
 * przyklad pola bitowego
 */
class PoleBitowe
{
public:
    uint8_t a : 2;
    uint8_t b : 2;
    uint8_t c : 2;
    uint8_t d : 2;
};

void pole_bitowe_test()
{
    PoleBitowe pb;
    pb.a = 0;
    pb.b = 1;
    pb.c = 2;
    pb.d = 3;
    cout<<(int)pb.a<<" "<<(int)pb.b<<" "<<(int)pb.c<<" "<<(int)pb.d<<endl;
    cout<<"Sizeof (PoleBitowe): "<<sizeof(pb)<<endl;

    // inny przyklad
    struct pociachane
    {
        uint16_t d;
        uint8_t u;
        uint8_t x;
    };
    union
    {
        uint32_t dana;
        pociachane p;
    };

    dana = 0xCAFEBABA;
    cout<<hex<<(int)p.d<<endl;
    cout<<hex<<(int)p.u<<endl;
    cout<<hex<<(int)p.x<<endl;

}

void unie_pola_bitowe_test()
{
    //unie_test();
    pole_bitowe_test();
}


