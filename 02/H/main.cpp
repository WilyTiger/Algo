#include <iostream>
#include <cstdio>


using namespace std;

const int MAXN = 3e5 + 10;

int p[MAXN];
int r[MAXN];
int mx[MAXN];
int mn[MAXN];
int cnt[MAXN];

int get(int u) {
    if (p[u] != u) {
        return get(p[u]);
    } else {
        return u;
    }
}

void unite(int u, int v) {
    u = get(u);
    v = get(v);
    if (u == v)
        return;
    if (r[v] < r[u]) {
        swap(u, v);
    }

    if (r[u] == r[v]) {
        r[v]++;
    }
    p[u] = v;
    cnt[u] -= cnt[v];
    mx[v] = max(mx[v], mx[u]);
    mn[v] = min(mn[v], mn[u]);
}

int get_exp(int u) {
    if (p[u] != u) {
        return cnt[u] + get_exp(p[u]);
    } else {
        return cnt[u];
    }
}
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        r[i] = 0;
        p[i] = i;
        cnt[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        if (s == "join") {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            unite(u, v);
        }
        if (s == "add") {
            int x, v;
            cin >> x >> v;
            x--;
            x = get(x);
            cnt[x] += v;
        }
        if (s == "get") {
            int x;
            cin >> x;
            x--;
            cout << get_exp(x) << endl;
        }
    }
    return 0;
}
