#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

const int MAXN = 1e5 + 5;

int st[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string s;
    int sz = 0;

    while (cin >> s) {
        if (s == "+") {
            int res = st[sz - 2] + st[sz - 1];
            sz -= 2;
            st[sz++] = res;
        } else if (s == "-") {
            int res = st[sz - 2] - st[sz - 1];
            sz -= 2;
            st[sz++] = res;
        } else if (s == "*") {
            int res = st[sz - 2] * st[sz - 1];
            sz -= 2;
            st[sz++] = res;
        } else {
            int num = stoi(s);
            st[sz++] = num;
        }
    }

    cout << st[sz - 1];
    return 0;
}