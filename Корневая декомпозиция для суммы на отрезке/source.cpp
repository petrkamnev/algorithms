#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <numeric>
#include <random>
#include <ctime>
#include <tuple>

using namespace std;
#define int long long
#define double long double
int MOD = 1e9 + 7;
double EPS = 1e-10;
mt19937 rnd(time(0));

int get_sum(int l, int r, int size, vector<int> &arr, vector<int> &blocks) {
    int ans = 0;
    while (r % size != 0 && r > l) {
        r--;
        ans += arr[r];
    }
    while (l % size != 0 && l < r) {
        ans += arr[l];
        l++;
    }
    while (l < r) {
        ans += blocks[l / size];
        l += size;
    }
    return ans;
}

signed main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    int size = (int) (sqrt(n + 1));
    vector<int> blocks(n / size + 1, 0);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        if (t == 'A') {
            a--;
            blocks[a / size] += -arr[a] + b;
            arr[a] = b;
        } else {
            a--;
            cout << get_sum(a, b, size, arr, blocks) << endl;
        }
    }
}
