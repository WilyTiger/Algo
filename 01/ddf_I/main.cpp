#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-6;

double f(double x) {
    return x * x + sqrt(x);
}
int main() {
    double c;
    cin >> c;

    double l = 0;
    double r = 1e7;

    while (r - l > EPS) {
        double m = (r + l) / 2;
        if(f(m) < c) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << fixed << setprecision(6) << r;
    return 0;
}