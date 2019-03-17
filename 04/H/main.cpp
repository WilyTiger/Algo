#include <iostream>
#include <algorithm>

using namespace std;

#define int long long
const int MAX = (1ll << 31) - 1;
const int MAXN = 1e5 + 10;

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
        t[v] = 0;
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


struct query {
    int l;
    int r;
    int ans;
};

query q[MAXN];

bool cmp(query f, query s) {
    return f.ans < s.ans;
}
signed main() {
    //freopen("rmq.in", "r", stdin);
    //freopen("rmq.out", "w", stdout);
    cin.sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    BuildTree(1, 0, n);
    for (int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r >> q[i].ans;
    }

    sort(q, q + m, cmp);
    for (int i = 0; i < m; i++)
        set(1, 0, n, q[i].l - 1, q[i].r, q[i].ans);
    for (int i = 0; i < m; i++) {
        if (get_min(1, 0, n, q[i].l - 1, q[i].r) != q[i].ans) {
            cout << "inconsistent";
            return 0;
        }
    }

    cout << "consistent" << endl;

    for (int i = 0; i < n; i++) {
        cout << get_min(1, 0, n, i, i + 1) << " ";
    }

    return 0;
}