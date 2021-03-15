#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("input.in");
    int n = 0, MAX = -1, v[1000];
    while (fin >> v[n++]) {}

    for (int i = 0; i < n; i++) {
        if (v[i] >= MAX) {
            MAX = v[i];
            cout << v[i] << ' ';
        }
    }
}