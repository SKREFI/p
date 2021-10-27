#include <bits/stdc++.h>
using namespace std;

class Graph {
   public:
    int V;
    list<int> *adj;

    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void muchiiCritice() {
        cout << "muchii critice:\n";
        bool *visited = new bool[V];
        int *parent = new int[V];

        for (int i = 0; i < V; i++) {
            parent[i] = -1;
            visited[i] = false;
        }

        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                helper(i, visited, new int[V], new int[V], parent);
    }

    void helper(int u, bool visited[], int disc[],
                int low[], int parent[]) {
        static int time = 0;

        visited[u] = true;

        disc[u] = low[u] = ++time;

        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = *i;

            if (!visited[v]) {
                parent[v] = u;
                helper(v, visited, disc, low, parent);

                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) cout << u << " " << v << endl;
            }

            else if (v != parent[u])
                low[u] = min(low[u], disc[v]);
        }
    }
};

int main() {
    int n, m, x, y;
    ifstream fin("graf.in");
    fin >> n >> m;

    Graph g(m);

    while (fin >> x >> y) {
        g.adj[x].push_back(y);
        g.adj[y].push_back(x);
    }

    g.muchiiCritice();

    return 0;
}
