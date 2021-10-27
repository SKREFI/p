#include <bits/stdc++.h>
using namespace std;

int main() {
<<<<<<< HEAD
    ifstream fin("input.in");
    int n = 0, MAX = -1, v[1000];
    while (fin >> v[n++]) {}

    for (int i = 0; i < n; i++) {
        if (v[i] >= MAX) {
            MAX = v[i];
            cout << v[i] << ' ';
        }
    }
=======
    vector<int> v{1, 2, 3, 4, 5};

    printV(v);

    return 0;
>>>>>>> 34fa06a7e982fa15bac1d4d0c615b9ac3e80f396
}