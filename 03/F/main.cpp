#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 120;
const int INF = 1e9;
const pair <int, int> NO = {-1, -1};

int cost[MAXN];
int dp[MAXN][MAXN];
pair <int, int> previous[MAXN][MAXN];

bool operator ==(const pair <int, int> &op1, const pair <int, int> &op2) {
    return ((op1.first == op2.first && op1.second == op2.second));
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    for (int i = 0; i <= n + 2; i++) {
        for (int j = 0; j <= n + 2; j++) {
            dp[i][j] = INF;
        }
    }

    dp[0][0] = 0;
    previous[0][0] = NO;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = dp[i - 1][j + 1];
            previous[i][j] = {i - 1, j + 1};
            if (cost[i] > 100) {
                if (j > 0)
                    if (dp[i][j] > dp[i - 1][j - 1] + cost[i]) {
                        previous[i][j] = {i - 1, j - 1};
                        dp[i][j] = dp[i - 1][j - 1] + cost[i];
                    }
            } else {
                if (dp[i][j] > dp[i - 1][j] + cost[i]) {
                    previous[i][j] = {i - 1, j};
                    dp[i][j] = dp[i - 1][j] + cost[i];
                }
            }
        }
    }


    int cnt = INF;
    int k1 = -1e9;
    for (int i = 0; i <= n; i++) {
        if (cnt > dp[n][i]) {
            k1 = i;
            cnt = dp[n][i];
        } else {
            if (cnt == dp[n][i]) {
                k1 = max(k1, i);
            }
        }
    }

    cout << cnt << endl;
    cout << k1 << " ";

    pair <int, int> cur = {n, k1};
    vector <int> ans;
    while (!(cur == NO)) {
        pair <int, int> pred = previous[cur.first][cur.second];
        if (pred == NO) {
            break;
        }
        if (cur.first - pred.first == 1 && cur.second - pred.second == -1) {
            ans.push_back(cur.first);
        }
        cur = pred;
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}