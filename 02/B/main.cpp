#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

const int MAXN = 1e5 + 10;

int a[MAXN];
int b[MAXN];
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    int prev = -1;

    int ans = 0;

    int sz = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (x == prev)
            ans++;
        else {
            if (a[sz - 1] == x) {
                if (b[sz - 1] + 1 == 3) {
                    prev = x;
                    ans += 3;
                    sz--;
                } else {
                    b[sz - 1]++;
                    prev = -1;
                }
            } else {
                a[sz] = x;
                b[sz++] = 1;
                prev = -1;
            }
        }
    }

    cout << ans;
    return 0;
}