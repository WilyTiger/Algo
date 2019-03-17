#include <iostream>

using namespace std;
typedef long long ll;

int main() {
    ll w, h, n;
    cin >> w >> h >> n;

    ll l = 0, r = n * max(w, h) + 1;
    while (r - l > 1) {
        ll m = (l + r) / 2;
        if ((m / w) * (m / h) < n) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << r;
    return 0;
}