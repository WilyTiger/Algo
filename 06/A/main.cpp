#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXP = 30;

int p[MAXN];
int dp[MAXN][MAXP];
int n;
int d[MAXN];
vector<int> tree[MAXN];

void dfs(int u, int p, int cnt) {
    d[u] = cnt;
    for (auto v : tree[u]) {
        dfs(v, u, cnt + 1);
    }
}
void pre_calc(int root) {
    dfs(root, -1, 0);
    for (int i = 0; i < n; i++) {
        dp[i][0] = p[i];
    }

    for (int k = 1; k < MAXP; k++) {
        for (int i = 0; i < n; i++) {
            if (dp[i][k - 1] == -1) {
                dp[i][k] = -1;
            } else {
                dp[i][k] = dp[dp[i][k - 1]][k - 1];
            }
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n;

    int root = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        if (p[i] == 0) {
            p[i] = -1;
            root = i;
        } else {
            p[i]--;
            tree[p[i]].push_back(i);
        }
    }

    pre_calc(root);

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";

        for (int j = 0; j < MAXP; j++) {
            if (i == root)
                break;
            if (dp[i][j] == -1)
                break;
            cout << dp[i][j] + 1 << " ";

        }
        cout << endl;
    }
    return 0;
}