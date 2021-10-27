#include <cstdio>
#include <cstring>

#define N 128
#define oo 0x3f3f3f3f  //infinit

int cap[N][N], flux[N][N];
int t[N];
int n, m;

int bfs(int source, int sink) {
    int Q[N + 1], p = 0, q = 0;
    bool use[N];
    memset(use, 0, sizeof(use));
    memset(t, 0, sizeof(t));
    Q[0] = source;
    use[source] = 1;

    while (p <= q) {
        int u = Q[p++];  //scoatem primul element din coada

        for (int i = source; i <= sink; ++i)     // pt fiecare nod ( adiacent )
            if (!use[i])                         // nu am folosit nodul
                if (cap[u][i] - flux[u][i] > 0)  // mai putem pompa?
                {
                    Q[++q] = i;  // inseram nodul i in coada
                    t[i] = u;
                    use[i] = 1;
                }
    }

    if (t[sink])
        return 1;
    return 0;
}

int edmondKarp(int source, int sink) {
    int flow = 0;  //fluxul
    int i, min;

    while (bfs(source, sink))  // cat timp mai exista un drum de ameliorare
    {
        min = oo;
        for (i = sink; i; i = t[i])
            if (cap[t[i]][i] - flux[t[i]][i] < min)
                min = cap[t[i]][i] - flux[t[i]][i];
        //calculam minimul dintre capacitatile ramase de pe drum

        for (i = sink; i; i = t[i])
            flux[t[i]][i] += min,      //adaugam minimul la fluxul de pe arcele de pe drum
                flux[i][t[i]] -= min;  //scadem minimul de pe arcele inverse

        flow += min;  // adaugam minimul la flux
    }
    return flow;
}

int main() {
    
}