#include <bits/stdc++.h>

using namespace std;

#define V 13

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int* dijkstra(int graph[V][V], int src) {
    int dist[V];

    bool sptSet[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    return dist;
}

void printDistanta(int* distanteA, int* distanteB) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (distanteA[i] == distanteB[j]) {
            }
        }
        cout << endl;
    }
}

class Node {
   public:
    int a, b, cost;
    Node(int a, int b, int cost) {
        this->a = a;
        this->b = b;
        this->cost = cost;
    }
};

int main() {
    int a, b;
    ifstream fin("graf.in");
    ofstream fout("graf.out");

    int graph[V][V]{0};

    fin >> a >> b;

    int nod1, nod2, cost;
    while (fin >> nod1) {
        fin >> nod2;
        fin >> cost;

        graph[nod1 + 1][nod2 + 1] = cost;
        graph[nod2 + 1][nod1 + 1] = cost;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    int* distanteA = dijkstra(graph, a);
    int* distanteB = dijkstra(graph, b);

    // vector<pair<int, int>> noduri_cu_aceeasi_distanta;
    vector<Node> noduri;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (distanteA[i] == distanteB[j] && distanteB[j] != 0 && distanteB[j] < 1000000) {  // am ceva probleme cu codul, nu inteleg de ce la unele noduri primesc drept distanta a valoare din memorie
                noduri.push_back(Node(i, j, distanteA[i]));
            }
        }
        cout << endl;
    }

    cout << "Noduri:\n";
    for (auto nod : noduri) {
        cout << nod.a << " " << nod.b << " cu un cost de: " << nod.cost << endl;
    }

    // segmentation foult, ne vedem in vara, 3 astfel de probleme in 1.5h... interesant, astept sa vad procentajul de promovati

    return 0;
}
