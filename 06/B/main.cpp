#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 3e5;
const int MAXP = 20;

int p[MAXN];
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

void pre_calc(int root) {
    dfs(root, -1, 0);
    for (int i = 0; i < n; i++) {
        dp[i][0] = p[i];
    }

    for (int k = 1; k < MAXP; k++) {
        for (int i = 0; i < n; i++) {
            if (dp[i][k - 1] == -1) {
                dp[i][k] = -1;
            } else {
                dp[i][k] = dp[dp[i][k - 1]][k - 1];
            }
        }
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
    return p[v];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n;

    int root = 0;
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        tree[p[i]].push_back(i);

    }

    p[0] = 0;
    pre_calc(root);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        cout << get_lca(a, b) + 1 << endl;
    }
    return 0;
}