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

void split(node* t, ll x, node *&l, node *&r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    //t->r->x < t->x < t->l->x

    if (x > t->x) {
        split(t->l, x, l, t->l);
        r = t;
    } else {
        split(t->r, x, t->r, r);
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
    node *l, *r;
    split(t, x, l, r);
    t = merge(merge(l, new node(x)), r);
}

void erase(node *&t, ll x) {
    node *l, *r;
    node *l1, *r1;
    split(t, x, l, r);
    split(l, x + 1, l1, r1);
    t = merge(l1, r);
}

bool find(node *&t, ll x) {
    if (!t) {
        return false;
    }
    if (t->x == x) {
        return true;
    }

    if ((t->x) > x) {
        return find(t -> l, x);
    } else {
        return find(t -> r, x);
    }
}


ll find_k(node *t, ll k) {
    ll cnt_l = 0;
    if (t->l) {
        cnt_l = t->l->cnt;
    }
    if (cnt_l >= k) {
        return find_k(t->l, k);
    }
    if (k - cnt_l == 1) {
        return t->x;
    }
    return find_k(t->r, k - cnt_l - 1);
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    srand(time(NULL));

    node *root = nullptr;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "+1" || s == "1") {
            ll x;
            cin >> x;
            insert(root, x);
        }
        if (s == "-1") {
            ll x;
            cin >> x;
            erase(root, x);
        }
        if (s == "0") {
            ll k;
            cin >> k;
            cout << find_k(root, k) << endl;
        }
    }

    return 0;
}