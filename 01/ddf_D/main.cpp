#include <iostream>

using namespace std;

const int MAXN = 2e5;
int sz = 0;
int heap[MAXN];

void insert(int x) {
    heap[sz++] = x;
    int i = sz - 1;
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(heap[(i - 1) / 2], heap[i]);
        i = (i - 1) / 2;
    }
}

int extract() {
    int res = heap[0];
    sz--;
    swap(heap[0], heap[sz]);
    int i = 0;
    while (2 * i + 1 < sz) {
        int j = 2 * i + 1;
        if (j + 1 < sz && heap[j + 1] > heap[j]) {
            j++;
        }
        if (heap[j] > heap[i]) {
            swap(heap[j], heap[i]);
            i = j;
        } else {
            break;
        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0;  i < n; i++) {
        int type;
        cin >> type;
        if (type == 0) {
            int x;
            cin >> x;
            insert(x);
        } else {
            cout << extract() << endl;
        }
    }
    return 0;
}