#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll MOD = 1e9;

struct node {
    ll x, y;
    ll sum;
    node *l, *r;

    explicit node(ll x): x(x), y(rand()), sum(x), l(nullptr), r(nullptr) {};
};

void upd(node *&t) {
    if (!t) {
        return;
    }
    t->sum = t->x;
    if (t->l) {
        t->sum += t->l->sum;
    }
    if (t->r) {
        t->sum += t->r->sum;
    }
}
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

ll get_sum(node *&t, ll l, ll r) {
    node *left, *right;
    node *left1, *right1;
    split(t, r, left, right);
    split(left, l - 1, left1, right1);
    if (!right1) {
        t = merge(merge(left1, right1), right);
        return 0;
    }
    ll ans = right1->sum;
    t = merge(merge(left1, right1), right);
    return ans;
}


int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    srand(time(NULL));
    ll y = 0;
    node *root = nullptr;
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        if (ch == '+') {
            ll x;
            cin >> x;
            if (!find(root, (x + y) % MOD)) {
                insert(root, (x + y) % MOD);
            }
            y = 0;
        }
        if (ch == '?') {
            ll l, r;
            cin >> l >> r;
            y = get_sum(root, l, r);
            cout << y << endl;
        }
    }


    return 0;
}