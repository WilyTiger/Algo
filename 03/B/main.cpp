#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e3 + 5;

int a[MAXN][MAXN];
int dp[MAXN][MAXN];
char previous[MAXN][MAXN];

int n, m;
bool check(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}


void print() {
    for (int i = 0; i < n; i++) {
        for (int j=  0; j < m; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j=  0; j < m; j++) {
            cout << previous[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            dp[i][j] = -1e9;
        }
    }

    dp[0][0] = a[0][0];
    previous[0][0] = '^';

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (check(i - 1, j)) {
                if (dp[i][j] < dp[i - 1][j] + a[i][j]) {
                    dp[i][j] = dp[i - 1][j] + a[i][j];
                    previous[i][j] = 'D';
                }
            }
            if (check(i, j - 1)) {
                if (dp[i][j] < dp[i][j - 1] + a[i][j]) {
                    dp[i][j] = dp[i][j - 1] + a[i][j];
                    previous[i][j] = 'R';
                }
            }
        }
    }

    //print();

    string ans = "";
    int curx = n - 1;
    int cury = m - 1;
    while (curx != 0 || cury != 0) {
        ans += previous[curx][cury];
        if (previous[curx][cury] == 'R') {
            cury--;
        } else {
            curx--;
        }
    }

    reverse(ans.begin(), ans.end());
    cout << dp[n - 1][m - 1] << endl << ans;
    return 0;
}