#include <iostream>

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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        int ind = binsearch(x, n);
        if (ind == -1) {
            cout << a[0] << endl;
            continue;
        }
        if (ind == n - 1) {
            cout << a[n - 1] << endl;
            continue;
        }
        if (x - a[ind] <= a[ind + 1] - x) {
            cout << a[ind] << endl;
        } else {
            cout << a[ind + 1] << endl;
        }
    }
    return 0;
}