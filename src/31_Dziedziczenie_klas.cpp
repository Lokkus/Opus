/*
 * 31_Dziedziczenie_klas.cpp
 *
 *  Created on: 12 sty 2021
 *      Author:
 */

#include "main.h"



class Radio
{
    string nazwa;
    int cena;
public:
    Radio(string n="Default", int c=10):nazwa(n), cena(c)
    {
        cout<<"Dziala konstruktor radia"<<endl;
    }
    string daj_nazwe()
    {
        return nazwa;
    }
    int daj_cene()
    {
        return cena;
    }
};

class Pojazd
{
protected:
    Radio r;
    int ilosc_kol;
public:
    Pojazd(Radio radio, int ik):r(radio), ilosc_kol(ik)
    {
        cout<<"Dziala pierwszy konstruktor Pojazdu"<<endl;
    }
    Pojazd(string nazwa, int cena, int ik):r(nazwa, cena), ilosc_kol(ik)
    {
        cout<<"Dziala drugi konstruktor Pojazdu"<<endl;
    }
    int daj_ilosc_kol()
    {
        return ilosc_kol;
    }
    Pojazd()
    {
        ilosc_kol = 4;
        cout<<"Dziala kontruktor domyslny klasy Pojazd"<<endl;
    }
};

class Samochod_Osobowy: public Pojazd
{
protected:
    int ilosc_osob;
public:
    Samochod_Osobowy(Pojazd p, int io):Pojazd(p), ilosc_osob(io)
    {
       cout<<"Dziala kontruktor pierwszy klasy Samochod_Osobowy"<<endl;
    }
    Samochod_Osobowy(Radio r, int ik, int io):Pojazd(r, ik), ilosc_osob(io)
    {
        cout<<"Dziala kontruktor drugi klasy Samochod_Osobowy"<<endl;
    }
    Samochod_Osobowy(int io, string nazwa, int cena, int ik):Pojazd(nazwa, cena, ik),
            ilosc_osob(io)

    {
        cout<<"Dziala kontruktor trzeci klasy Samochod_Osobowy"<<endl;
    }
    Samochod_Osobowy()
    {
        ilosc_osob = 5;
        cout<<"Dziala konstruktor domyslny klasy Samochod_Osobowy"<<endl;
    }
};

class Toyota : public Samochod_Osobowy
{
    string nazwa_samochodu;
public:
    Toyota(Samochod_Osobowy so, string ns):Samochod_Osobowy(so), nazwa_samochodu(ns)
    {
        cout<<"Dziala konstruktor pierwszy klasy Toyota"<<endl;
    }
    Toyota(Pojazd p, int ik, string ns):Samochod_Osobowy(p, ik), nazwa_samochodu(ns)
    {
        cout<<"Dziala konstruktor drugi klasy Toyota"<<endl;
    }
    Toyota(Radio r, int ik, int io, string ns):Samochod_Osobowy(r, ik, io), nazwa_samochodu(ns)
    {
        cout<<"Dziala konstruktor trzeci klasy Toyota"<<endl;
    }
    Toyota(int io, string nazwa, int cena, int ik, string ns):Samochod_Osobowy(
            io, nazwa, cena, ik), nazwa_samochodu(ns)
    {
        cout<<"Dziala konstruktor czwarty klasy Toyota"<<endl;
    }
    Toyota()
    {
        nazwa_samochodu = "Toyota";
        cout<<"Dziala konstruktor domyslny klasy Toyota"<<endl;
    }

    void wypisz()
    {
        cout<<"Nazwa samochodu: "<<nazwa_samochodu<<endl;
        cout<<"Ilosc osob: "<<ilosc_osob<<endl;
        cout<<"Ilosc kol: "<<ilosc_kol<<endl;
        cout<<"Parametry radia: nazwa: "<<r.daj_nazwe()<<" cena: "<<r.daj_cene()<<endl;
    }
};

