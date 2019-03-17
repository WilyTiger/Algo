#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;
const double EPS = 1e-9;

struct jew {
    int v;
    int w;
    int ind;
    double cmp;
};

int n, k;
jew a[MAXN];

bool cmp(jew first, jew second) {
    return first.cmp > second.cmp;
}
bool check(double x) {
    for (int i = 0; i < n; i++) {
        a[i].cmp = a[i].v - x * a[i].w;
    }
    sort(a, a + n, cmp);

    double sum = 0;
    for (int i = 0; i < k; i++) {
        sum += a[i].cmp;
    }
    return sum > 0;
}

int main() {
    freopen("kbest.in", "r", stdin);
    freopen("kbest.out", "w", stdout);
    cin >> n >> k;

    double r = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i].v >> a[i].w;
        a[i].ind = i + 1;
        r += a[i].v;
    }


    double l = 0;

    while (r - l > EPS) {
        double m = (r + l) / 2;
        if (check(m)) {
            l = m;
        } else {
            r = m;
        }
    }

    for (int i = 0; i < k; i++) {
        cout << a[i].ind << endl;
    }
    return 0;
}