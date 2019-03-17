#include <iostream>
#include <cstdio>

using namespace std;

struct node {
    node* left;
    node* right;
    int key;

    node(int x) {
        right = left = nullptr;
        key = x;
    }
};

node* head = nullptr;
node* tail = nullptr;
node* mid = nullptr;
int cnt = 0;

int del_head() {
    cnt--;
    int x = head -> key;
    head = head -> right;
    if (cnt == 1) {
        head -> left = nullptr;
        mid = head;
        tail = nullptr;
    } else
    if (cnt == 0) {
        mid = tail = head = nullptr;
    } else {
        if (cnt % 2) {
            mid = mid -> right;
        }
    }

    return x;
}

void insert_tail(int x) {
    cnt++;
    node* a = new node(x);
    if (cnt == 1) {
        mid = head = a;
        return;
    }
    if (cnt == 2) {
        head -> right = a;
        tail = a;
        tail -> left = head;
        return;
    }
    tail -> right = a;
    tail = a;
    if (cnt % 2) {
        mid = mid -> right;
    }
}

void insert_mid(int x) {
    cnt++;
    node* a = new node(x);
    if (cnt == 1) {
        mid = head = a;
        return;
    }
    if (cnt == 2) {
        head -> right = a;
        tail = a;
        tail -> left = head;
        return;
    }
    a -> right = mid -> right;
    a -> left = mid;
    mid -> right -> left = a;
    mid -> right = a;
    if (cnt % 2) {
        mid = a;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        if (ch == '-') {
            cout << del_head() << endl;
        } else {
            int x;
            cin >> x;
            if (ch == '+') {
                insert_tail(x);
            }
            if (ch == '*') {
                insert_mid(x);
            }
        }
    }
    return 0;
}