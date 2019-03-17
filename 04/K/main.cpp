#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 2e5;

int t[4 * MAXN];

void BuildTree(int v, int l, int r) {
    if (r - l == 1) {
        t[v] = 1;
        return;
    }
    int m = (l + r) / 2;
    BuildTree(v * 2, l, m);
    BuildTree(v * 2 + 1, m, r);
    t[v] = t[v * 2] + t[v * 2 + 1];
}

void upd(int v, int l, int r, int ind, int d) {
    if (ind < l || ind >= r) {
        return;
    }
    if (r - l == 1) {
        t[v] += d;
        return;
    }
    int m = (l + r) / 2;
    upd(v * 2, l, m, ind, d);
    upd(v * 2 + 1, m, r, ind, d);
    t[v] = t[v * 2] + t[v * 2 + 1];
}

int get_sum(int v, int l, int r, int ql, int qr) {
    if (r <= ql || l >= qr) {
        return 0;
    }
    if (l >= ql && r <= qr) {
        return t[v];
    }
    int m = (l + r) / 2;
    return get_sum(v * 2, l, m, ql, qr) + get_sum(v * 2 + 1, m, r, ql, qr);
}

int kth(int v, int l, int r, int k) {
    int m = (l + r) / 2;
    if (r - l == 1) {
        return l;
    }
    if (t[v * 2] >= k) {
        return kth(v * 2, l, m, k);
    } else {
        return kth(v * 2 + 1, m, r, k - t[v * 2]);
    }
}

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    BuildTree(1, 0, 2 * n);
    string s;
    int x;
    while (cin >> s >> x) {
        if (s == "exit") {
            x--;
            upd(1, 0, 2 * n, x, 1);
            upd(1, 0, 2 * n, x + n, 1);
        } else {
            int cnt = get_sum(1, 0, 2 * n, 0, x - 1);
            int free = kth(1, 0, 2 * n, cnt + 1);
            if (free >= n) {
                free -= n;
            }
            upd(1, 0, 2 * n, free, -1);
            upd(1, 0, 2 * n, free + n, -1);
            cout << free + 1 << endl;
        }
    }
    return 0;
}