#include <bits/stdc++.h>
using namespace std;


/*mai intai vom presupune ca inputul este de forma
n m
u1 v1
u2 v2
...
unde u1 este un nod din primul set de noduri din graful bipartit iar v1 este un nod din al doilea set de noduri din graful bipartit.

Ideea de rezolvare : adaugam doua noduri, 0 si n + 1, 0 fiind un nodul de start iat n + 1 fiind nodul destinatie. Astfel, ducem cate o muchie
de la nodul de start la toate nodurile din primul set, si de la fiecare nod din al doilea set in nodul destinatie. Vom modela problema ca pe o problema
de flux, astfel, cuplajul maxim in graful initial este egal cu fluxul maxim in noul graf in care avem muchii orientate de la 0 la primul set,
de la primul set la al doilea set si de la al doilea set la nodul n + 1. Astfel, aplicand Ford Fulkerson vom determina un cuplaj maximal.

Complexitatea este O(nm), dat de complexitatea lui Ford Fulkerson


*/

///graful initial
unordered_set<int> nodes[100010];

///graful rezidual
unordered_set<int> rNodes[100010];

int n;


bool bfs(int s, int t, int parent[]) {

    bool visited[n + 5];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    ///facem un bfs sa gasim un drum de la sursa la destinatie.
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : rNodes[u]) {
        if (visited[v] == false) {
            q.push(v);
            parent[v] = u;
            visited[v] = true;
        }
        }
    }

    return (visited[t] == true);
}

int fordFulkerson(int s, int t) {
    int u, v;

    for (int i = 0; i <= n + 1; i++)
    {
        for(auto it: nodes[i])
            rNodes[i].insert(it);
    }


    int parent[n + 5]; ///vector de parinti pt bfs
    int max_flow = 0;


    while (bfs(s, t, parent)) {
        for (v = t; v != s; v = parent[v]) {
        u = parent[v];
        }

    for (v = t; v != s; v = parent[v]) {
        u = parent[v];
        rNodes[u].erase(v);
        rNodes[v].insert(u);
        }

        max_flow += 1;
    }

    return max_flow;
}

int main() {

    ifstream cin ("input.in");
    int m;
    cin >> n >> m;
    for (int i = 1; i<= m; i++)
    {
        int x, y;
        cin >> x >> y;
        ///punem muchie de la nodul de start 0 la nodul x, de la x la y si de la y la nodul final
        /// e ca si cum am avea muchii orientate si trebuie sa gasim fluxul maxim
        nodes[0].insert(x);
        nodes[y].insert(n+1);
        nodes[x].insert(y);
    }
    cout << "Cardinalitatea maxima a unui cuplaj este de " << fordFulkerson(0, n + 1) <<"\n";
    cout << "Muchiile din cuplajul maxim sunt \n";

        ///verific pe ce muchii am pus 'flow'
    for (int i = 1; i <= n; i++)
    {
        for (auto el : nodes[i])
        {
            if (rNodes[el].find(i) != rNodes[el].end() && el != n + 1)
            {
                cout << i << " " << el <<"\n";
            }
        }
    }

}
