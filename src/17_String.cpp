/*
 * 17_String.cpp
 *
 *  Created on: 7 pa? 2020
 *      Author:
 */

#include "main.h"

// rzucenie wyjatku po przekroczeniu zakresu
void rzucanie_wyjatkow_test()
{
    string s = "Ala ma kota";
    //s[100] = 'X'; //to sie nie wykona choc skompiluje
    cout<<s<<endl;

    // jak to zrobic prawilnie
    try
    {
        s.at(100) = 'X';
    }
    catch(out_of_range& e)
    {
        cout<<"Cos poszlo nie tak"<<endl;
        cout<<e.what()<<endl;
    }
}

void front_back_funkcje()
{
    // front i back
    string s = "Ala ma kota";
    char& a = s.front();
    cout<<a<<endl;
    a = 'U';
    cout<<s<<endl; // Ula ma kota, dzieje sie tak dlatego ze front jest ref.
    // to samo mozemy zrobic z back

    char& b = s.back();
    b = 'A';
    cout<<s<<endl;
}

template <typename T>
void liczby_i_stringi(T& l, string& s)
{
    s += to_string(l);
    cout<<s<<endl;

}

void przeszukiwanie()
{
    string s = "jakis strasznie dlugi tekst w ktorym trzeba cos znalesc a ja jakos musze to zrobic";
    const string& znajdz = "jak";

    // znajdujemy wszystkie poczatki indekspow gdzie wystepuje slowo "jak"

    vector<size_t> indexes;
    int len = 0;
    size_t pos = 0;
    pos = s.find(znajdz, pos + len);;
    while(pos != string::npos)
    {
        indexes.push_back(pos);
        len = znajdz.length();
        pos = s.find(znajdz, pos + len);
    }
    for (auto a : indexes)
    {
        cout<<a<<endl;
    }
}

void odwracanie_stringa()
{
    string s1 = "Ala ma kota";
    string s2 = string(s1.rbegin(), s1.rend());
    cout<<s2<<endl;

}

void palindrom(const string& str)
{

    string temp = str;
    temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
    for (auto& a: temp)
    {
        a = tolower(a);
    }
    string rev = string(temp.rbegin(), temp.rend());
    if (temp == rev)
    {
        cout<<"Palindrom"<<endl;
    }
}
void f_insert()
{
    string s  = "Kobyla ma maly bo";
    s.insert(s.length(), "czek");
    cout<<s<<endl;

    // w srodku
    // zamiana wszystkich spacji na xx
    size_t pos = 0;
    while((pos = s.find(" ", pos)) != string::npos)
    {
        s.replace(pos, 1, "");
        s.insert(pos, "xx");
    }
    for (auto a: s)
    {
        cout<<a;
    }
}

// w jaki sposob dobrac sie do danych ktore sa w zamkniete w obiekcie string
void f_data()
{
    string s = "Ala ma kota";
    size_t len = s.length();
    const char* t = s.data();
    while(*t != '\0')
    {
        cout<<*(t++);
    }
    cout<<endl;
    const char* n = s.data();
    n+=(len-1);
    while(len-- > 0)
    {
        cout<<*(n--);
    }
}

void f_getline()
{
    cout<<"wprowadz tyle tekstu ile chcesz, naciskajac enter wprowadzasz dane, "
            "jednkorotne wcisniecie k lub K i wcisniecie enter "
            "konczy wprowadzanie"<<endl;
    vector<string> vstr;
    string tmp;
    while(getline(cin, tmp))
    {
        if (tmp == "k" or tmp == "K")
            break;
        vstr.push_back(tmp);
    }

    for (const auto& a: vstr)
    {
        cout<<a<<endl;
    }
}

void iteratory()
{
    string s = "kobylamamalyboki";
    int count = 1;
    bool flag = true;
    for (string::iterator it = s.begin(); it<(s.end() - s.length()/2); ++it)
    {
        if (*it != *(s.end()-count++))
        {
            flag = false;
        }
    }
    flag == true ? cout<<"Palindrom!!"<<endl : cout<<"To nie jest pali"<<endl;
}

void iteratory_2()
{
    string s = ("Ala ma xxx kota");

    s.erase(remove(s.begin(), s.end(), 'x'), s.end());
    cout<<s<<endl;
}

void porownywanie()
{
    string s1 = "Ala ma kota";
    string s2 = "kot";
    string s3(s1.begin()+7, s1.end()-1);

    cout<<s3<<endl;

    if ((s2.compare(0, string::npos, s3)) == 0)
    {
        cout<<"Takie same"<<endl;
    }
}
void stringi_test()
{
//    rzucanie_wyjatkow_test();
//    front_back_funkcje();
//    string s = "Ala ma ";
//    double liczba = 123.456;
//    liczby_i_stringi(liczba, s);
//    przeszukiwanie();
//    odwracanie_stringa();
//    palindrom("kobylA ma maly bok");
//    f_insert();
//    f_data();
//    f_getline();
//    iteratory_2();
    porownywanie();
}


