#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5 + 10;
typedef long long ll;

int a[MAXN];
ll ans = 0;

void merge(int l, int m, int r) {
    int ind1 = l, ind2 = m;
    vector <int> vec;
    while (ind1 < m && ind2 < r) {
        if (a[ind1] <= a[ind2]) {
            vec.push_back(a[ind1]);
            ind1++;
        } else {
            ans += m - ind1;
            vec.push_back(a[ind2]);
            ind2++;
        }
    }
    while (ind1 < m) {
        vec.push_back(a[ind1]);
        ind1++;
    }
    while (ind2 < r) {
        vec.push_back(a[ind2]);
        ind2++;
    }

    for (int i = 0; i < vec.size(); i++) {
        a[i + l] = vec[i];
    }
}

void merge_sort(int l, int r) {
    if (r - l <= 1)
        return;
    int m = (l + r) / 2;
    merge_sort(l, m);
    merge_sort(m, r);
    merge(l, m, r);
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    for (int i = 0 ; i < n; i++) {
        cin >> a[i];
    }

    merge_sort(0, n);

    cout << ans;

    return 0;
}