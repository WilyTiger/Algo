#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2e5;

struct matrix {
    int a11;
    int a12;
    int a21;
    int a22;
};

matrix a[MAXN];
matrix t[4 * MAXN];
int r;
matrix ONE_MATRIX;

matrix multiply(matrix &a, matrix &b) {
    matrix res = {0, 0, 0, 0};
    res.a11 = ((a.a11 * b.a11) % r + (a.a12 * b.a21) % r) % r;
    res.a12 = ((a.a11 * b.a12) % r + (a.a12 * b.a22) % r) % r;
    res.a21 = ((a.a21 * b.a11) % r + (a.a22 * b.a21) % r) % r;
    res.a22 = ((a.a21 * b.a12) % r + (a.a22 * b.a22) % r) % r;
    return res;
}


void BuildTree(int v, int l, int r) {
    if (r - l == 1) {
        t[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    BuildTree(v * 2, l, m);
    BuildTree(v * 2 + 1, m, r);
    t[v] = multiply(t[v * 2], t[v * 2 + 1]);
}

matrix get_ans(int v, int l, int r, int ql, int qr) {
    if (qr <= l || ql >= r) {
        return ONE_MATRIX;
    }
    if (l >= ql && r <= qr) {
        return t[v];
    }
    int m = (l + r) / 2;
    matrix a, b;
    a = get_ans(v * 2, l, m, ql, qr);
    b = get_ans(v * 2 + 1, m, r, ql, qr);
    return multiply(a, b);
}

void init() {
    ONE_MATRIX.a11 = 1;
    ONE_MATRIX.a22 = 1;
}

void print(matrix a) {
    printf("%d %d \n%d %d\n\n", a.a11, a.a12, a.a21, a.a22);
}

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);


    int n, m;
    scanf("%d%d%d", &r, &n, &m);

    init();

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &a[i].a11, &a[i].a12, &a[i].a21, &a[i].a22);
    }

    BuildTree(1, 0, n);

    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        matrix res = get_ans(1, 0, n, l, r);
        print(res);
    }

    return 0;
}