#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 3e5;
const int MAXP = 20;

int p[MAXN];
int dp[MAXN][MAXP];
int minimum[MAXN][MAXP];
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
        for (int j = 1; j < MAXP; j++) {
            minimum[i][j] = 1e9;
        }
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = p[i];
    }

    for (int k = 1; k < MAXP; k++) {
        for (int i = 0; i < n; i++) {
            dp[i][k] = dp[dp[i][k - 1]][k - 1];
            minimum[i][k] = min(minimum[dp[i][k - 1]][k - 1], minimum[i][k - 1]);
        }
    }
}

int get_lca(int u, int v) {
    if (d[u] < d[v]) {
        swap(u, v);
    }

    int r = d[u] - d[v];
    int ans = 1e9;
    for (int i = MAXP - 2; i >= 0; i--) {
        if (r & (1 << i)) {
            ans = min(ans, minimum[u][i]);
            u = dp[u][i];
        }
    }


    if (v == u) {
        return ans;
    }

    for (int i = MAXP - 2; i >= 0; i--) {
        if (dp[v][i] != dp[u][i]) {
            ans = min(ans, minimum[v][i]);
            ans = min(ans, minimum[u][i]);
            v = dp[v][i];
            u = dp[u][i];
        }
    }
    return min(ans, min(minimum[u][0], minimum[v][0]));
}

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);

    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.sync_with_stdio(0);
    cout.tie(0);
    cin >> n;

    int root = 0;
    for (int i = 1; i < n; i++) {
        cin >> p[i] >> minimum[i][0];
        p[i]--;
        tree[p[i]].push_back(i);
    }

    minimum[0][0] = 1e9;
    p[0] = 0;
    pre_calc(root);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (i) {
            cout << endl;
        }
        cout << get_lca(a, b);
    }
    return 0;
}