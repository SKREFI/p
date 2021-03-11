///am folosit Edmonds-Karp si avem complexitatea O(nm^2)

#include <bits/stdc++.h>

using namespace std;
struct Edge
{
    int node, capacity, flux;
};

int totalFlow;

vector<vector<Edge>> edges;
unordered_map<int, int> _edges[100010], _rEdges[100010];

int n, s, t, m;

int bfs(int s, int t, int parent[])
{
    bool visited[n + 5];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (auto nextNode : _rEdges[node])
        {
            if (!visited[nextNode.first] && nextNode.second > 0)
            {
                q.push(nextNode.first);
                parent[nextNode.first] = node;
                visited[nextNode.first] = true;
            }
        }


    }
    return visited[t];

}

void dfs (int s, bool visited[])
{
    visited[s] = true;
    for (auto nextNode : _rEdges[s])
        if (nextNode.second && !visited[nextNode.first])
            dfs(nextNode.first, visited);
}


void solve(int s, int t)
{
    int parent[n + 5];
    int prev, curr;

    while (bfs(s, t, parent))
    {
        int path_flow = INT_MAX;
        for (curr = t; curr != s; curr = parent[curr])
        {
            prev = parent[curr];
            path_flow = min(path_flow, _rEdges[prev][curr]);
        }
        for (curr = t; curr != s; curr = parent[curr])
        {
            prev = parent[curr];
            _rEdges[prev][curr] -= path_flow;
            _rEdges[curr][prev] += path_flow;
        }
        totalFlow += path_flow;
    }
    ///am gasit fluxul total

    bool visited[n + 5];
    memset(visited, false, sizeof(visited));

    dfs(s, visited);
    cout << totalFlow << "\n";

    for (int i = 1; i <= n; i++)
    {
        for (auto it : _edges[i])
        {
            cout << i <<" " << it.first <<" ";
            cout << it.second - _rEdges[i][it.first] << "\n";
        }
    }
    ///min cut has the same cost as max flow
    cout << totalFlow <<"\n";

    for (int i = 1 ; i <= n; i++)
        for (auto it : _edges[i])
        {
            if (visited[i] && !visited[it.first] && it.second)
                cout << i <<" " << it.first<<"\n";
        }
}



int main()
{
    ifstream fin ("retea.in");
    fin >> n;
    fin >> s >> t;
    fin >> m;

    edges.resize(n + 5);

    int inFlux[n + 5];
    int outFlux[n + 5];

    for (int i = 1; i<= n; i++)
        inFlux[i] = outFlux[i] = 0;

    bool isValidFlux = 1;
    for (int i = 1; i <= m; i++)
    {
        Edge aux;
        int node;
        fin >> node;
        fin >> aux.node >> aux.capacity >> aux.flux;
        inFlux[aux.node] += aux.flux;
        outFlux[node] += aux.flux;

        edges[node].push_back(aux);

        if (aux.capacity < aux.flux)
            isValidFlux = false;

        ///punem muchiiile in graf
        _edges[node][aux.node] = aux.capacity; ///graful fara flux

        ///punem in graful rezidual muchiile reziduale
        _rEdges[node][aux.node] = aux.capacity - aux.flux;
        _rEdges[aux.node][node] = aux.flux;
    }

    for (int i = 1; i<= n; i++)
        if (inFlux[i] != outFlux[i] && (i != s && i != t))
            {
                isValidFlux = false;
            }
    if (outFlux[s] != inFlux[t])
        isValidFlux = false;

    if(isValidFlux)
        cout << "DA\n";
    else
        cout << "NU\n";
    ///daca nu e valid nu are sens sa mai continuam
    if (!isValidFlux)
        return 0;

    ///fluxul total momentan este cat intra in sursa
    totalFlow = inFlux[t];
    solve(s, t);


    return 0;
}
