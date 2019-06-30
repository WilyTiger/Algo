#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

const int MAXN = 1e5;
typedef long long ll;

struct node {
    ll cnt;
    ll y;
    pair <int, int> edge;
    node* left;
    node* right;
    node* p;
    node(pair<int, int> edge): edge(edge), cnt(1), y(rand()), left(nullptr), right(nullptr), p(nullptr) {};
};

void upd(node *&t) {
    if (!t) {
        return;
    }
    t->cnt = 1;
    if (t->left) {
        t->cnt += t->left->cnt;
    }
    if (t->right) {
        t->cnt += t->right->cnt;
    }
}

ll get_cnt(node *&t) {
    if (!t) {
        return 0;
    }
    return t->cnt;
}

node* merge(node *l, node *r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }
    if (l->y >= r->y) {
        l->right = merge(l->right, r);
        if (l->right) {
            l->right->p = l;
        }
        upd(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        if (r->left) {
            r->left->p = r;
        }
        upd(r);
        return r;
    }
}

void split(node* t, ll k, node *&l, node *&r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    ll cnt = get_cnt(t->left);

    if (cnt >= k) {
        split(t->left, k, l, t->left);
        if (t->left) {
            t->left->p = t;
        }
        r = t;
    } else {
        split(t->right, k - cnt - 1, t->right, r);
        if (t->right) {
            t->right->p = t;
        }
        l = t;
    }
    upd(t);
    if (l)
        l -> p = nullptr;
    if (r)
        r -> p = nullptr;
}

node* get_root(node *t) {
    if (!t) {
        return t;
    }

    while(t->p) {
        t = t->p;
    }

    return t;
}

ll get_position(node *t) {
    if (!t) {
        return 0;
    }

    ll cnt = get_cnt(t->left);
    while (t->p) {
        if (t == t->p->right) {
            cnt += get_cnt(t->p->left) + 1;
        }
        t = t->p;
    }
    return cnt;
}

map <pair<int, int>, node*> edge_pointer;
node* pointer[MAXN];

void link(int a, int b) {
    node *u = edge_pointer[{a, a}];
    node *v = edge_pointer[{b, b}];

    node *A, *B;
    node *root_u = get_root(u);
    split(root_u, get_position(u) + 1, A, B);

    node *C, *D;
    split(get_root(v), get_position(v), C, D);

    node* ab_edge = new node({a, b});
    node* ba_edge = new node({b, a});
    merge(merge(merge(A, ab_edge), D), merge(C, merge(ba_edge, B)));
    edge_pointer[{a, b}] = ab_edge;
    edge_pointer[{b, a}] = ba_edge;
}

void cut(int a, int b) {
    node *ab_edge = edge_pointer[{a, b}];
    node *ba_edge = edge_pointer[{b, a}];
    edge_pointer.erase({a, b});
    edge_pointer.erase({b, a});
    node *A, *BC;
    if (get_position(ab_edge) > get_position(ba_edge)) {
        swap(ab_edge, ba_edge);
    }
    node *root = get_root(ab_edge);

    split(get_root(ab_edge), get_position(ab_edge), A, BC);

    node *useless, *BC1;
    split(BC, 1, useless, BC1);

    node *B, *C1;
    split(BC1, get_position(ba_edge), B, C1);
    node *C, *useless2;
    split(C1, 1, useless2, C);

    merge(A, C);
}

bool connected(int a, int b) {
    return get_root(edge_pointer[{a, a}]) == get_root(edge_pointer[{b, b}]);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        edge_pointer[{i, i}] = new node({i, i});
    }

    for (int i = 0; i < m; i++) {
        string s;
        int u, v;
        cin >> s >> u >> v;
        u--;
        v--;
        if (s == "link") {
            link(u, v);
        }
        if (s == "cut") {
            cut(u, v);
        }
        if (s == "connected") {
            cout << connected(u, v) << endl;
        }
    }
    return 0;
}