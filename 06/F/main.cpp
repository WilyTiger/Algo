#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 10;
const int MAXP = 20;
typedef long long ll;
int p[MAXN];
int up[MAXN][MAXP];
int n;
ll d[MAXN];
vector<int> tree[MAXN];
int tin[MAXN];
int t = 0;
void dfs(int u, ll cnt) {
    d[u] = cnt;
    tin[u] = t++;
    for (auto v : tree[u]) {
        dfs(v, cnt + 1);
    }
}

bool cmp(int a, int b) {
    return tin[a] < tin[b];
}

void precalc(int root) {
    dfs(root, 1);
    for (int i = 0; i < n; i++) {
        up[i][0] = p[i];
    }

    for (int k = 1; k < MAXP; k++) {
        for (int i = 0; i < n; i++) {
            up[i][k] = up[up[i][k - 1]][k - 1];
        }
    }
}

int get_lca(int u, int v) {
    if (d[u] < d[v]) {
        swap(u, v);
    }

    ll r = d[u] - d[v];
    for (int i = MAXP - 1; i >= 0; i--) {
        if (r & (1 << i)) {
            u = up[u][i];
        }
    }

    if (v == u) {
        return u;
    }

    for (int i = MAXP - 1; i >= 0; i--) {
        if (up[v][i] != up[u][i]) {
            v = up[v][i];
            u = up[u][i];
        }
    }
    return p[v];
}

int main() {
    scanf("%d", &n);
    int root = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        if (p[i] == -1) {
            root = i;
        } else {
            p[i]--;
            tree[p[i]].push_back(i);
        }
    }
    precalc(root);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        vector <int> vec;
        for (int j = 0; j < k; j++) {
            int x;
            scanf("%d", &x);
            x--;
            vec.push_back(x);
        }
        sort(vec.begin(), vec.end(), &cmp);
        ll ans = d[vec[0]];
        for (int j = 1; j < k; j++) {
            ans += d[vec[j]];
            int lca = get_lca(vec[j - 1], vec[j]);
            ans -= d[lca];
        }
        printf("%d\n", ans);
    }

    return 0;
}
