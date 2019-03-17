#include <iostream>

using namespace std;

#define int long long

const int MAXN = 14;

char board[MAXN][MAXN];
int dp[1 << MAXN][MAXN];

int n;
bool check(int msk1, int msk2, int j) {
    if (msk1 & msk2)
        return 0;
    int msk = msk1 | msk2;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if ((msk & (1 << i)) && board[i][j] == 'X') {
            return 0;
        }
        if (msk2 & (1 << i) && board[i][j + 1] == 'X') {
            return 0;
        }
        if (!(msk & (1 << i)) && board[i][j] != 'X')  {
            cnt++;
        } else {

            if (cnt % 2 != 0) {
                return 0;
            }
            cnt = 0;
        }
    }
    if (cnt % 2)
        return 0;
    return 1;
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            board[i][j] = s[j];
        }
    }

    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int msk1 = 0; msk1 < (1 << n); msk1++) {
            for (int msk2 = 0; msk2 < (1 << n); msk2++) {
                if (check(msk1, msk2, i)) {
                    /*if (msk2 == 0 && i + 1 == m) {
                        cout << msk1 << " " << msk2 << endl;
                    }*/
                    dp[msk2][i + 1] += dp[msk1][i];
                }
            }
        }
    }

    cout << dp[0][m];
    return 0;
}