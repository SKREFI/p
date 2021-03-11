#include <bits/stdc++.h>

#include <fstream>

using namespace std;

ifstream fin("graf1.in");
ofstream fout("graf1.out");

vector<int> muchii[100010];
bool vizitat[100010];
int grad[100010];
vector<int> sol;
queue<int> q;

void topologic() {
    while (!q.empty()) {
        int elem = q.front();
        q.pop();

        for (auto vecin : muchii[elem]) {
            grad[vecin]--;
            if (grad[vecin] == 0 && !vizitat[vecin]) {
                vizitat[vecin] = true;
                sol.push_back(vecin);
                q.push(vecin);
            }
        }
    }
}

int main() {
    int n, m, x, y;
    fin >> n >> m;

    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        muchii[x].push_back(y);
        grad[y]++;
    }

    for (int i = 1; i <= n; i++) {
        if (grad[i] == 0) sol.push_back(i), q.push(i);
    }

    topologic();

    for (int elem : sol) {
        cout << elem << " ";
        fout << elem << " ";
    }
}