#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 1e5 + 5;
#define int long long

const int MAX = 1e18 + 10;
int a[MAXN];
int t[4 * MAXN];
int add_val[4 * MAXN];
int set_val[4 * MAXN];
bool flag[4 * MAXN];

void BuildTree(int v, int l, int r) {
    add_val[v] = 0;
    t[v] = MAX;
    flag[v] = false;
    set_val[v] = 0;
    if (r - l <= 1) {
        t[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    BuildTree(v * 2, l, m);
    BuildTree(v * 2 + 1, m, r);
    t[v] = min(t[v * 2], t[v * 2 + 1]);
}

void push(int v, int l, int r) {

    if (r - l <= 1)
        return;
    if (add_val[v] != 0) {
        if (flag[v * 2]) {
            set_val[v * 2] += add_val[v];
        } else {
            add_val[v * 2] += add_val[v];
        }
        t[v * 2] += add_val[v];
        if (flag[v * 2 + 1]) {
            set_val[v * 2 + 1] += add_val[v];
        } else {
            add_val[v * 2 + 1] += add_val[v];
        }
        t[v * 2 + 1] += add_val[v];
        add_val[v] = 0;
    }
    if (flag[v]) {
        set_val[v * 2] = set_val[v * 2 + 1] = set_val[v];
        t[v * 2] = t[v * 2 + 1] = set_val[v];
        add_val[v * 2] = add_val[v * 2 + 1] = 0;
        set_val[v] = 0;
        flag[v * 2] = flag[v * 2 + 1] = true;
        flag[v] = false;
    }
    t[v] = min(t[v * 2], t[v * 2 + 1]);
}

int get_min(int v, int l, int r, int ql, int qr) {
    push(v, l, r);
    if (r <= ql || l >= qr) {
        return MAX;
    }
    if (l >= ql && r <= qr) {
        return t[v];
    }
    int m = (l + r) / 2;
    return min(get_min(v * 2, l, m, ql, qr), get_min(v * 2 + 1, m, r, ql, qr));
}

void set(int v, int l, int r, int ql, int qr, int x) {
    push(v, l, r);
    if (r <= ql || l >= qr) {
        return;
    }
    if (l >= ql && r <= qr) {
        set_val[v] = x;
        flag[v] = true;
        t[v] = x;
        add_val[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    set(v * 2, l, m, ql, qr, x);
    set(v * 2 + 1, m, r, ql, qr, x);
    push(v, l, r);
}

void add(int v, int l, int r, int ql, int qr, int x) {
    push(v, l, r);
    if (r <= ql || l >= qr) {
        return;
    }
    if (l >= ql && r <= qr) {
        t[v] += x;
        add_val[v] = x;
        return;
    }
    int m = (l + r) / 2;
    add(v * 2, l , m, ql, qr, x);
    add(v * 2 + 1, m , r, ql, qr, x);
    push(v, l, r);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    BuildTree(1, 0, n);

    string s;
    int ql, qr;
    while (cin >> s >> ql >> qr) {
        if (s == "min") {
            cout << get_min(1, 0, n, ql - 1, qr) << endl;
        } else if (s == "set") {
            int x;
            cin >> x;
            set(1, 0, n, ql - 1, qr, x);
        } else {
            int x;
            cin >> x;
            add(1, 0, n, ql - 1, qr, x);
        }
    }
    return 0;
}
