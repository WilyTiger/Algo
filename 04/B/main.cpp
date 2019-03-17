#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
ll a[MAXN];
ll t[MAXN];
int n;

void upd(int x, ll y) {
    for (int i = x; i < n; i = (i | (i + 1))) {
        t[i] += y;
    }
}

ll get_sum(int x) {
    ll result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        result += t[i];
    }
    return result;
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        upd(i, a[i]);
    }

    string s;
    ll x, y;
    while (cin >> s >> x >> y) {
        if (s == "sum") {
            x--;
            y--;
            cout << get_sum(y) - get_sum(x - 1) << endl;
        } else {
            x--;
            upd(x, y - a[x]);
            a[x] = y;
        }
    }

    return 0;
}