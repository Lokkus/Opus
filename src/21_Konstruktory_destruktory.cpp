/*
 * 21_Konstruktory_destruktory.cpp
 *
 *  Created on: 14 pa? 2020
 *      Author:
 */

#include "main.h"
/************************************ Explicit ****************************************/
//  tutaj chodzi o niejawne wylaczenie konwersji
class KExplicit
{
    int a;
public:
    explicit KExplicit(int skl):a(skl){}
    int get()
    {
        return a;
    }
};

// defuniujemy sobie jakas funkcje ktora przyjmuje jako argument obiejt klasy KExplicit
void explicit_fun(KExplicit ex)
{
    KExplicit temp = ex;
    cout<<temp.get()<<endl;
}

void explicit_test()
{
    explicit_fun(KExplicit(12));
    // explicit_fun(5); // to sie nie skompiluje bo slowo explicit tego zabrania
}
/************************************ Explicit ****************************************/
/********************** Konstruowanie obiektow ****************************************/
namespace Konstruowanie_obiektow{
    // przekazywanie obiektow przez this
    class KMoja;
    void przekazywanie_obiektu(KMoja* ptr);

    // definiujemy sobie jakas klase:
    class KMoja
    {
        int a;
        string napis;
    public:
        KMoja(int a = 0, string napis = "");
        void show()
        {
            cout<<"Napis: "<<napis<<endl;
            cout<<"Zmienna: "<<a<<endl;
        }
        void wywolaj_przekazywanie_obiektu()
        {
            przekazywanie_obiektu(this); // gwozdz programu
        }
    };
    KMoja::KMoja(int a, string napis)
    {
        this->a = a;
        this->napis = napis;
    }

    void przekazywanie_obiektu(KMoja* ptr)
    {
        ptr->show();
    }

    void konstruowanie_obiektow_test()
    {
        KMoja km(12, "Ala ma kota"); // jawne konstruowanie obiektu
        km.wywolaj_przekazywanie_obiektu();

        //KMoja* ptr_KMoja = &km; // jak wskaznik

        //KMoja* ptr_new = new KMoja; // tu wywola sie konstruktor domyslny
        KMoja* ptr_new_params = new KMoja(654, "Jakis napis");
        ptr_new_params->wywolaj_przekazywanie_obiektu();
        // Ale
        //KMoja km_obj = KMoja(); // tutaj musza byc te nawiasy ( w przeciwienstiwe do new)
    }
}
    /*********************************************************************************/
namespace Lista_Inicjalizacyjna{
    // Lista inicjalizacyjna
    class KListaInicjalizacyjna
    {
        int &ref;
        const int const_i;
    public:
        // referencje i consty musza byc inicjalizowane w ten sposob
        // co wazne, znaczek & musi wystepowac takze na liscie konstrukora
        KListaInicjalizacyjna(int& rr, int c):ref(rr), const_i(c){}
        int wez_referencje()
        {
            return ref;
        }
        void zmien_referencje()
        {
            ref += 100;
        }
    };

    void fun_lista_inicjalizacyjna_test()
    {
        int zmienna = 12;
        KListaInicjalizacyjna kli(zmienna, 123);
        cout<<"zmienna: "<<zmienna<<endl;
        zmienna += 123;
        cout<<"zmienna po zmianie: "<<kli.wez_referencje()<<endl;
        kli.zmien_referencje();
        cout<<"Zmienna lokalna po zmianie w klasie: "<<zmienna<<endl;
    }

    /************* wyjatki rzucane z listy inicjalizacyjnej *******************/
    class Podstawowa
    {
        unique_ptr<double> ptr_d = nullptr;
        long long size;
    public:
        Podstawowa(long s) try : ptr_d(new double[s]), size(s){}
        catch (exception& e)
        {
            cerr<<"Wyjatek typu "<<e.what()<<" z listy inicjalizacyjnej klasy Pochodna"
                    <<endl;
        }
    };

    class Pochodna : public Podstawowa
    {
    public:
        Pochodna(long s) try : Podstawowa(s){}
        catch (exception& e)
        {
            cerr<<"Wyjatek typu "<<e.what()<<" z listy inicjalizacyjnej klasy Podstawowa"
                    <<endl;
        }
    };

    void wyjatki_rzucane_z_listy_inicjalizacyjnej_test()
    {
        try
        {
            Podstawowa obj1(10000000000);
        }
        catch(...)
        {
            cout<<"Zlapany wyjatek od Podstawowej"<<endl;
        }
    }
}

namespace Konstruktor_delegujacy
{
    class KDelegat
    {
        const int down;
        const int up;
        string name;
    public:
        KDelegat(int d, int u, string n): down{(d < u) ? d : u},
            up{(d < u)? u : d}, name(n){}
        // za lista inicjalizacyjna umieszcza sie konstruktor delegujacy
        // const - mozna w ten sposob zadelkarowac stale
        KDelegat() : KDelegat{0, 123, "Ala ma kota"}{}
        KDelegat(string n, int up) : KDelegat{0, up, n}{}
        KDelegat(int down) : KDelegat{down, 555, "Whatever"}{}

        void get_data()
        {
            cout<<"Down: "<<down<<" Up: "<<up<<" Name: "<<name<<endl;
        }
    };

    void konstruktor_delegujacy_test()
    {
        vector<KDelegat> delegat = {{1,5, "Ala"},
                                    {},
                                    {32, 1, "Ola"},
                                    {1},
                                    {"Iza", 13}};
        for (auto& a: delegat)
        {
            a.get_data();
        }
    }
}

