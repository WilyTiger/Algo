#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-7;

double vp, vf;
double a;

double len(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
double f(double x) {
    return len(x, a, 0, 1) / vp + len(x, a, 1, 0) / vf;
}
int main() {
    cin >> vp >> vf;

    cin >> a;

    double l = 0;
    double r = 1;

    while (r - l > EPS) {
        double m1 = (l * 2 + r) / 3;
        double m2 = (l + r * 2) / 3;
        if (f(m1) < f(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }

    cout << fixed << setprecision(7) << r;
    return 0;
}