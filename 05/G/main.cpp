#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll MOD = 1e9;

struct node {
    ll x, y;
    node *l, *r;
    ll cnt;
    explicit node(ll x): x(x), y(rand()), cnt(1), l(nullptr), r(nullptr) {};
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

ll get_cnt(node *t) {
    if (!t) {
        return 0;
    }
    return t->cnt;
}

void split(node* t, ll k, node *&l, node *&r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    ll cnt = get_cnt(t->l);

    if (cnt > k) {
        split(t->l, k, l, t->l);
        r = t;
    } else {
        split(t->r, k - cnt - 1, t->r, r);
        l = t;
    }
    upd(t);
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
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}

void insert(node *&t, ll x) {
    t = merge(t, new node(x));
}

void move(node *&t, ll l, ll r) {
    node *l1, *r1;
    node *l2, *r2;
    split(t, r, l1, r1);
    split(l1, l - 1, l2, r2);
    t = merge(r2, merge(l2, r1));
}

void print(node *t) {
    if (t->l) {
        print(t->l);
    }
    cout << t->x << " ";
    if (t->r) {
        print(t->r);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    srand(time(NULL));

    node *root = nullptr;
    for (int i = 1; i <= n; i++) {
        insert(root, i);
    }

    for (int j = 0; j < m; j++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        move(root, l, r);
    }

    print(root);
    return 0;
}
