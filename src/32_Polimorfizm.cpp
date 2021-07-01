/*
 * 32_Polimorfizm.cpp
 *
 *  Created on: 15 sty 2021
 *      Author
 */
#include "main.h"

class Instrument
{
public:
    //Instrument(){};
    void virtual wydaj_dzwiek()
    {
        cout<<"Nieokreslony brzdek"<<endl;
    }
    virtual ~Instrument(){}
};
class Trabka : public Instrument
{
public:
    void wydaj_dzwiek()
    {
        cout<<"Gra trabka"<<endl;
    }
};

void muzyk(Instrument& co_gra)
{
    co_gra.wydaj_dzwiek();
}

void prosty_przyklad_polimorfizmu()
{
    Instrument* i = new Trabka;
    Trabka t;
    Instrument& j = t;
    i->wydaj_dzwiek();
    j.wydaj_dzwiek();
    muzyk(t);
}

/*
 * Wirtualny destruktor
 */

class Wizytowka
{
protected:
    char* imie;
    char* nazwisko;
public:
    Wizytowka(const char* i, const char* n)
    {
        imie = new char[strlen(i) + 1];
        strcpy(imie, i);
        nazwisko = new char[strlen(n) + 1];
        strcpy(nazwisko, n);
    }
    virtual
    ~Wizytowka()
    {
        cout<<"Dziala d-tor klasy Wizytowka"<<endl;
        delete [] imie;
        delete [] nazwisko;
    }
    virtual void pokaz() = 0;
};
class MojaWizytowka : public Wizytowka
{
    int telefon;
public:
    MojaWizytowka(const char* imie, const char* nazwisko, int tel):
        Wizytowka(imie, nazwisko), telefon(tel){}

    ~MojaWizytowka()
    {
        cout<<"Dziala d-tor klasy MojaWizytowka"<<endl;
    }

    void pokaz()
    {
        cout<<"Imie: "<<imie<<endl;
        cout<<"Nazwisko: "<<nazwisko<<endl;
        cout<<"Telefon: "<<telefon<<endl;
    }
};

Wizytowka* wiz;

void wirtualny_destruktor_test()
{
    wiz = new MojaWizytowka("M", "K", 777);
    wiz->pokaz();
    cout<<"nazstepny przyklad"<<endl;
    Wizytowka* wiz2;
    MojaWizytowka m_wiz("L", "R", 444);
    wiz2 = &m_wiz;
    wiz2->pokaz();
    delete wiz;
}

/*
 * Nieco bardziej zaawansowany program wykorzytujacy polimorfim
 */

class Program
{
protected:
    string name;
public:
    Program(string n=""):name(n){}
    virtual string get_name()=0;
    virtual ~Program()
    {
        cout<<"D-tor Program"<<endl;
    }
};

class Freeware : public Program
{
public:
    Freeware(string name):Program(name){}
    string get_name()
    {
        return "Program Freeware: " + name;
    }
    ~Freeware()
    {
        cout<<"D-tor Freeware"<<endl;
    }
};

class Shareware : public Program
{
    int price;
public:
    Shareware(string name, int p):Program(name), price(p){}
    void show_price()
    {
        cout<<"Price: "<<price<<endl;
    }
    string get_name()
    {
        return "Program shareware: " + name;
    }
    ~Shareware()
    {
        cout<<"D-tor Shareware"<<endl;
    }
};

void polimorfizm_test_2()
{
    vector<Program*> program;
    program.push_back(new Shareware("MS_Office", 1500));
    program.push_back(new Shareware("Windows 10", 1000));
    program.push_back(new Freeware ("Linux"));
    program.push_back(new Freeware("Meld"));

    for (auto p : program)
    {
        cout<<p->get_name()<<endl;
        try
        {
            Shareware& s = dynamic_cast<Shareware&>(*p); // jezeli chcemy uzywac dnamic_cast
            s.show_price();
        }
        catch(bad_cast& bc)
        {
            bc.what();
        }
    }

    for (auto p : program)
    {
        cout<<p->get_name()<<endl;
        Shareware* sh;
        if ((sh = dynamic_cast<Shareware*>(p)) != nullptr)
        {
            sh->show_price();
        }
    }

    for (size_t i = 0; i<program.size(); i++)
    {
        delete program[i];
    }
}

/*
 * Przyklad tworzenia obiektow w innej klasie operatorem new na bazie istniejacej klasy
 * cos a'la builder
 */

class Strunowy
{
public:
    int ile_lat;
    Strunowy():ile_lat(0){} // konstr domniemany
    virtual Strunowy* stworz_nowy_dziewiczy() = 0;
    virtual Strunowy* stworz_nowy_sklonowany() = 0;
    virtual void jestem() = 0;
    virtual ~Strunowy()
    {
        cout<<"D-tor Strunowy"<<endl;
    }
};

class Skrzypce : public Strunowy
{
    Strunowy* stworz_nowy_dziewiczy()
    {
        return new Skrzypce;
    }

    Strunowy* stworz_nowy_sklonowany()
    {
        return new Skrzypce(*this);
    }
public:
    Skrzypce(int ile = 0):Strunowy(){}
    Skrzypce(const Skrzypce& wzor)
    {
        cout<<"Dziala C-tor kopiujacy"<<endl;
        ile_lat = wzor.ile_lat;

    }

    void jestem()
    {
        cout<<"Jestem klasy skrzypce mam "<<ile_lat<<" lat"<<endl;
    }
    ~Skrzypce()
    {
        cout<<"D-tor skrzypiec"<<endl;
    }
};

void tworzenie_obiektow_test()
{
    Skrzypce sk;
    sk.jestem();

    Strunowy* ptr = &sk;
    ptr->jestem();

    Strunowy* ptr2 = ptr->stworz_nowy_sklonowany();
    ptr2->ile_lat = 100;
    ptr2->jestem();

    Strunowy& ptr3 = *ptr2;
    ptr3.ile_lat = 200;
    ptr3.stworz_nowy_dziewiczy();
    ptr3.jestem();
}



void polimorfizm_test()
{
    //prosty_przyklad_polimorfizmu();
    //wirtualny_destruktor_test();
    //polimorfizm_test_2();
    //tworzenie_obiektow_test();
}


