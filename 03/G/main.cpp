#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 110;

string dp[MAXN][MAXN];

bool isGood(char x, char y) {
    return (x == '(' && y == ')') || (x == '[' && y == ']') || (x == '{' && y == '}');
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string s;
    cin >> s;

    int n = s.length();

    for (int i = 0; i <= n; i++) {
        dp[i][i + 1] = "";
    }


    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            dp[l][r] = dp[l + 1][r];
            if (dp[l][r].length() < dp[l][r - 1].length()) {
                dp[l][r] = dp[l][r - 1];
            }
            for (int k = l; k <= r; k++) {
                if (dp[l][r].length() < (dp[l][k] + dp[k][r]).length()) {
                    dp[l][r] = dp[l][k] + dp[k][r];
                }
            }
            if (isGood(s[l], s[r - 1])) {
                if (dp[l][r].length() < dp[l + 1][r - 1].length() + 2) {
                    dp[l][r] = s[l] + dp[l + 1][r - 1] + s[r - 1];
                }
            }
        }
    }

    cout << dp[0][n];
    return 0;
}