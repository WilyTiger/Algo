#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 1e5 + 5;

int deq[MAXN];
int num[MAXN];
int main() {
#ifndef DEBUG
    freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	cin.sync_with_stdio(0);
    cin.tie(0);
    cout.sync_with_stdio(0);
    cout.tie(0);

    int n;
    cin >> n;

    int head = 0;
    int tail = 0;
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        switch (type) {
            case 1: {
                int id;
                cin >> id;
                deq[tail] = id;
                num[id] = tail++;
                break;
            }
            case 2: {
                head++;
                break;
            }
            case 3: {
                tail--;
                break;
            }
            case 4: {
                int q;
                cin >> q;
                cout << num[q] - head << endl;
                break;
            }
            case 5: {
                cout << deq[head] << endl;
            }
        }
    }
    return 0;
}