void prosty_przyklad_dziedziczenia()
{
    //Toyota t;
    //t.wypisz();

    //Toyota t1(Samochod_Osobowy(), "Auris");
    //t1.wypisz();

//    Toyota t2(Samochod_Osobowy(Radio(), 4, 5), "Auris2");
//    t2.wypisz();
//    Toyota t2(Samochod_Osobowy(Pojazd(Radio("Kasprzak", 1234), 4), 5), "Auris2");
//    t2.wypisz();

    Toyota t3(Pojazd(Radio("Lampowe", 555), 4), 5, "Avensis");
    t3.wypisz();
}

/******************************************************************************/
/*
 * przyklad kodu wykorzystujacego kopiujace opearatory przypisania oraz kopiujace
 * konstruktory i przenoszace opearatory
 */

class UrzadzenieMechaniczne
{
protected:
    int* nastawy;
    int cena;
    static constexpr int rozmiar = 10;
public:
    UrzadzenieMechaniczne(int c):nastawy(new int[rozmiar]), cena(c){}

    UrzadzenieMechaniczne(const UrzadzenieMechaniczne&); // konstr kopiujacy
    UrzadzenieMechaniczne& operator=(const UrzadzenieMechaniczne& um);
    UrzadzenieMechaniczne(UrzadzenieMechaniczne&&);
    UrzadzenieMechaniczne& operator=(UrzadzenieMechaniczne&& odzysk);

    void zmien_pozycje(int x, int y)
    {
        nastawy[0] = x;
        nastawy[9] = y;
    }

    void ogarnij_nastawy()
    {
        for (int i = 0; i<rozmiar; i++)
        {
            nastawy[i] = i*10 + 1;
        }
    }
};

UrzadzenieMechaniczne::UrzadzenieMechaniczne(const UrzadzenieMechaniczne& wzor)
{
    cena = wzor.cena;
    nastawy = new int[rozmiar];
    for (int i = 0; i<rozmiar; i++)
    {
        nastawy[i] = wzor.nastawy[i];
    }
}

UrzadzenieMechaniczne& UrzadzenieMechaniczne::operator =(const UrzadzenieMechaniczne& um)
{
    if (this != &um)
    {
        delete [] nastawy;
        cena = um.cena;
        nastawy = new int[rozmiar];
        for (int i = 0; i<rozmiar; i++)
        {
            nastawy[i] = um.nastawy[i];
        }
    }
    return *this;
}

UrzadzenieMechaniczne::UrzadzenieMechaniczne(UrzadzenieMechaniczne&& odzysk)
{
    cena = odzysk.cena;
    nastawy = odzysk.nastawy;
    odzysk.nastawy = nullptr;
}

UrzadzenieMechaniczne& UrzadzenieMechaniczne::operator =(UrzadzenieMechaniczne&& odzysk)
{
    cout<<"Dziala przenoszacy operator= (&&)"<<endl;
    if (this != &odzysk)
    {
        delete [] nastawy;
        cena = odzysk.cena;
        nastawy = odzysk.nastawy;
        odzysk.nastawy = nullptr;
    }
    return *this;
}


class Pralka : public UrzadzenieMechaniczne
{
    string kolor;
public:
    Pralka(string col, int cena):UrzadzenieMechaniczne(cena), kolor(col){}
    Pralka(const Pralka&);
    Pralka& operator=(const Pralka& pralka);
    Pralka(Pralka&&);
    Pralka& operator=(Pralka&& pralka);
    void pokaz()
    {
        cout<<"Kolor: "<<kolor<<endl;
        for (int i = 0; i<rozmiar; i++)
        {
            cout<<nastawy[i]<<"\t";
        }
        cout<<endl;
    }
};

/*
 * definicja konstruktora kopiujacego
 */
Pralka::Pralka(const Pralka& pralka):UrzadzenieMechaniczne(pralka)
{
    kolor = pralka.kolor;
}

/*
 * Definicja kopiujacego operatora przypisania
 */
Pralka& Pralka::operator =(const Pralka& pr)
{
    if (this != &pr)
    {
        UrzadzenieMechaniczne::operator =(pr);
        kolor = pr.kolor;
    }
    return *this;
}

