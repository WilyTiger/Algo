#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
const int MAXN = 3e5 + 5;
const int MAXP = 20;
bool was[MAXN];
int trsize[MAXN];
vector <int> graph[MAXN];
int up[MAXP][MAXN];
int path_nums[MAXN];
int len[MAXN];
int pos_path[MAXN];
int tin[MAXN];
int tout[MAXN];
int p[MAXN];
int root[MAXN];

int pn = 1;

struct node {
    node *vl;
    node *vr;
    ll key;
    ll dt;
    int l;
    int r;
};


node *path_trees[MAXN];
void BuildTree(node *&v, int l, int r) {
    v->l = l;
    v->r = r;
    v->dt = 0;
    if (r - l == 1) {
        v->key = 0;
        v -> vl = v -> vr = NULL;
        return;
    }
    v->vl = new node();
    v->vr = new node();
    int m = (l + r) >> 1;
    BuildTree(v->vl, l, m);
    BuildTree(v->vr, m, r);
}

void push(node *&v) {
    if (v->dt == 0) {
        return;
    }
    if (v->r - v->l == 1) {
        v->key += v-> dt;
        v->dt = 0;
        return;
    }
    v->vl->dt += v->dt;
    v->vr->dt += v->dt;
    v->dt = 0;
}

void upd(node *&v, int ql, int qr, ll x) {
    if (!v)
        return;
    if (v->r <= ql || v->l >= qr) {
        return;
    }
    push(v);
    if (v->l >= ql && v->r <= qr) {
        v->dt = x;
        return;
    }
    upd(v->vl, ql, qr, x);
    upd(v->vr, ql, qr, x);
}

int tm = 1;
int d[MAXN];
void dfs(int v) {
    was[v] = 1;
    tin[v] = tm++;
    trsize[v] = 1;
    for (int i = 0; i < graph[v].size();i++)
    {
        if (!was[graph[v][i]])
        {
            d[graph[v][i]] = d[v] + 1;
            p[graph[v][i]] = v;
            dfs(graph[v][i]);
            trsize[v] += trsize[graph[v][i]];
        }
    }
    tout[v] = tm++;
}

int new_path(int u) {
    root[++pn] = u;
    return pn;
}

void build_decomposition(int v, int num) {
    was[v] = 1;
    path_nums[v] = num;
    pos_path[v] = len[num]++;
    for (int i = 0; i < graph[v].size(); i++)
    {
        if (!was[graph[v][i]])
        {
            if (2 * trsize[graph[v][i]] >= trsize[v])
                build_decomposition(graph[v][i], num);
            else
                build_decomposition(graph[v][i], new_path(graph[v][i]));
        }
    }
}


void upd(int a, int lca, int d) {
    while (path_nums[a] != path_nums[lca]) {
        upd(path_trees[path_nums[a]], 0, pos_path[a] + 1, d);
        a = p[root[path_nums[a]]];
    }
    upd(path_trees[path_nums[a]], pos_path[lca], pos_path[a] + 1, d);
}

ll get_ans(node *&v, int pos) {
    if (!v)
        return 0;
    if (pos >= v -> l && pos < v -> r) {
        push(v);
        if (v -> r - v -> l == 1) {
            return v -> key;
        }
        return get_ans(v -> vl, pos) + get_ans(v -> vr, pos);
    }
    return 0;
}

int n;
void build_up() {
    for (int i = 0; i < n; i++) {
        up[0][i] = p[i];
    }

    for (int i = 1; i < MAXP; i++) {
        for (int j = 0; j < n; j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
}

int get_LCA(int a, int b) {
    if (a == b) {
        return a;
    }

    if (tin[a] < tin[b] && tout[a] > tout[b]) {
        return a;
    }

    if (tin[b] < tin[a] && tout[b] > tout[a]) {
        return b;
    }

    for (int i = MAXP - 1; i >= 0; i--) {
        if (!(tin[up[i][a]] < tin[b] && tout[up[i][a]] > tout[b])) {
            a = up[i][a];
        }
    }

    return up[0][a];
}

void upd1(int a, int b, int x) {
    while (path_nums[a] != path_nums[b]) {
        if (d[root[path_nums[a]]] < d[root[path_nums[b]]]) {
            swap(a, b);
        }
        upd(path_trees[path_nums[a]], 0, pos_path[a] + 1, x);
        a = p[root[path_nums[a]]];
    }
    if (pos_path[a] > pos_path[b]) {
        swap(a, b);
    }
    upd(path_trees[path_nums[a]], pos_path[a], pos_path[b] + 1, x);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(0);

    memset(was, 0, sizeof(was));
    build_decomposition(0, 1);

    for (int i = 1; i <= pn; i++) {
        path_trees[i] = new node();
        BuildTree(path_trees[i], 0, len[i]);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        char ch;
        cin >> ch;

        if (ch == '+') {
            int x, y, d;
            scanf("%d%d%d", &x, &y, &d);
            x--;
            y--;
            upd1(x, y, d);
        } else {
            int x;
            scanf("%d", &x);
            x--;
            printf("%lld\n", get_ans(path_trees[path_nums[x]], pos_path[x]));
        }
    }
    return 0;
}
