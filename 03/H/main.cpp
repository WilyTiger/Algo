#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAXN = 15;
ll dist[MAXN][MAXN];
ll dp[1 << MAXN][MAXN];
int previous[1 << MAXN][MAXN];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;


    for (int msk = 0; msk < (1 << n); msk++) {
        for (int i=  0; i < n; i++) {
            dp[msk][i] = 1e9;
        }
    }
    for (int i = 0; i <n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
        previous[1 << i][i] = -1;
    }

    for (int msk = 0; msk < (1 << n); msk++) {
        for (int v = 0; v < n; v++) {
            if ((1 << v) & msk) {
                continue;
            }
            for (int u = 0; u < n; u++) {
                if (!((1 << u) & msk)) {
                    continue;
                }
                if (dp[msk][u] + dist[v][u] < dp[msk | (1 << v)][v]) {
                    dp[msk | (1 << v)][v] =dp[msk][u] + dist[v][u];
                    previous[msk | (1 << v)][v] = u;
                }
            }
        }
    }

    ll len = 1e9;
    int cur = -1;
    for (int i = 0; i < n; i++) {
        if (len > dp[(1 << n) - 1][i]) {
            len = dp[(1 << n) - 1][i];
            cur = i;
        }
    }

    cout << len << endl;
    vector <int> ans;
    int curmsk = (1 << n) - 1;
    while (cur != -1) {
        ans.push_back(cur);
        int ncur = previous[curmsk][cur];
        curmsk ^= (1 << cur);
        cur = ncur;
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0 ; i < ans.size(); i++) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}