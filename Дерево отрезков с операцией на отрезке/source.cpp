#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

long long INF = 1e9;

void add(long long i, long long l, long long r, long long ql, long long qr, long long d, vector<long long> &tree) {
    if (qr <= l || ql >= r) {
        return;
    }
    if (l >= ql && r <= qr) {
        if (tree[i] != 0 && l + 1 != r) {
            tree[2 * i + 1] += tree[i];
            tree[2 * i + 2] += tree[i];
            tree[i] = 0;
        }
        tree[i] += d;
        return;
    }
    long long m = (l + r) / 2;
    add(2 * i + 1, l, m, ql, qr, d, tree);
    add(2 * i + 2, m, r, ql, qr, d, tree);
}

void query(long long i, long long l, long long r, long long q, long long sum, vector<long long> &tree) {
    if (q < l || q >= r) {
        return;
    }
    sum += tree[i];
    if (l + 1 == r) {
        cout << sum << "\n";
        return;
    }
    long long m = (l + r) / 2;
    query(2 * i + 1, l, m, q, sum, tree);
    query(2 * i + 2, m, r, q, sum, tree);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    long long n;
    cin >> n;
    long long n2 = 1;
    for (long long i = 0; i < 100; i++) {
        if (n2 >= n) {
            break;
        }
        n2 *= 2;
    }
    vector<long long> arr(n2, INF);
    for (long long i = 0; i < n; i++) {
        cin >> arr[i];
    }
    long long k;
    cin >> k;
    vector<long long> tree(2 * n2, 0);
    for (long long i = 0; i < n2; i++) {
        tree[2 * n2 - 2 - i] = arr[n2 - i - 1];
    }
    for (long long i = 0; i < k; i++) {
        char t;
        cin >> t;
        if (t == 'g') {
            long long q;
            cin >> q;
            query(0, 0, n2, q - 1, 0, tree);
        } else {
            long long l, r, d;
            cin >> l >> r >> d;
            if (r == n) {
                r = n2;
            }
            add(0, 0, n2, l - 1, r, d, tree);
        }
    }
}