namespace Lista_inicjalizatorow
{
    class Temperatury
    {
        long ile_pomiarow;
        int* dane;
        string termin_pomiarow;

    public:
        // konstruktor z lista inicjalizatorow
        Temperatury(initializer_list<int> pomiary)
        {
            ile_pomiarow = pomiary.size();
            dane = new int[ile_pomiarow];
            int i = 0;
            for (auto t: pomiary)
            {
                dane[i++] = t;
            }
        }
        ~Temperatury()
        {
            if (dane) delete [] dane;
        }
        // konstruktor z lista inicjalizatorow i dodatkowym napisem
        Temperatury(initializer_list<int> pomiary, string kiedy_zrobione):Temperatury{pomiary}
        {
            termin_pomiarow = kiedy_zrobione;
        }
        void wypisz_wszystkie_pomiary()
        {
            cout<<"Wypisanie pomiarow "<<termin_pomiarow<<endl;
            for (int i = 0; i < ile_pomiarow; i++)
            {
                cout<<"["<<i<<"]= "<<dane[i]<<"\t"<<flush;
            }
            cout<<endl;
        }
    };

    void lista_inicjalizacyjna_test()
    {
        Temperatury tydzien1 {11, 12, 13, 14, 15, 16, 17};
        tydzien1.wypisz_wszystkie_pomiary();

        Temperatury tydzien2 ({23, 24, 25, 26, 27, 28}, "sprzed miesiaca");
        tydzien2.wypisz_wszystkie_pomiary();
    }
}

namespace Obiekt_skladnik
{
    class Skladnik
    {
        string nazwa;
        int wartosc;
    public:
        Skladnik(string n, int w):nazwa(n), wartosc(w){}
        string pobierz_nazwe()
        {
            return nazwa;
        }
        int pobierz_wartosc()
        {
            return wartosc;
        }
    };

    class Obiekt
    {
        Skladnik skladnik;
        int liczba;
    public:
        // pierwszy konstruktor
        // jezeli mamy zainicjalizowac obiekt innej klasy w konstruktorze
        // to MUSIMY to zrobic na liscie incjalizacyjnej
        Obiekt(Skladnik s, int l):skladnik(s), liczba(l){}
        // drugi konstruktor
        Obiekt(string s, int w, int l):skladnik(s, w), liczba(l){}
        Skladnik pobierz_skladnik()
        {
            return skladnik;
        }

    };

    class Obiekt2
    {
        unique_ptr<Skladnik> ups;
    public:
        Obiekt2(string s, int w): ups(new Skladnik(s, w)){}
        unique_ptr<Skladnik> pobierz_skladnik()
        {
            return move(ups); // unique_ptr wymaga przeniesienia wlasnosci... trzeba doczytac
        }
    };

    void Obiekt_skladnik_test()
    {
        Skladnik s("skladnik", 123);
        Obiekt o1(s, 444);
        Obiekt o2("drugi skladnik", 777, 888);
        cout<<o2.pobierz_skladnik().pobierz_nazwe()<<endl;
    }

    void Obiekt2_skladnik_test()
    {
        Obiekt2 o1("ala ma kota", 666);
        cout<<o1.pobierz_skladnik()->pobierz_nazwe()<<endl;
    }
}
namespace Konstruktor_constexpr
{
    using pixel_color = unsigned char;
    class Pixel
    {
        pixel_color red;
        pixel_color green;
        pixel_color blue;

    public:
        constexpr Pixel(pixel_color r, pixel_color g, pixel_color b):red(r), green(g), blue(b){}
        Pixel()
        {
            red = green = blue = 0;
        }

        constexpr unsigned int id() const
        {
            return (red << 16) + (green << 8) + blue;
        }

        constexpr unsigned int light_pixels() const // musi byc const
        {
            return (red ? 1 : 0) + (green ? 1 : 0) + (blue ? 1 : 0);
        }
    };

    constexpr Pixel pattern_red {255, 0, 0};
    constexpr Pixel pattern_green {0, 255, 0};
    constexpr Pixel pattern_blue {0, 0, 255};

    // constexpr Pixel p; // to sie nie skompiluje bo konstruktor Pixel nie jest constexpr

    void Konstruktor_constexpr_test()
    {
        cout<<"Wzorzec czerwony: "<<pattern_red.light_pixels()<<endl;
        cout<<"Wzorzec czerwony: "<<hex<<"0x"<<pattern_green.id()<<endl;
    }
}
namespace KO = Konstruowanie_obiektow;
namespace LI = Lista_Inicjalizacyjna;
namespace KD = Konstruktor_delegujacy;
namespace Lin = Lista_inicjalizatorow;
namespace OS = Obiekt_skladnik;
namespace KC = Konstruktor_constexpr;



/********************** Konstruowanie obiektow ****************************************/

void konstruktory_destruktory_test()
{
    //explicit_test();
    //KO::konstruowanie_obiektow_test();
    //LI::fun_lista_inicjalizacyjna_test();
    //LI::wyjatki_rzucane_z_listy_inicjalizacyjnej_test();
    //KD::konstruktor_delegujacy_test();
    //Lin::lista_inicjalizacyjna_test();
    //OS::Obiekt_skladnik_test();
    //OS::Obiekt2_skladnik_test();
    KC::Konstruktor_constexpr_test();
}


