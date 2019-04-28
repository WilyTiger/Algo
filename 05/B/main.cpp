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

    explicit node(ll x): x(x), y(rand()), l(nullptr), r(nullptr) {};
};

void split(node* t, ll x, node *&l, node *&r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    if (t->x <= x) {
        split(t->r, x, t->r, r);
        l = t;
    } else {
        split(t->l, x, l, t->l);
        r = t;
    }
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
        return l;
    } else {
        r->l = merge(l, r->l);
        return r;
    }
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

void insert(node *&t, ll x) {
    if (find(t, x)) {
        return;
    }
    node *l, *r;
    split(t, x, l, r);
    t = merge(merge(l, new node(x)), r);
}

node* minimum(node*& v) {
    if (!v->l) {
        return v;
    }
    return minimum(v->l);
}

node* maximum(node*& v) {
    if (!v->r) {
        return v;
    }
    return minimum(v->r);
}

void erase(node *&t, ll x) {
    if (!find(t, x)) {
        return;
    }
    node *l1, *r1;
    node *l2, *r2;
    split(t, x, l1, r1);
    split(l1, x - 1, l2, r2);
    t = merge(l2, r1);
}

node* next(node *&v, int x) {
    node* current = v;
    node* ans = nullptr;
    while (current) {
        if (x < current->x) {
            ans = current;
            current = current->l;
        } else {
            current = current->r;
        }
    }
    return ans;
}

node* prev(node *&v, int x) {
    node* current = v;
    node* ans = nullptr;
    while (current) {
        if (x <= current->x) {
            current = current->l;
        } else {
            ans = current;
            current = current->r;
        }
    }
    return ans;
}



int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string s;
    int x;
    node* root = nullptr;
    srand(time(NULL));
    while (cin >> s >> x) {
        if (s == "insert") {
            insert(root, x);
        }
        if (s == "exists") {
            if (find(root, x))
                cout << "true" << endl;
            else {
                cout << "false" << endl;
            }
        }
        if (s == "delete") {
            erase(root, x);
        }
        if (s == "next") {
            node* ans = next(root, x);
            if (!ans) {
                cout << "none" << endl;
            } else {
                cout << ans->x << endl;
            }
        }
        if (s == "prev") {
            node* ans = prev(root, x);
            if (!ans) {
                cout << "none" << endl;
            } else {
                cout << ans->x << endl;
            }
        }
    }

    return 0;
}