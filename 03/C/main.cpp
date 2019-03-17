#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e4;

int a[MAXN];
int dp[MAXN];
int previous[MAXN];
int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = 1;
        previous[i] = -1;
    }

    int len = 1;
    int cur = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    previous[i] = j;
                }
            }
        }
        if (dp[i] > len) {
            len = dp[i];
            cur = i;
        }
    }

    vector <int> ans;
    cout << len << endl;
    while (len > 0) {
        ans.push_back(a[cur]);
        cur = previous[cur];
        len--;
    }

    reverse(ans.begin(), ans.end());

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    return 0;
}