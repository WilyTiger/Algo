#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

typedef long long ll;
ll dp[120][11];

const int MOD = 1e9;
const int dx[] = {1, 2, -1, 2, -2, 1, -1, -2};
const int dy[] = {2, 1, 2, -1, 1, -2, -2, -1};

map <int, pair<int, int>> mp1;
map <pair<int, int>, int> mp2;

bool check(int x, int y) {
    return (x == 3 && y == 1) || (x >= 0 && x < 3 && y >= 0 && y < 3);
}
int main() {
    int n;
    cin >> n;

    int num = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            mp1[num] = {i, j};
            mp2[{i, j}] = num;
            num++;
        }

    mp1[0] = {3, 1};
    mp2[{3, 1}] = 0;

    for (int i = 0; i <= 9; i++) {
        dp[1][i] = 1;
    }

    dp[1][8] = dp[1][0] = 0;

    for (int len = 2; len <= n; len++) {
        for (int last = 0; last < 10; last++) {
            for (int k = 0; k < 8; k++) {
                pair <int, int> cur = mp1[last];
                if (check(cur.first + dx[k], cur.second + dy[k])) {
                    dp[len][last] =
                            (dp[len][last]
                            + dp[len - 1][mp2[{cur.first + dx[k], cur.second + dy[k]}]]) % MOD;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 10; i++) {
        ans = (ans + dp[n][i]) % MOD;
    }
    cout << ans;
    return 0;
}