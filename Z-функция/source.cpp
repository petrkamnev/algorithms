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

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s;
    if (cin >> s && s.size() > 0) {
        vector<int> z;
        z_func(s, z);
        z[0] = s.size();
        for (auto i : z) {
            cout << i << " ";
        }
        return 0;
    }
}
