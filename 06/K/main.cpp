#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 10;
const int MAXP = 20;
vector <int> graph[MAXN];
int previous[MAXN];
ll d[MAXN];
int up[MAXN][MAXP];

struct count {
    ll cnt;
    ll sum_current;
    ll sum_prev;
};

count black[MAXN];
count white[MAXN];
int color[MAXN];
count black_white[MAXN][2];

void dfs(int v, int p, ll cnt) {
    previous[v] = p;
    d[v] = cnt;
    for (auto to : graph[v]) {
        if (to != p) {
            dfs(to, v, cnt + 1);
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
    return previous[v];
}

int level[MAXN];
int calc_size(int v, int p) {
    int cnt = 1;
    for (int i = 0; i < graph[v].size(); i++)
    {
        if (level[graph[v][i]] == -1 && graph[v][i] != p)
            cnt += calc_size(graph[v][i], v);
    }

    return cnt;
}

int prev_centroid[MAXN];
int centroid = -1;
int get_centroid(int v, int n, int p) {
    int sz = 1;
    for (int i = 0; i < graph[v].size(); i++) {
        int nxt = graph[v][i];
        if (nxt == p)
            continue;
        if (level[nxt] != -1)
            continue;
        sz += get_centroid(nxt, n, v);
    }
    if (sz * 2 > n && centroid == -1)
    {
        centroid = v;
    }
    return sz;
}

void build(int v, int lvl, int p) {
    int sz = calc_size(v, -1);
    get_centroid(v, sz, -1);
    level[centroid] = lvl;
    prev_centroid[centroid] = p;
    int c = centroid;
    centroid = -1;
    for (int i = 0; i < graph[c].size(); i++)
    {
        if (level[graph[c][i]] == -1 && graph[c][i] != p)
            build(graph[c][i], lvl + 1, c);
    }
}

ll distance(int u, int v) {
    return d[u] + d[v] - 2 * d[get_lca(u, v)];
}

void paint_in_black(int n) {
    for (int i = 0; i < n; i++) {
        int v = i;
        color[v] = 1;
        while (true) {
            black_white[v][1].cnt++;
            black_white[v][1].sum_current += distance(v, i);
            if (prev_centroid[v] == -1) {
                break;
            }
            black_white[v][1].sum_prev += distance(i, prev_centroid[v]);
            v = prev_centroid[v];
        }
    }

}

void precalc(int v, int n) {
    dfs(v, -1, 0);
    for (int i = 0; i < n; i++) {
        up[i][0] = previous[i];
        level[i] = -1;
    }

    for (int k = 1; k < MAXP; k++) {
        for (int i = 0; i < n; i++) {
            up[i][k] = up[up[i][k - 1]][k - 1];
        }
    }

    build(v, 1, -1);
    paint_in_black(n);
}

ll k[2];
void change_color(int u) {
    int clr = color[u];
    k[1] = 1;
    k[0] = -1;
    if (clr == 1) {
        k[1] = -1;
        k[0] = 1;
    }
    int v = u;
    while (true) {
        for (int i = 0; i < 2; i++) {
            black_white[v][i].cnt += k[i];
            black_white[v][i].sum_current += k[i] * distance(u, v);
        }
        if (prev_centroid[v] == -1) {
            break;
        }
        for (int i = 0; i < 2; i++) {
            black_white[v][i].sum_prev += k[i] * distance(u, prev_centroid[v]);
        }
        v = prev_centroid[v];
    }
    color[u] = 1 - clr;
}


ll get_ans(int u) {
    int clr = color[u];
    ll ans = black_white[u][clr].sum_current;
    if (prev_centroid[u] == -1) {
        return ans;
    }
    int v = u;
    int prev = prev_centroid[u];
    while (prev != -1) {
        ans += black_white[prev][clr].sum_current - black_white[v][clr].sum_prev + (black_white[prev][clr].cnt - black_white[v][clr].cnt) * distance(u, prev);
        v = prev;
        prev = prev_centroid[v];
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    precalc(0, n);
    for (int i = 0; i < m; i++) {
        int t, u;
        cin >> t >> u;
        u--;
        if (t == 1) {
            change_color(u);
        }
        if (t == 2) {
            cout << get_ans(u) << endl;
        }
    }
    return 0;
}