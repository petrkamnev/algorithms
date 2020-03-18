#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int start, vector<vector<int>> &g, vector<bool> &used, int &time, vector<int> &enter, vector<int> &f,
         vector<bool> &res) {
    enter[start] = time;
    used[start] = 1;
    f[start] = enter[start];
    int c = 0;
    for (auto i : g[start]) {
        if (!used[i]) {
            c++;
            time += 1;
            dfs(i, g, used, time, enter, f, res);
            f[start] = min(f[start], f[i]);
            if (enter[start] != 1 && f[i] >= enter[start]) {
                res[start] = 1;
            }
        } else {
            f[start] = min(f[start], enter[i]);
        }
    }
    if (enter[start] == 1 && c >= 2) {
        res[start] = 1;
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
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> f(n);
    vector<int> enter(n); //время входа
    vector<bool> used(n, 0);
    vector<bool> res(n, 0); //является ли вершина точкой сочленения
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            int time = 1;
            dfs(i, g, used, time, enter, f, res);
        }
    }
    int count = 0;
    for (auto i : res) {
        if (i) {
            count++;
        }
    }
    cout << count << endl;
    for (int i = 0; i < n; i++) {
        if (res[i]) {
            cout << i + 1 << " ";
        }
    }
}
