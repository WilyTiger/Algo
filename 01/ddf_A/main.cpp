#include <iostream>

using namespace std;
const int MAXN = 1e5 + 10;

int a[MAXN];

void merge(int arr[], int l, int m, int r) {
    int res[MAXN];
    int ind1, ind2;
    ind1 = ind2 = 0;
    while (l + ind1 < m && m + ind2 < r) {
        if (arr[l + ind1] <= arr[m + ind2]) {
            res[ind1 + ind2] = arr[l + ind1];
            ind1++;
        } else {
            res[ind1 + ind2] = arr[m + ind2];
            ind2++;
        }
    }
    while (l + ind1 < m) {
        res[ind1 + ind2] = arr[l + ind1];
        ind1++;
    }
    while (m + ind2 < r) {
        res[ind1 + ind2] = arr[m + ind2];
        ind2++;
    }

    for (int i = 0; i < ind1 + ind2; i++) {
        arr[l + i] = res[i];
    }
}

void merge_sort(int arr[], int l, int r) {
    if (r - l <= 1)
        return;
    int m = (l + r) / 2;
    merge_sort(arr, l, m);
    merge_sort(arr, m, r);
    merge(arr, l, m, r);
}

int main() {
    int n;
    cin >> n;

    for (int i = 0 ; i < n; i++) {
        cin >> a[i];
    }

    merge_sort(a, 0, n);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    return 0;
}