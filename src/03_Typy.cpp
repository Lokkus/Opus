/*
 * 01_Limits.cpp
 *
 *  Created on: 24 wrz 2020
 *      Author:
 */

#include "main.h"
// kod sprawdzajacy zakresy zmiennych
template <typename T>
void info_about_limits(string name)
{
	cout<<"Sizeof "<<name<<": "<<sizeof(T)<<" numeric limits<T>: "<<numeric_limits<T>::digits<<endl;
}

void limits_test()
{
	info_about_limits<char>("char");
	info_about_limits<int>("int");
	info_about_limits<unsigned int>("unsigned int");
	info_about_limits<long int>("long int");
	info_about_limits<long>("long");
	info_about_limits<long long>("long long");
	info_about_limits<float>("float");
	info_about_limits<double>("double");
	info_about_limits<long double>("long double");
}

// Constexpr c++11
// wartosci zmiennych musza byc znane na etapie kompilacji
constexpr int size = 10;
void constexpr_arry_size()
{
	int array[size] = {};
	for (int i = 0; i< size; i++)
	{
		array[i] = 100%(i+1);
		cout<<array[i]<<" ";
	}
}

// przyklady funkcji constexpr
constexpr int constexpr_multiple(int a, int b)
{
	return a*b;
}

// silnia obliczona przy constexpr
constexpr int silnia(int n)
{
	return n>0 ? n*silnia(n-1) : 1;
}

// porownanie znakow przy uzyciu constexpr
constexpr int compare(char a, char b)
{
	return a < b ? -1 : (a == b) ? 0 : 1;
}

// obliczenie sinusa bez constexpr
double sinus(double x, int amount)
{
	double sin = 0;
	for (int n = 0; n<amount; n++)
	{
		sin += (pow(-1, n)/silnia(2*n+1))*pow(x, 2*n+1);
	}
	return sin;
}

// obliczenie sinusa przy uzyciu constexpr
constexpr double sin_constexpr(double x)
{
	return x - (x*x*x)/silnia(3) + (x*x*x*x*x)/silnia(5) - (x*x*x*x*x*x*x)/silnia(7) + (x*x*x*x*x*x*x*x*x)/silnia(9);
}

constexpr double deg_to_rad(double deg)
{
	return 3.14159265358979323846*deg/180;
}

// to nie zadziala przy kompilacji w sensie te sinusy nie zostalna wtedy obliczone, trzeba by bylo to wrzucic
// jako zmienna globalna
void array_od_sinuses()
{
	constexpr double sin_array[] = {
			sin_constexpr(deg_to_rad(0)),
			sin_constexpr(deg_to_rad(30)),
			sin_constexpr(deg_to_rad(60)),
			sin_constexpr(deg_to_rad(90)),
			sin_constexpr(deg_to_rad(180))
	};
	for (int i = 0; i < 5; i++)
	{
		cout<<sin_array[i]<<endl;
	}
}

void constexpr_test()
{
	//constexpr_arry_size();
	//cout<<constexpr_multiple(10, 20);
	//cout<<silnia(5);
	//cout<<compare('b', 'b');
	//cout<<sinus(3.14159265358979323846*90/180, 5);
	//cout<<sin_constexpr(1);
	array_od_sinuses();
}

// enum przypomnienie
enum class DniTygodnia {
    pn,
    wt,
    sr,
    czw,
    pt,
    sb,
    nd
};

void enum_test_2(DniTygodnia* ptr_dt)
{
    if (*ptr_dt == DniTygodnia::czw)
    {
        cout<<"Dzien tygodnia to: "<<static_cast<int>(*ptr_dt)<<endl;
    }
}

void enum_test()
{
    DniTygodnia dt;
    dt = DniTygodnia::wt;
    if(dt == DniTygodnia::wt)
    {
        cout<<"Wszystko ok"<<endl;
    }
    // mozna tez zadeklarowac poprzez auto:
    auto a_dt = DniTygodnia::czw;
    enum_test_2(&a_dt);
}



void typy_test()
{
	//limits_test();
	//constexpr_test();
	//enum_test();
}



