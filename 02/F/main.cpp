#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

const int MAXN = 1e5;

int a[MAXN];
int b[MAXN];
stack <int> st;
vector <string> ans;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(a, a + n);

    int ind = 0;
    for (int i = 0; i < n; i++) {
        ans.push_back("push");
        st.push(b[i]);
        while (!st.empty() && st.top() == a[ind]) {
            ind++;
            st.pop();
            ans.push_back("pop");
        }
    }

    if (!st.empty()) {
        cout << "impossible";
    } else {
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}