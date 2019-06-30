#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 2e5 + 4;
vector <int> graph[MAXN];

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

int pred[MAXN];
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
    pred[centroid] = p;
    int c = centroid;
    centroid = -1;
    for (int i = 0; i < graph[c].size(); i++)
    {
        if (level[graph[c][i]] == -1 && graph[c][i] != p)
            build(graph[c][i], lvl + 1, c);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        level[i] = -1;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    level[n - 1] = -1;

    build(0, 1, -1);

    for (int i = 0; i < n; i++) {
        cout << pred[i] + 1 << " ";
    }
    return 0;
}