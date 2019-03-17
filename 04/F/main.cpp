#include <iostream>

using namespace std;

const int MAXN = 1e5;
const int P = 30;

int st[MAXN][P];
int a[MAXN];
int log[MAXN];

void BuildSparse(const int* a, int n) {
    log[1] = 0;
    for (int i = 2; i < n; i++) {
        log[i] = log[i / 2] + 1;
    }

    for (int i = 0; i < n; i++) {
        st[i][0] = a[i];
    }

    for (int j = 1; j < P; j++) {
        for (int l = 0; l + (1 << j) <= n; l++) {
            st[l][j] = min(st[l][j - 1], st[l + (1 << (j - 1))][j - 1]);
        }
    }
}
int get_min(int ql, int qr) {
    ql--;
    qr--;
    if (ql > qr) {
        swap(ql, qr);
    }
    int k = log[qr - ql + 1];
    return min(st[ql][k], st[qr - (1 << k) + 1][k]);
}
int main() {
    int n, m;
    cin >> n >> m >> a[0];

    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }

    BuildSparse(a, n);

    int u, v;
    cin >> u >> v;
    int ans = get_min(u, v);
    //cout << ans << endl;
    for (int i = 2; i <= m; i++) {
        int un = ((17 * u + 751 + ans + 2 * (i - 1)) % n) + 1;
        int vn = ((13 * v + 593 + ans + 5 * (i - 1)) % n) + 1;
        u = un;
        v = vn;
        ans = get_min(u, v);
        int ans1 = 1e10;
        for (int i = min(u, v) - 1; i < max(u, v); i++) {
            ans1 = min(ans1, a[i]);
        }
    }
    cout << u << " " << v << " " << ans << endl;

    return 0;
}