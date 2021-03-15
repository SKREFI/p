#include <bits/stdc++.h>
using namespace std;

ifstream f("grafpond.in");

int varfuri, muchii, vizitat[1000];
vector<pair<int, int>> apcm;
vector<pair<int, int>> graf[1000];

class Nod {
   public:
    int x, y, cost;
};

vector<Nod> aux;

void citire() {
    f >> varfuri >> muchii;

    for (int i = 1; i <= muchii; i++) {
        int a, b, c;
        f >> a >> b >> c;
        graf[a].push_back(make_pair(b, c));
        graf[b].push_back(make_pair(a, c));
    }
}

bool cmp(Nod x, Nod y) {
    return x.cost < y.cost;
}

bool am_de_inserat() {
    for (int i = 1; i <= varfuri; i++)
        if (vizitat[i] == 0)
            return true;

    return false;
}

void prim(int nod) {
    vizitat[nod] = 1;

    for (auto urm : graf[nod])
        if (vizitat[urm.first] == 0) {
            Nod a;
            a.x = nod;
            a.y = urm.first;
            a.cost = urm.second;
            aux.push_back(a);
        }

    while (am_de_inserat()) {
        sort(aux.begin(), aux.end(), cmp);

        for (Nod i : aux)
            if (vizitat[i.y] == 0) {
                vizitat[i.y] = 1;

                apcm.push_back(make_pair(i.x, i.y));

                for (auto urm : graf[i.y])
                    if (vizitat[urm.first] == 0) {
                        Nod a;
                        a.x = i.y;
                        a.y = urm.first;
                        a.cost = urm.second;
                        aux.push_back(a);
                    }
                break;
            }
    }
}

void afisare() {
    for (int i = 0; i < apcm.size(); i++)
        cout << apcm[i].first << " " << apcm[i].second << endl;
}

int main() {
    citire();

    prim(1);

    afisare();
}