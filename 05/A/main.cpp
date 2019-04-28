#include <iostream>
#include <cstdio>

using namespace std;

struct node {
    node* left;
    node* right;
    int key;
    node() {
        left = nullptr;
        right = nullptr;
        key = 0;
    }

    explicit node(int key) {
        left = nullptr;
        right = nullptr;
        this->key = key;
    }
};

void insert(node *&v, int x) {
    if (!v) {
        v = new node(x);
        return;
    }
    if (v->key == x) {
        return;
    }
    if (v -> key > x) {
        insert(v->left, x);
    } else {
        insert(v->right, x);
    }
}

void print(node* v) {
    if (!v) {
        return;
    }
    if (v->left) {
        print(v->left);
    }
    cout << v->key << " ";
    if (v->right) {
        print(v->right);
    }
}


bool exists(node*& v, int x) {
    if (!v) {
        return false;
    }
    if (v->key == x) {
        return true;
    }
    if (x < v->key) {
        return exists(v->left, x);
    } else {
        return exists(v->right, x);
    }
}

node* minimum(node*& v) {
    if (!v->left) {
        return v;
    }
    return minimum(v->left);
}

node* maximum(node*& v) {
    if (!v->right) {
        return v;
    }
    return minimum(v->right);
}

void remove(node*& v, int x) {
    if (!v) {
        return;
    }
    if (v->key > x) {
        remove(v->left, x);
    }
    if (v->key < x) {
        remove(v->right, x);
    }
    if (v->key == x) {
        if (!v->left && !v->right) {
            v = nullptr;
            return;
        }
        if (!v->left) {
            v = v->right;
            return;
        }
        if (!v->right) {
            v = v->left;
            return;
        }
        node* kek = minimum(v->right);
        v->key = kek->key;
        remove(v->right, kek->key);
    }
}

node* next(node *&v, int x) {
    node* current = v;
    node* ans = nullptr;
    while (current) {
        if (x < current->key) {
            ans = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return ans;
}
node* prev(node *&v, int x) {
    node* current = v;
    node* ans = nullptr;
    while (current) {
        if (x <= current->key) {
            current = current->left;
        } else {
            ans = current;
            current = current->right;
        }
    }
    return ans;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    string s;
    int x;
    node* root = nullptr;
    while (cin >> s >> x) {
        if (s == "insert") {
            insert(root, x);
        }
        if (s == "exists") {
            if (exists(root, x))
                cout << "true" << endl;
            else {
                cout << "false" << endl;
            }
        }
        if (s == "delete") {
            remove(root, x);
        }
        if (s == "next") {
            node* ans = next(root, x);
            if (!ans) {
                cout << "none" << endl;
            } else {
                cout << ans->key << endl;
            }
        }
        if (s == "prev") {
            node* ans = prev(root, x);
            if (!ans) {
                cout << "none" << endl;
            } else {
                cout << ans->key << endl;
            }
        }
    }

    //print(root);

    return 0;
}