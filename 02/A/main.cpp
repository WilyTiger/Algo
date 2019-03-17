#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

stack <pair <int, int> > st;

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.sync_with_stdio(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            if (st.empty()) {
                st.push({x, x});
            } else {
                st.push({x, min(x, st.top().second)});
            }
        }
        if (type == 2) {
            st.pop();
        }
        if (type == 3) {
            cout << st.top().second << endl;
        }
    }


    return 0;
}