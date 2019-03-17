#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1e5;
int a[MAXN];

int binsearch(int x, int n) {
    int l = -1;
    int r = n;

    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] <= x) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}
int main() {
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);*/
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int ql, qr;
        cin >> ql >> qr;
        cout << binsearch(qr, n) - binsearch(ql - 1, n) << " ";
    }
    return 0;
}