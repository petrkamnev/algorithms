#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

void z_func(string &s, vector<int> &z) {
    int n = s.size();
    z.resize(n, 0);
    z[0] = 0;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - l], r - i));
        while (s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
}

void pr_func(string &s, vector<int> &p) {
    int n = s.size();
    p.resize(n);
    p[0] = 0;
    for (int i = 1; i < n; i++) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s;
    if (cin >> s && s.size() > 0) {
        vector<int> p;
        pr_func(s, p);
        for (auto i : p) {
            cout << i << " ";
        }
        return 0;
    }
}
