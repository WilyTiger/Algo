#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

typedef long long ll;

ll a[MAXN];
ll dp[MAXN];
int previous[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i < n - 1; i++) {
        cin >> a[i];
    }

    dp[0] = 0;
    previous[0] = -1;
    for (int i = 1; i < n; i++) {
        ll mx = dp[i - 1];
        int ind = i - 1;
        for (int j = 2; i - j >= 0 && j <= k; j++) {
            if (dp[i - j] > mx) {
                mx = dp[i - j];
                ind = i - j;
            }
        }
        dp[i] = dp[ind] + a[i];
        previous[i] = ind;
    }

    cout << dp[n - 1] << endl;

    vector <int> ans;
    int cur = n - 1;
    while (cur != -1) {
        ans.push_back(cur);
        cur = previous[cur];
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() - 1 << endl;

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}