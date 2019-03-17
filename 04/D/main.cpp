#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

map <string, int> color;

const int MAXN = 5e5;

struct node {
    node* l;
    node* r;
    int inner;
    int l_color;
    int r_color;
    int length;
    int set_value;
    node() {
        l = r = nullptr;
        inner = l_color = r_color = length = 0;
        set_value = -1;
    }
};

void push(node* &v, int l, int r) {
    if (v -> set_value == -1)
        return;
    v -> l -> set_value = v -> r -> set_value = v -> set_value;
    int value = v -> set_value;
    int m = (l + r) / 2;
    if (value == 0) {
        v -> l -> l_color = v -> r -> l_color = v -> l -> r_color = v -> r -> r_color = value;
        v -> l -> inner = v -> r -> inner = v -> l -> length = v -> r -> length = 0;
    } else {
        v -> l -> inner = v -> r -> inner = 1;
        v -> l -> l_color = v -> r -> l_color = v -> l -> r_color = v -> r -> r_color = value;
        v -> l -> length = m - l;
        v -> r -> length = r - m;
    }
    v -> set_value = -1;
}

void set(node* &v, int l, int r, int ql, int qr, int value) {
    if (qr <= l || ql >= r) {
        return;
    }
    if (!v -> l) {
        v -> l = new node();
        v -> r = new node();
    }
    push(v, l, r);
    if (l >= ql && r <= qr) {
        v -> l_color = v -> r_color = value;
        if (value == 0) {
            v -> inner = v -> length = 0;
        } else {
            v -> inner = 1;
            v -> length = r - l;
        }
        v -> set_value = value;
        return;
    }
    int m = (l + r) / 2;
    set(v -> l, l, m, ql, qr, value);
    set(v -> r, m, r, ql, qr, value);
    v -> inner = v -> l -> inner + v -> r -> inner;
    v -> l_color = v -> l -> l_color;
    v -> r_color = v -> r -> r_color;
    v -> length = v -> l -> length + v -> r -> length;
    if (!(v -> l -> r_color != v -> r -> l_color || (v -> l -> r_color == v -> r -> l_color && v -> l -> r_color == 0))) {
        v -> inner--;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    node* root = new node();
    color["W"] = 0;
    color["B"] = 1;
    int n;
    cin >> n;


    string s;
    int x, l;
    //BuildTree(1, 0, 10);
    while (cin >> s >> x >> l) {
        int clr = color[s];
        set(root, -MAXN, MAXN + 1, x, x + l, clr);
        cout << root -> inner << " " << root -> length << endl;
    }
    return 0;
}