#include <bits/stdc++.h>
using namespace std;

#define printV(v) \
    for (auto x : v) print(x);

template <class T>
void print(T x, char end = '\n') {
    cout << x << end;
}

int main() {
    vector<int> v{1, 2, 3, 4, 5};

    printV(v);
    
    return 0;
}