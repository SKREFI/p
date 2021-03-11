#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream f("grafpond.in");

int varfuri, muchii;
int reprezentant[1000], dimensiune[1000];

vector<pair<int, int>> apcm;

struct m
{
    int x, y, cost;
} v[1000];

void citire()
{
    f>>varfuri>>muchii;

    for(int i=1; i<=muchii; i++)
        f>>v[i].x>>v[i].y>>v[i].cost;
}

bool cmp (m m1, m m2)
{
    return m1.cost < m2.cost;
}

int reprz(int nod)
{
    if(nod != reprezentant[nod])
        reprezentant[nod] = reprz(reprezentant[nod]);
    return reprezentant[nod];
}

void kruskal()
{
    for(int i=1; i<muchii; i++)
    {
        int rx, ry;
        rx = reprz(v[i].x);
        ry = reprz(v[i].y);

        if(rx != ry)
        {
            if(dimensiune[rx] < dimensiune[ry])
            {
                dimensiune[ry] += dimensiune[rx];
                reprezentant[rx] = ry;
            }
            else
            {
                dimensiune[rx] += dimensiune[ry];
                reprezentant[ry] = rx;
            }

            apcm.push_back(make_pair(v[i].x,v[i].y));
        }
    }
}

void afisare()
{
    for (int i=0; i<apcm.size(); i++)
        cout<<apcm[i].first<<" "<<apcm[i].second<<endl;
}

int main()
{
    citire();

    sort(v+1, v+muchii+1, cmp);

    for(int i=1; i<=varfuri; i++) {
        reprezentant[i] = i;
        dimensiune[i] = i;
    }

    kruskal();

    afisare();
}