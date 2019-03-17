#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct node {
    node* l;
    node* r;
    int min;
    int ind;
    int dt;
    node() {
        l = r = nullptr;
        min = 0;
        ind = 0;
        dt = -1;
    }
};

void push(node* &v) {
    if (v -> dt == -1) {
        return;
    }
    v -> l -> dt = max(v -> l -> dt, v -> dt);
    v -> r -> dt = max(v -> r -> dt, v -> dt);
    v -> l -> min = max(v -> dt, v -> l -> min);
    v -> r -> min = max(v -> dt, v -> r -> min);
    v -> dt = -1;
}

void set(node* &v, int l, int r, int ql, int qr, int val) {
    if (r <= ql || l >= qr) {
        return;
    }
    int m = (l + r) / 2;
    if (!v -> l) {
        v -> l = new node();
        v -> r = new node();
        v -> l -> ind = l;
        v -> r -> ind = m;
    }
    push(v);
    if (l >= ql && r <= qr) {
        v -> dt = val;
        v -> min = max(val, v -> min);
        return;
    }
    set(v -> l, l, m, ql, qr, val);
    set(v -> r, m, r, ql, qr, val);
    if (v -> l -> min <= v -> r -> min) {
        v -> min = v -> l -> min;
        v -> ind = v -> l -> ind;
    } else {
        v -> min = v -> r -> min;
        v -> ind = v -> r -> ind;
    }
}

pair<int, int> get_min(node* &v, int l, int r, int ql, int qr) {
    if (r <= ql || l >= qr) {
        return {1e9, -1};
    }
    int m = (l + r) / 2;
    if (!v -> l) {
        v -> l = new node();
        v -> r = new node();
        v -> l -> ind = l;
        v -> r -> ind = m;
    }
    push(v);
    if (l >= ql && r <= qr) {
        return {v -> min, v -> ind};
    }
    pair <int, int> left, right;
    left = get_min(v -> l, l, m, ql, qr);
    right = get_min(v -> r, m, r, ql, qr);
    if (left.first <= right.first) {
        return left;
    } else {
        return right;
    }
}

node* root = new node();
int a[10000];

void gentest() {
    int n, m;

    string s;
    int l, r;
    n = 8;
    m = 10;



    for (int i = 0; i < m; i++) {
        int type = rand() % 2;
        l = rand() % n + 1;
        r = rand() % n + 1;
        if (l > r) {
            swap(l, r);
        }
        l--;
        if (type == 0) {
            int x = rand() % 100 + 1;
            for (int j = l + 1; j <= r; j++) {
                a[j] = max(a[j], x);
            }
            cout << "defend" << " " << l + 1 << " " << r  << " " << x << endl;
            set(root, 0, n, l, r, x);
        } else {
            cout << "attack " << " " << l + 1 << " " << r << endl;
            int k = l + 1;
            int mn = a[l + 1];
            for (int j = l + 1; j <= r; j++) {
                if (mn > a[j]) {
                    k = j;
                    mn = a[j];
                }
            }
            pair <int, int> ans = get_min(root, 0, n, l, r);
            cout << ans.first << " " << ans.second + 1 << endl;
            cout << "real answer: " << mn <<  " " << k << endl;
            if (ans.first != mn || ans.second + 1 != k) {
                cout << "AAAAAAA" << endl;
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    srand(time(NULL));
    //gentest();

    int n, m;
    cin >> n >> m;
    string s;
    int l, r;

    while (cin >> s >> l >> r) {
        l--;
        if (s == "defend") {
            int x;
            cin >> x;
            set(root, 0, n, l, r, x);
        } else {
            pair <int, int> ans = get_min(root, 0, n, l, r);
            cout << ans.first << " " << ans.second + 1 << endl;
        }
    }
    return 0;
}