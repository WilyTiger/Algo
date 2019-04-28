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
    char letter;
    ll ans;
    explicit node(ll cnt, char letter): x(cnt), letter(letter), y(rand()), cnt(cnt), ans(1 << (letter - 'a')), l(nullptr), r(nullptr) {};
};

void upd(node *&t) {
    if (!t) {
        return;
    }
    t->cnt = t->x;
    t->ans = 1 << (t->letter - 'a');
    if (t->l) {
        t->ans |= t->l->ans;
        t->cnt += t->l->cnt;
    }
    if (t->r) {
        t->ans |= t->r->ans;
        t->cnt += t->r->cnt;
    }
}

ll get_cnt(node *t) {
    if (!t) {
        return 0;
    }
    return t->cnt;
}

ll get_ans(node *t) {
    if (!t) {
        return 0;
    }
    return t->ans;
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

void split(node* t, ll k, node *&l, node *&r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    ll cnt = get_cnt(t->l);

    if (cnt < k && cnt + t->x > k) {
        l = merge(t->l, new node(k - cnt, t->letter));
        r = merge(new node(t->x - (k - cnt), t->letter), t->r);
        upd(l);
        upd(r);
        return;
    }
    if (cnt >= k) {
        split(t->l, k, l, t->l);
        r = t;
    } else {
        split(t->r, k - cnt - t->x, t->r, r);
        l = t;
    }
    upd(t);
}

void print(node *t) {
    if (t->l) {
        print(t->l);
    }
    for (int i = 0; i < t->x; i++) {
        cout << t->letter << "(" << t->ans << ") ";
    }
    if (t->r) {
        print(t->r);
    }
}

void insert(node *&t, int k, int cnt, char letter) {
    node *l, *r;
    split(t, k, l, r);
    t = merge(l, merge(new node(cnt, letter), r));
}


void remove(node *&t, int k, int cnt) {
    node *l1, *r1;
    node *l2, *r2;
    split(t, k, l1, r1);
    split(r1, cnt, l2, r2);
    t = merge(l1, r2);
}

ll query(node *&t, int l, int r) {
    node *l1, *r1;
    node *l2, *r2;
    split(t, l, l1, r1);
    split(r1, r - l + 1, l2, r2);
    ll ans = get_ans(l2);
    t = merge(l1, merge(l2, r2));
    int cnt = 0;
    for (int i = 0; i < 27; i++) {
        if (ans & (1 << i)) {
            cnt++;
        }
    }
    return cnt;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    srand(time(NULL));

    node *root = nullptr;
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        if (ch == '+') {
            int ind, cnt;
            char letter;
            cin >> ind >> cnt >> letter;
            ind--;
            insert(root, ind, cnt, letter);
        }
        if (ch == '-') {
            int ind, cnt;
            cin >> ind >> cnt;
            ind--;
            remove(root, ind, cnt);
        }
            //print(root);
        //cout << endl;
        if (ch == '?') {
            int ind1, ind2;
            cin >> ind1 >> ind2;
            ind1--;
            ind2--;
            cout << query(root, ind1, ind2) << endl;
        }
    }

    return 0;
}