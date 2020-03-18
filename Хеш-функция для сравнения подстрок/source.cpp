#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

long long M = 1e9 + 7;
long long B = 31;

long long get_hash(int l, int r, const vector<long long> &pref, vector<long long> &pw) {
    return ((pref[r] - (pref[l] * pw[r - l]) % M) + M) % M;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    vector<long long> pref(s.size() + 1, 0);
    for (int i = 1; i <= s.size(); i++) {
        pref[i] = (pref[i - 1] * B + s[i - 1]) % M;
    }
    int n;
    cin >> n;
    vector<long long> pw(s.size() + 2, 1);
    for (int i = 1; i <= s.size(); i++) {
        pw[i] = (pw[i - 1] * B) % M;
    }
    for (int i = 0; i < n; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (get_hash(l1 - 1, r1, pref, pw) == get_hash(l2 - 1, r2, pref, pw)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
