#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <random>

using namespace std;

mt19937 RND;

int INF = 1e9;

struct Node {  //структура для декартова дерева на указателях
    int x, y;
    Node *left, *right;

    Node(int a) {
        x = a;
        y = RND();
        left = nullptr;
        right = nullptr;
    }

    Node() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }
};

bool find(Node *root, int key) { //проверка, есть ли элемент key в декартаче
    if (!root) return false;
    if (root->x == key) {
        return true;
    } else if (root->x > key) {
        return find(root->left, key);
    } else {
        return find(root->right, key);
    }
}

pair<Node *, Node *> split(Node *root, int key) {  //разделяет дерево на два поддерева, барьер key
    if (!root) {
        return {nullptr, nullptr};
    }
    if (root->x <= key) {
        auto [root1, root2] = split(root->right, key);
        root->right = root1;
        return {root, root2};
    } else {
        auto [root1, root2] = split(root->left, key);
        root->left = root2;
        return {root1, root};
    }
}

Node *merge(Node *root1, Node *root2) { //слияние двух деревьев в правильном порядке
    if (!root1) {
        return root2;
    }
    if (!root2) {
        return root1;
    }
    if (root1->y > root2->y) {
        root1->right = merge(root1->right, root2);
        return root1;
    } else {
        root2->left = merge(root1, root2->left);
        return root2;
    }
}

Node *insert(Node *root, int a) { //добавление элемента в дерево
    if (find(root, a)) {
        return root;
    }
    auto pr = split(root, a);
    auto root1 = pr.first;
    auto root3 = pr.second;
    Node *root2 = new Node(a);
    return merge(merge(root1, root2), root3);
}

Node *erase(Node *root, int key) { //удаление элемента из дерева
    auto t = split(root, key);
    auto root12 = t.first;
    auto root3 = t.second;
    auto t2 = split(root12, key - 1);
    auto root1 = t2.first;
    auto root2 = t2.second;
    return merge(root1, root3);
}

int next(Node *root, int key) { //минимальный элемент, строго больший key
    if (!root) {
        return INF;
    }
    int a = INF, b = INF, c = INF;
    if (root->x > key) {
        c = root->x;
    }
    if (root->x > key) {
        b = next(root->left, key);
    }
    if (b == INF && c == INF) {
        a = next(root->right, key);
    }
    return min(min(a, b), c);
}

int prev(Node *root, int key) { //максимальный элемент, строго меньший key
    if (!root) {
        return -INF;
    }
    int a = -INF, b = -INF, c = -INF;
    if (root->x < key) {
        c = root->x;
    }
    if (root->x < key) {
        a = prev(root->right, key);
    }
    if (a == -INF && c == -INF) {
        b = prev(root->left, key);
    }
    return max(max(a, b), c);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    srand(time(0));
    Node *root = nullptr;
    string t;
    while (cin >> t) {
        int k;
        cin >> k;
        if (t == "insert") {
            root = insert(root, k);
        } else if (t == "exists") {
            if (find(root, k)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        } else if (t == "next") {
            int tmp = next(root, k);
            if (tmp == INF) {
                cout << "none" << endl;
            } else {
                cout << tmp << endl;
            }
        } else if (t == "prev") {
            int tmp = prev(root, k);
            if (tmp == -INF) {
                cout << "none" << endl;
            } else {
                cout << tmp << endl;
            }
        } else {
            root = erase(root, k);
        }
    }
}
