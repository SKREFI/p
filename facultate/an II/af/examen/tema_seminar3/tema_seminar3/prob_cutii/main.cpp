/*
Se dau n cutii m dimiensionale;
(a1,a2,  ...am)  (3,4,6, 7)
(b1,b2,…. bm) (7,2, 1, 3) -> 2, 1,3,7   -> b intra în a
(c1,c2,..... cm) (7, 7, 1,1 ) -> asta nu intra nicaieri și nici vreuna în ea

O cutie intra în alta dacă exista o permutara a laturilor sale astfel incat b1 <= a2, b2 <=a2, b3 <=a3,....
Găsiți cel mai mare număr de cutii care sa intre una în alta si afisati-le
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
ifstream f("cutii.in");

int n, m;
struct cutie {
    int laturi[1000], nr_cutie;
} c[1000];

vector<int> predecesor[1000];

//drum[i][j] = lungimea celui mai lung drum pana la i daca as trece prin j
int drum[1000][1000];

//coordonatele din matrice corespunzatoare nodului final al celui mai lung drum
int i_max_matrice = 0, j_max_matrice = 0;

//atunci cand merg inapoi de la ultima la prima cutie, salvez valorile intr-o stiva pentru a le putea afisa apoi
stack<int> rezultat;

//dmin, succesor, intern0, sortare_graf -> ma folosesc de ele atunci cand trebuie sa fac sortarea topologica
int dmin[1000];
vector<int> succesor[1000];
queue<int> intern0;
queue<int> sortare_graf;


void citire()
{
    f>>n>>m;
    for(int i=1; i<=n; i++) {

        cutie aux;
        for (int j = 0; j < m; j++)
            f>>aux.laturi[j];

        sort(aux.laturi+0, aux.laturi+m);

        aux.nr_cutie=i;
        c[i] = aux;
    }
}

bool intra(cutie a, cutie b)
{
    for(int i=0; i<m; i++)
        if(a.laturi[i] > b.laturi[i])
            return false;

    return true;
}

void creare_graf()
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(i!=j)
                if(intra(c[i], c[j])){
                    succesor[c[i].nr_cutie].push_back(c[j].nr_cutie);
                    dmin[c[j].nr_cutie]++;

                    predecesor[c[j].nr_cutie].push_back(c[i].nr_cutie);
                }

    //adaug nodul 0 in graf ca fiind un nod de start din care pot sa merg in orice alt nod
    for(int i=1; i<=n; i++) {
        succesor[0].push_back(i);
        predecesor[i].push_back(0);
    }
}

void sortare_topologica() {
    int i;

    for(i=0; i<=n; i++)
        if(dmin[i] == 0)
            intern0.push(i);


    while (!intern0.empty()) {
        i = intern0.front();
        intern0.pop();

        sortare_graf.push(i);

        for(int j : succesor[i]) {
            dmin[j]--;
            if(dmin[j] == 0)
                intern0.push(j);
        }
    }
}

int maxim(int i)
{
    int max_crt = -123456789;
    for(int j=0; j<=n; j++)
        if(drum[i][j] > max_crt)
            max_crt = drum[i][j];

    return max_crt;
}

void parcurgere()
{
    sortare_graf.pop(); //scot nodul de start pe care l-am adaugat de la mine

    while (!sortare_graf.empty()) {

        int crt = sortare_graf.front();
        sortare_graf.pop();


        for(int j : predecesor[crt]) {

            int max_crt = maxim(j);     //obtin lungimea maxima pana la predecesorul i al nodului curent
            drum[crt][j] = max_crt+1;

            if(drum[crt][j] > drum[i_max_matrice][j_max_matrice])
                i_max_matrice = crt, j_max_matrice = j;
        }

    }
}

int pozitie_maxim(int i, int max)
{
    for(int j=0; j<=n; j++)
        if(drum[i][j] == max)
            return j;
}

void sfarsit()
{
    int i = i_max_matrice, j = j_max_matrice;

    while (drum[i][j] != 0) {           //parcurg matricea inapoi pana cand ajung la nodul de start

        rezultat.push(i);               //inserez elementele in stiva
        int aux = i;

        i = j;
        j = pozitie_maxim(j, drum[aux][j]-1);
    }

    while (!rezultat.empty()) {
        cout<<rezultat.top()<<" ";
        rezultat.pop();
    }
}

int main()
{
    citire();

    creare_graf();

    ///afisare cutii sortate
//    for(int i=1; i<=n; i++){
//        for(int j=0; j<m; j++)
//            cout<<c[i].laturi[j]<<" ";
//        cout<<endl;
//    }

    ///afisare succesori noduri, prdecesori noduri
//    for(int i=0; i<=n; i++){
//        cout<<i<<":  ";
//        for(int j : succesor[i])
//            cout<<j<<" ";
//        cout<<endl;
//    }
//      cout<<endl;
//    for(int i=0; i<=n; i++){
//        cout<<i<<":  ";
//        for(int j : predecesor[i])
//            cout<<j<<" ";
//        cout<<endl;
//    }

    sortare_topologica();

    ///afisare noduri in ordinea sortarii topologice
//    while (!sortare_graf.empty()) {
//        int a = sortare_graf.front();
//        sortare_graf.pop();
//        cout<<a<<" ";
//    }

    parcurgere();

    ///afisare matrice
//    for(int i=0; i<=n; i++) {
//        for (int j = 0; j <= n; j++)
//            cout<<drum[i][j]<<" ";
//        cout<<endl;
//    }

    ///afisare coordonate punct final al celui mai lung drum
//    cout<<i_max_matrice<<" "<<j_max_matrice;

    sfarsit();

}