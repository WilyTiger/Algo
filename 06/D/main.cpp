#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 3e5;
const int MAXP = 20;

int p[MAXN];
int r[MAXN];
int dp[MAXN][MAXP];
int n;
int d[MAXN];
vector<int> tree[MAXN];

void dfs(int u, int p, int cnt) {
    d[u] = cnt;
    for (auto v : tree[u]) {
        dfs(v, u, cnt + 1);
    }
}

int get(int u) {
    if (p[u] == u) {
        return u;
    }
    return p[u] = get(p[u]);
}

void unite(int u, int v) {
    u = get(u);
    v = get(v);

    if (u == v) {
        return;
    }

    p[u] = v;
}

void calc(int v, int pred) {
    p[v] = v;
    d[v] = d[pred] + 1;
    dp[v][0] = pred;
    for (int i = 1; i < MAXP; i++) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
}

int get_lca(int u, int v) {
    if (d[u] < d[v]) {
        swap(u, v);
    }

    int r = d[u] - d[v];
    for (int i = MAXP - 1; i >= 0; i--) {
        if (r & (1 << i)) {
            u = dp[u][i];
        }
    }

    if (v == u) {
        return u;
    }

    for (int i = MAXP - 1; i >= 0; i--) {
        if (dp[v][i] != dp[u][i]) {
            v = dp[v][i];
            u = dp[u][i];
        }
    }
    return dp[v][0];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m;
    cin >> m;


    int root = 1;
    int cnt = 2;
    p[1] = 1;

    for (int i = 0; i <= MAXP; i++) {
        dp[root][i] = root;
    }

    for (int i = 0; i < m; i++) {
        char ch;
        cin >> ch;
        if (ch == '+') {
            int v;
            cin >> v;

            calc(cnt, v);
            cnt++;
        }
        if (ch == '-') {
            int v;
            cin >> v;
            unite(v, dp[v][0]);
        }
        if (ch == '?') {
            int u, v;
            cin >> u >> v;
            cout << get(get_lca(u, v)) << endl;
        }
    }

    return 0;
}