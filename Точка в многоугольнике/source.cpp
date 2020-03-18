#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double PI = atan2(0, -1);
double EPS = 1e-9;

struct Point {
    double x, y;

    Point(double a, double b) {
        x = a;
        y = b;
    }

    Point() {
        x = 0;
        y = 0;
    }
};

istream &operator>>(istream &cin, Point &p) {
    double x, y;
    cin >> x >> y;
    p = Point(x, y);
    return cin;
}

bool eqls_p(Point a, Point b) {
    return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}


double dot_prod(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross_prod(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool c_p(Point a, Point b, Point c) {
    double ax = b.x - a.x, ay = b.y - a.y, bx = c.x - a.x, by = c.y - a.y;
    return ax * by - ay * bx == 0;
}

bool between(Point a, Point b, Point c) {
    Point vec1, vec2;
    vec1.x = a.x - b.x;
    vec1.y = a.y - b.y;
    vec2.x = a.x - c.x;
    vec2.y = a.y - c.y;
    return dot_prod(vec1, vec2) < 0;
}

Point get_vec(Point a, Point b) {
    return Point(b.x - a.x, b.y - a.y);
}

double ang(Point a, Point b) {
    return atan2(cross_prod(a, b), dot_prod(a, b));
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    Point a;
    cin >> a;
    vector<Point> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    arr.push_back(arr[0]);
    for (int i = 1; i < arr.size(); i++) {
        if (eqls_p(a, arr[i - 1]) || eqls_p(a, arr[i]) ||
            (c_p(a, arr[i - 1], arr[i]) && between(a, arr[i - 1], arr[i]))) {
            cout << "YES";
            return 0;
        }
    }
    double alph = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        Point vec1 = get_vec(a, arr[i]), vec2 = get_vec(a, arr[i + 1]);
        alph += ang(vec1, vec2);
    }
    alph = abs(alph);
    if (abs(alph - 0) < EPS) {
        cout << "NO";
        return 0;
    }
    cout << "YES";
}
