#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 1e3 + 5;
int dp[MAXN][MAXN];


int main() {
    string s, t;
    cin >> s >> t;

    s = '#' + s;
    t = '#' + t;

    int n = s.length();
    int m = t.length();

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 1e9;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0 && i == 0) {
                continue;
            }
            if (i - 1 >= 0 && j - 1 >= 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                if (s[i] != t[j]) {
                    dp[i][j]++;
                }
            }

            if (i - 1 >= 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            if (j - 1 >= 0)
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
        }
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j< m; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << dp[n - 1][m - 1];
    return 0;
}