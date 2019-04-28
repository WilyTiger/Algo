#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll MOD = 1e9;

struct node {
    ll x, y;
    node *l, *r, *p;
    bool cycle;
    int cnt;
    explicit node(ll x): x(x), p(nullptr), y(rand()), cycle(false),  cnt(1), l(nullptr), r(nullptr) {};
};

void upd(node *&t) {
    if (!t) {
        return;
    }
    t->cnt = 1;
    if (t->l) {
        t->cnt += t->l->cnt;
    }
    if (t->r) {
        t->cnt += t->r->cnt;
    }
}

int get_cnt(node *t) {
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
        l->r = merge(l->r, r);
        if (l->r) {
            l->r->p = l;
        }
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        if (r->l) {
            r->l->p = r;
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

    ll cnt = get_cnt(t->l);

    if (cnt >= k) {
        split(t->l, k, l, t->l);
        if (t->l) {
            t->l->p = t;
        }
        r = t;
    } else {
        split(t->r, k - cnt - 1, t->r, r);
        if (t->r) {
            t->r->p = t;
        }
        l = t;
    }
    upd(t);
}

const int MAXN = 1e5;
node* roots[MAXN];

node* get_parent(node* t) {
    if (!t) {
        return t;
    }

    while (t->p) {
        t = t->p;
    }

    return t;
}

int get_position(node *t) {
    if (!t) {
        return 0;
    }

    int cnt = get_cnt(t->l);
    while (t->p) {
        if (t == t->p->r) {
            cnt += get_cnt(t->p->l) + 1;
        }
        t = t->p;
    }
    return cnt;
}

void reverse(node *t) {
    if (!t)
        return;
    swap(t->l, t->r);
    reverse(t->l);
    reverse(t->r);
}

void add(node* u, node* v) {
    node *parent_u, *parent_v;
    parent_u = get_parent(u);
    parent_v = get_parent(v);
    if (parent_u == parent_v) {
        parent_u->cycle = true;
        return;
    }
    int posv = get_position(v);
    int posu = get_position(u);
    if (posu == 0)
        reverse(parent_u);
    if (posv == parent_v->cnt - 1)
        reverse(parent_v);
    merge(parent_u, parent_v);
}

void remove(node*& u, node*& v) {
    node* parent;
    parent = get_parent(u);
    int posu = get_position(u);
    int posv = get_position(v);
    if (!parent->cycle) {
        node *l, *r;
        split(parent, max(posu, posv), l, r);
        r->p = l->p = nullptr;
    } else {
        parent->cycle = false;
        if (abs(posu - posv) == parent->cnt - 1)
            return;
        node *l, *r;
        split(parent, max(posu, posv), l, r);
        reverse(l);
        reverse(r);
        merge(l, r);
    }
}

int get_ans(node* u, node* v) {
    node* parent_u = get_parent(u);
    node* parent_v = get_parent(v);
    if (parent_u != parent_v) {
        return -1;
    }
    node* parent = parent_u;
    int posu = get_position(u);
    int posv = get_position(v);
    if (!parent->cycle) {
        return abs(posu - posv) - 1;
    }
    return min(abs(posv - posu), min(posu, posv) + (parent->cnt - max(posu, posv))) - 1;
}

void print(node *t) {
    if (t->l) {
        print(t->l);
    }
    cout << t->x;
    if (t->r) {
        print(t->r);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, q;
    cin >> n >> m >> q;
    srand(time(NULL));

    for (int i = 1; i <= n; i++) {
        roots[i] = new node(i);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        add(roots[u], roots[v]);
    }



    for (int i = 0; i < q; i++) {
        char ch;
        cin >> ch;
        if (ch == '+') {
            int u, v;
            cin >> u >> v;
            add(roots[u], roots[v]);
        }
        if (ch == '-') {
            int u, v;
            cin >> u >> v;
            remove(roots[u], roots[v]);
        }
        if (ch == '?') {
            int u, v;
            cin >> u >> v;
            if (u == v) {
                cout << 0 << endl;
            } else {
                cout << get_ans(roots[u], roots[v]) << endl;
            }
        }
        /*
        for (int j = 1; j <= n; j++) {
            if (!roots[j]->p) {
                print(roots[j]);
                cout << endl;
            }
        }
        cout << endl;*/
    }


    return 0;
}