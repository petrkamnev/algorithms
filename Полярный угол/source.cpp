#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double PI = atan2(0, -1);

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
    double a, b;
    cin >> a >> b;
    cout.precision(30);
    double t = atan2(b, a);
    if (t < 0) {
        t += 2 * PI;
    }
    cout << t;
}
