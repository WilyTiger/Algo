#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1e7;
unsigned int old_dp[MAXN], new_dp[MAXN];
int n;

void ini()
{
    for (int msk1 = 0; msk1 < (1 << (n + 1)); msk1++)
    {
        old_dp[msk1] = new_dp[msk1];
        new_dp[msk1] = 0;
    }
}
int main() {
    freopen("nice.in", "r", stdin);
    freopen("nice.out", "w", stdout);
    int m;
    cin >> n >> m;
    if (m < n)
        swap(n, m);

    for (int msk = 0; msk < (1 << (n + 1)); msk++) {
        if ((msk & 1) == 0)
            old_dp[msk] = 1;
    }



    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int msk = 0; msk < (1 << (n + 1)); msk++) {
                int c = msk & 1;
                if ((((msk >> 1) & 1) != c) || (((msk >> n) & 1) != c) || (j == 0)) {
                    int msk2 = (msk >> 1) | (c << n);
                    new_dp[msk2] += old_dp[msk];
                }
                int msk3 = (msk >> 1) | (((1 - c) << n));
                new_dp[msk3] += old_dp[msk];
            }
            ini();
        }
    }

    int ans = 0;
    for (int msk = 0; msk < (1 << (n + 1)); msk++) {
        ans += old_dp[msk];
    }

    cout << ans;

    return 0;
}
