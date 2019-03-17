#include <iostream>
#include <cstdio>


using namespace std;

typedef long long ll;
const int MAXN = 1e7 + 10;
const int MOD1 = 1 << 16;
const int MOD2 = 1 << 30;

int a[MAXN];
ll pref[MAXN];

ll get_sum(int ql, int qr) {
    return pref[qr] - ((ql == 0) ? 0 : pref[ql - 1]);
}

int main() {
    int n, x, y;
    cin >> n >> x >> y >> a[0];

    pref[0] = a[0];
    for (int i = 1; i < n; i++) {
        a[i] = (x  * a[i - 1] + y) % MOD1;
        pref[i] = pref[i - 1] + a[i];
    }


    int m, z, t, prev;
    cin >> m >> z >> t >> prev;
    ll ans = 0;
    for (int i = 1; i < 2 * m; i++) {
        int next = ((1ll * z * prev) % MOD2 + t + MOD2) % MOD2;
        if (i % 2) {
            int ql = min(prev % n, next % n);
            int qr = max(next % n, prev % n);
            //cout << ql << " " << qr << endl;
            ans += get_sum(ql, qr);
        }
        prev = next;
    }

    cout << ans;
    return 0;
}