#include <bits/stdc++.h>

using namespace std;

#define MAXN 20005

struct List {
    int node, cap, flow;
    List *nxt, *dup;
};

typedef List *plist;

plist adj[MAXN], edge[MAXN];
int n, m, q[MAXN], sel[MAXN], src, sink;

void alloc_edge(plist &nou, plist &dup, int i, int j) {
    nou = new List, dup = new List;
    nou->node = j, dup->node = i;
    nou->dup = dup, dup->dup = nou;
    nou->nxt = adj[i], dup->nxt = adj[j];
    adj[i] = nou, adj[j] = dup;
}

void read_in(void) {
    ifstream fin("sesiuni.in");
    int muchii, x, y;
    plist nou, dup;

    fin >> n >> m;

    while (fin >> x >> y) {
        alloc_edge(nou, dup, x, y + n);
        nou->cap = 1, nou->flow = dup->cap = dup->flow = 0;
    }
    fin.close();

    src = 0;
    for (int i = 1; i <= n; ++i) {
        alloc_edge(nou, dup, src, i);
        nou->cap = 1, nou->flow = dup->cap = dup->flow = 0;
    }
    sink = n + m + 1;
    for (int i = n + 1; i <= n + m; ++i) {
        alloc_edge(nou, dup, i, sink);
        nou->cap = 1, nou->flow = dup->cap = dup->flow = 0;
    }
}

int BFS(const int src, const int sink) {
    int h, t;
    plist it;

    memset(sel, 0, sizeof(sel));

    edge[src] = 0;
    for (sel[q[h = t = 0] = src] = 1; h <= t; ++h) {
        for (it = adj[q[h]]; it; it = it->nxt)
            if ((it->cap - it->flow) > 0 && !sel[it->node]) {
                sel[q[++t] = it->node] = 1;
                edge[it->node] = it;
                if (it->node == sink) {
                    for (it = edge[sink]; it; it = edge[it->dup->node])
                        it->flow++, it->dup->flow--;
                    return 1;
                }
            }
    }
    return 0;
}

int main(void) {
    read_in();
    int cuplaj = 0;
    while (BFS(src, sink)) cuplaj++;

    ofstream fout("sesiuni.out");
    fout << cuplaj << endl;
    for (int i = 1; i <= n; ++i) {
        for (plist it = adj[i]; it != NULL; it = it->nxt)
            if (it->flow == 1)
                fout << i << " " << it->node - n << endl;
    }

    return 0;
}