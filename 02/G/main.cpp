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
        return p[u] = get(p[u]);
    }
    return u;
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
    cnt[v] += cnt[u];
    mx[v] = max(mx[v], mx[u]);
    mn[v] = min(mn[v], mn[u]);
}


int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        mx[i] = mn[i] = p[i] = i;
        r[i] = 0;
        cnt[i] = 1;
    }

    string s;
    while (cin >> s) {
        if (s == "union") {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            unite(u, v);
        }
        if (s == "get") {
            int u;
            cin >> u;
            u--;
            u = get(u);
            cout << mn[u] + 1 << " " << mx[u] + 1 << " " << cnt[u] << endl;
        }
    }
    return 0;
}