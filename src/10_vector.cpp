/*
 * 10_vector.cpp
 *
 *  Created on: 1 pa? 2020
 *      Author:
 */


#include "main.h"

void show_vector2D(const vector<vector<int>>& vint)
{
    for (auto i: vint)
    {
        for (auto j: i)
        {
            cout<<j<<"\t";
        }
        cout<<endl;
    }
}

void vector_2D()
{
    // przyklad utworzenia vectora 10x10
    vector<vector<int>> v2dint;
    v2dint.resize(10);
    for (int i = 0; i<10; i++)
    {
        v2dint[i].resize(10);
    }

    // wypelniamy go liczbami 0 - 100
    int l = 0;
    for (int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            v2dint[i][j] = l++;
        }
    }

    // pokazujemy verktor
    show_vector2D(v2dint);
    cout<<endl;

    // kasujemy dowolny wiersz
    int wiersz = 4;
    v2dint.erase(v2dint.begin()+wiersz);
    show_vector2D(v2dint);

    // kasujemy ostatni wiersz
    v2dint.pop_back();
    cout<<endl;
    show_vector2D(v2dint);

    // modyfikujemy tak, ze jesli element jest >=50 oraz <60 to wstawiamy elementy = 100
    // musiby ti zrobic przez referencje
    for (auto& i : v2dint)
    {
        for (auto& j : i)
        {
            if (j >=50 and j< 60)
            {
                j = 100;
            }
        }
    }
    cout<<endl;
    show_vector2D(v2dint);

    // przyklad wektora 3d
    vector<vector<vector<int>>> v3dint
    {
        {
            {1, 2, 3},
            {4, 5, 6}
        },
        {
            {7, 8, 9},
            {10, 11, 12}
        }
    };
    // zeby wyswietlic 12
    cout<<v3dint[1][1][2];

}

void vector_test()
{
    vector_2D();
}

