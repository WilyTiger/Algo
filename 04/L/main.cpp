#include <iostream>

using namespace std;

#define int long long
const int MAXN = 200;
int n;

int t[MAXN][MAXN][MAXN];
void upd(int x, int y, int z, int d) {
    for (int i = x; i < n; i = (i | (i + 1)))
        for (int j = y; j < n; j = (j | (j + 1)))
            for (int k = z; k < n; k = (k | (k + 1))) {
                t[i][j][k] += d;
            }
}

int get_sum(int x, int y, int z) {
    int result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
                result += t[i][j][k];
            }
    return result;
}

signed main() {
    cin >> n;

    while (true) {
        int type;
        cin >> type;
        if (type == 3)
            break;
        if (type == 1) {
            int x, y, z, k;
            cin >> x >> y >> z >> k;
            upd(x, y, z, k);
        }
        if (type == 2) {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << get_sum(x2, y2, z2) - get_sum(x1 - 1, y2, z2) - get_sum(x2, y1 - 1, z2) - get_sum(x2, y2, z1 - 1) + get_sum(x1 - 1, y1 - 1, z2) + get_sum(x1 - 1, y2, z1 - 1) + get_sum(x2, y1 - 1, z1 - 1) - get_sum(x1 - 1, y1 - 1, z1 - 1) << endl;
        }
    }
    return 0;
}