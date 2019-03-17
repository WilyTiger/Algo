#include <iostream>

using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;

    int l = 0;
    int r = (n - 1) * max(x, y);

    while (r - l > 1) {
        int m = (l + r) / 2;
        if (m / x + m / y < n - 1) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << r + min(x, y);
    return 0;
}