/*
 * Definicja konstruktora przenoszacego
 */

Pralka::Pralka(Pralka&& odzysk):UrzadzenieMechaniczne(move(odzysk))
{
    kolor = odzysk.kolor;
}

Pralka& Pralka::operator =(Pralka&& pralka)
{
    if (this != &pralka)
    {
        UrzadzenieMechaniczne::operator =(move(pralka));
        kolor = pralka.kolor;
    }
    return *this;
}

void dziedziczenie_operatory_test()
{
    Pralka a1("biala", 2000);
    a1.ogarnij_nastawy();
    Pralka a2(a1);
    Pralka a3 ("czerwona", 1000);
    Pralka a4 ("czarna", 2345);
    a4.ogarnij_nastawy();
    Pralka a5 = move(a4); // tu dzialaj konstruktory w typ przypadku przenoszacy

    a1.pokaz();
    a2.pokaz();

    a3 = a2;
    a3.pokaz();
    a5.pokaz();

    a1 = move(a3); // tu dzialaja operatory bo nie tworzymy obiektu
    a1.pokaz();
}

/******************************************************************************/
/*
 * Dziedziczenie wielokrotne i dostep do skladnikow o tych samych nazwach
 */

class Madka
{
protected:
    int suma_pobranych_piecsetplusow;
public:
    Madka(int spp):suma_pobranych_piecsetplusow(spp){}
    int dej_na_horo_curke()
    {
       return suma_pobranych_piecsetplusow;
    }
};
class Tatel
{
protected:
    int suma_pobranych_piecsetplusow;
    int ilosc_wypitych_malpek;
public:
    Tatel(int spp, int iwm):suma_pobranych_piecsetplusow(spp), ilosc_wypitych_malpek(iwm){}
    int dej_na_piwo()
    {
        return ilosc_wypitych_malpek;
    }
    int dej_na_horo_curke()
    {
        return suma_pobranych_piecsetplusow;
    }
};
class Bombelek : public Madka, public Tatel
{
    string imie;
public:
    Bombelek(string imie, int suma_madka, int suma_tatel, int malpki):
        Madka(suma_madka), Tatel(suma_tatel, malpki), imie(imie){}
    void poka()
    {
        cout<<"Imie bombelka: "<<imie<<endl;
        cout<<"Suma pobranych pincetplusow przez madke: "<<Madka::dej_na_horo_curke()<<endl;
        cout<<"Suma pobranych pincetplusow przez tatela: "<<Tatel::dej_na_horo_curke()<<endl;
        cout<<"Ilosc wypitych malpek: "<<Tatel::dej_na_piwo()<<endl;
    }
};

void patologiczne_dziedziczenie_test()
{
    Bombelek bombelek("Dzesika", 1500, 1000, 100);
    bombelek.poka();
}

/*
 * Wskaznik lub referencja do obiektu klasy pochodnej moze byc niejawnie przeksztalcony na
 * wskaznik dostepnej klasy podstawowej
 */

class Kwadrat
{
protected:
    int bok;
public:
    Kwadrat(int b):bok(b){}
    int daj_bok() const
    {
       return bok;
    }
};

class Kwadracik : private Kwadrat // to zadziala TYLKO przy dziedziczeniu publicznym
{
public:
    Kwadracik(int b):Kwadrat(b){}
};

void oblicz_pole(const Kwadrat& kw)
{
    double pole = kw.daj_bok();
    cout<<"Pole kwadratu: "<<pole*pole<<endl;
}

void dziedziczenie_konwersje_test()
{
    Kwadracik kw(10);
    //oblicz_pole(kw); // w przypadku dziedziczenia public
    oblicz_pole(reinterpret_cast<Kwadrat&>(kw)); // w przypadku dziedziczenia private musimy zastosowac rzutowanie
}

void dziedziczenie_test()
{
    //prosty_przyklad_dziedziczenia();
    //dziedziczenie_operatory_test();
    //patologiczne_dziedziczenie_test();
    dziedziczenie_konwersje_test();

}

