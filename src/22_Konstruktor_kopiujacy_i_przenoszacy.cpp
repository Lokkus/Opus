/*
 * 22_Konstruktor_kopiujacy_i_przenoszacy.cpp
 *
 *  Created on: 8 gru 2020
 *      Author:
 */

/* konstruktor kopiujacy to konstruktor postaci klasa::klasa(klasa& )
 * Wywolanie konstruktora kopiujacego na nasze zyczenie nastepuje wtedy,
 * gdy tego jawnie zazadamy, definiujac nowy obiekt w nastepujacy sposob:
 * Kobiekt_wzor;        // wczesniej zdefiniowany obiekt klasy K
 * // ...
 * K obiekt_nowy1  {obiekt_wzor}; // definicja nowego obiektu
 * K obiekt_nowy2  (obiekt_wzor);  // inna (starsza) forma zapisu
 * K obiekt_nowy3 = obiekt_wzor;   // inna (starsza) forma zapisu
 */
#include "main.h"
#define KONSTR_KOP
#define KONSTR_PRZ
namespace Konstruktor_kopiujacy
{
    class Wizytowka
    {
        char* imie;
        char* nazwisko;
    public:
        Wizytowka(const char* imie, const char* nazwisko)
        {
            size_t dl_imienia = strlen(imie);
            size_t dl_nazwiska = strlen(nazwisko);
            this->imie = new char[dl_imienia + 1];
            this->nazwisko = new char[dl_nazwiska + 1];
            strcpy(this->imie, imie);
            strcpy(this->nazwisko, nazwisko);
        }
        char* wez_imie() const
        {
            return imie;
        }

        char* wez_nazwisko() const
        {
            return nazwisko;
        }
#ifdef KONSTR_KOP
        Wizytowka(const Wizytowka& wiz)
        {
            cout<<"Dziala konstruktor kopiujacy"<<endl;
            size_t dl_imienia = strlen(wiz.wez_imie());
            size_t dl_nazwiska = strlen(wiz.wez_nazwisko());
            this->imie = new char[dl_imienia + 1];
            this->nazwisko = new char[dl_nazwiska + 1];
            strcpy(this->imie, wiz.wez_imie());
            strcpy(this->nazwisko, wiz.wez_nazwisko());
        }
#endif
#ifdef KONSTR_PRZ
        // dorzucamy konstruktor przenoszacy
        Wizytowka(Wizytowka&& r_wiz)
        {
            // kopiujemy skladniki w ten sposob
            this->imie = r_wiz.imie;
            this->nazwisko = r_wiz.nazwisko;

            //zacieramy slady
            r_wiz.imie = nullptr;
            r_wiz.nazwisko = nullptr;
            cout<<"Dziala konstruktor przenoszacy"<<endl;
        }
#endif

        void przedstaw_sie()
        {
            cout<<"Imie: "<<imie<<endl;
            cout<<"Nazwisko: "<<nazwisko<<endl;
        }
        void zmien_litere_imie(char l, size_t pos)
        {
            if (pos < strlen(imie))
            {
                imie[pos] = l;
            }
        }
    };
    // okazuje sie, ze aby konstruktor przenoszacy zadzialal, to musi byc kilka instrukcji return
    // kilka uwag
    // jezli stworzymy 1 obiekt i go zwrocimy to wtedy konstruktor przenoszacy nie zadziala
    // zadziala zwykly konstruktor
    // mozna to zmienic motajac logika jak ponizej
    // albo uzywajac std::move(obj) ale tego nie rob
    // bo obecnie kompilatory uzywaja techniki RVO czyli buduja obiekt poza stosem tak aby usprawdzic ewentualne kopiowanie
    Wizytowka daj_rwartosc(int ktory)
    {
        Wizytowka x("Iksinski", "Ygrek");
        Wizytowka y("Iksinski", "Ygrek");
        Wizytowka z("Iksinski", "Ygrek");
        if (ktory == 1)
        {
            return x;
        }
        else if (ktory == 2)
        {
            return y;
        }
        else
            return z;
    }
}

namespace KK = Konstruktor_kopiujacy;


void konstruktor_kopiujacy_i_przenoszacy()
{
//    KK::Wizytowka ala("Ala", "Ma kota");
//    ala.przedstaw_sie();
//    KK::Wizytowka ula = ala;
//    ula.przedstaw_sie();
//    // zmieniamy
//    ala.zmien_litere_imie('O', 0);
//    ala.przedstaw_sie();
//    ula.przedstaw_sie(); // tego nie chcemy jezeli usuniedz dego definea

    // patrzymy co sie stanie jak wywolamy daj_rwartosc
    KK::Wizytowka temp = KK::daj_rwartosc(1);
    temp.przedstaw_sie();
}


