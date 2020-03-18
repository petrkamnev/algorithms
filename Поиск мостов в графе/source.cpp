#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

void
dfs(int u, int parent, const vector<vector<int>> &g, vector<bool> &used, vector<int> &enter, vector<int> &f, int &time,
    vector<int> &res, map<pair<int, int>, int> &mp) {
    enter[u] = time++;
    f[u] = enter[u];
    used[u] = 1;
    for (auto v : g[u]) {
        if (v == parent) {
            continue;
        } else if (!used[v]) {
            dfs(v, u, g, used, enter, f, time, res, mp);
            f[u] = min(f[u], f[v]);
            if (f[v] > enter[u]) {
                res.push_back(mp[{min(u, v), max(u, v)}]);
            }
        } else {
            f[u] = min(f[u], enter[v]);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    map<pair<int, int>, int> mp;//соответствие ребра его номеру
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
        mp[{min(a, b), max(a, b)}] = i + 1;
    }
    vector<int> res; //все мосты
    vector<int> enter(n); //время входа
    int time = 0;
    vector<bool> used(n, 0);
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, i, g, used, enter, f, time, res, mp);
        }
    }
    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for (int i : res) {
        cout << i << ' ';
    }
}
