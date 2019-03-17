#include <iostream>
#include <cstdio>

using namespace std;

const int INF = -1e9;
struct node {
    int sum;
    int mx;
    int dt;
    node *l;
    node *r;
    node() {
        l = r = nullptr;
        mx = INF;
        sum = 0;
        dt = INF;
    }
};

void push(node* &v, int l, int r) {
    if (v -> dt == INF) {
        return;
    }
    int m = (l + r) / 2;
    v -> l -> sum = (v -> dt) * (m - l);
    v -> r -> sum = (v -> dt) * (r - m);
    v -> l -> mx = max(0, v -> l -> sum);
    v -> r -> mx = max(0, v -> r -> sum);
    v -> l -> dt = v -> r -> dt = v -> dt;
    v -> dt = INF;
}

void upd(node* &v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || ql >= r) {
        return;
    }
    if (!v -> l) {
        v -> l = new node();
        v -> r = new node();
    }
    push(v, l, r);
    if (l >= ql && r <= qr) {
        v -> sum = (r - l) * x;
        v -> mx = max(0, v -> sum);
        v -> dt = x;
        return;
    }
    int m = (l + r) / 2;
    upd(v -> l, l, m, ql, qr, x);
    upd(v -> r, m, r, ql, qr, x);
    v -> sum = v -> l -> sum + v -> r -> sum;
    v -> mx = max(v -> l -> mx, v -> r -> mx + v -> l -> sum);
}

int get_ans(node *&v, int l, int r, int h) {
    if (v -> mx <= h) {
        return r - l;
    }
    if (r - l == 1) {
        return 0;
    }
    if (!v -> l) {
        v -> l = new node();
        v -> r = new node();
    }
    push(v, l, r);
    int m = (l + r) / 2;
    if (v -> l -> mx <= h) {
        return get_ans(v -> l, l, m, h) + get_ans(v -> r, m, r, h - v -> l -> sum);
    } else {
        return get_ans(v -> l, l, m, h);
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    node* root = new node();
    while (true) {
        char ch;
        cin >> ch;
        if (ch == 'I') {
            int a, b, d;
            cin >> a >> b >> d;
            a--;
            upd(root, 0, n, a, b, d);
        }
        if (ch == 'Q') {
            int h;
            cin >> h;
            cout << get_ans(root, 0, n, h) << endl;
        }
        if (ch == 'E') {
            break;
        }
    }
    return 0;
}