#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAXN = 19;

ll c[MAXN];

int main() {
    freopen("skyscraper.in", "r", stdin);
    freopen("skyscraper.out", "w", stdout);

    ll n, w;
    cin >> n >> w;

    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector <pair <ll, ll>> masks;
    for (int msk = 0; msk < (1 << n); msk++) {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (msk & (1 << i)) {
                sum += c[i];
            }
        }
        masks.push_back({sum, msk});
    }

    sort(masks.begin(), masks.end());
    reverse(masks.begin(), masks.end());
/*
    for (int i = 0; i < masks.size(); i++) {
        cout << masks[i].first << " " << masks[i].second << endl;
    }*/
    vector <ll> ans;
    ll msk = 0;
    int i = 0;
    while (msk != (1 << n) - 1) {
        if (masks[i].first <= w && !(msk & masks[i].second)) {
            ans.push_back(masks[i].second);
            msk |= masks[i].second;
        }
        i++;
    }

    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (ans[i] & (1 << j)) {
                cnt++;
            }
        }

        cout << cnt << " ";
        for (int j = 0; j < n; j++) {
            if (ans[i] & (1 << j)) {
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }

    return 0;
}