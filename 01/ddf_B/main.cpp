#include <iostream>
#include <cstdio>

using namespace std;
const int MAXN = 2e5 + 10;

int a[MAXN];
int cnt[MAXN];

void count_sort(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        cnt[arr[i]]++;
    }

    int j = 0;
    for (int i = 0; i <= 100; i++) {
        while (cnt[i] > 0) {
            arr[j++] = i;
            cnt[i]--;
        }
    }
}
int main() {
    int n = 0;
    while (cin >> a[n++]) {

    }
    n--;

    count_sort(a, n);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    return 0;
}