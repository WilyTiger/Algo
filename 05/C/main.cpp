#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    node* l;
    node* r;
    node* p;
    int x;
    int y;
    int num;
    node(int x, int y, int num): x(x), y(y), num(num), l(nullptr), r(nullptr), p(nullptr) {};
    node(int x, int y, int num, node* l, node* r, node* p): x(x), y(y), num(num), l(l), r(r), p(p) {};
};

struct kek {
    int x;
    int y;
    int num;
};


const int MAXN = 3e5 + 50;

kek a[MAXN];

bool cmp(kek first, kek second) {
    return first.x < second.x;
}


struct state {
    int s;
    int f;
    int t;
};

state ans[MAXN];

void get_ans(node *&t, int prev) {
    if (t->l) {
        ans[t->num].s = t->l->num;
        get_ans(t->l, t->num);
    }
    ans[t->num].f = prev;
    if (t->r) {
        ans[t->num].t = t->r->num;
        get_ans(t->r, t->num);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].num = i + 1;
    }

    sort(a, a + n, cmp);

    node* last = new node(a[0].x, a[0].y, a[0].num);

    for (int i = 1; i < n; i++) {
        node* cur = last;
        if (last->y < a[i].y) {
            last->r = new node(a[i].x, a[i].y, a[i].num, nullptr, nullptr, last);
            last = last->r;
        } else {
            while (cur->y > a[i].y && cur->p) {
                cur = cur->p;
            }
            if (cur->y >= a[i].y) {
                last = new node(a[i].x, a[i].y, a[i].num, cur, nullptr, nullptr);
                cur->p = last;
            } else {
                last = new node(a[i].x, a[i].y, a[i].num, cur->r, nullptr, cur);
                cur->r = last;
                last->p = cur;
                last->l->p = last;
            }
        }
    }

    while (last->p) {
        last = last->p;
    }

    get_ans(last, 0);

    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        cout << ans[i].f << " " << ans[i].s << " " << ans[i].t << endl;
    }
}