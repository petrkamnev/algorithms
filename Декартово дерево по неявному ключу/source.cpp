#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

mt19937 RND;

struct Node {
    int y;
    Node *left, *right;
    int data, size;

    Node(int val) {
        data = val;
        size = 1;
        y = rand();
        left = nullptr;
        right = nullptr;
    }
};

int get_size(Node *root) {
    if (root) return root->size;
    else return 0;
}

void update(Node *&root) {
    if (!root) return;
    root->size = 1 + get_size(root->left) + get_size(root->right);
}

pair<Node *, Node *> split(Node *root, int k) {
    if (!root) {
        return {nullptr, nullptr};
    }
    int s1 = get_size(root->left);
    int s2 = get_size(root->right);
    if (s1 >= k) {
        auto[root1, root2] = split(root->left, k);
        root->left = root2;
        update(root);
        return {root1, root};
    } else {
        auto[root1, root2] = split(root->right, k - s1 - 1);
        root->right = root1;
        update(root);
        return {root, root2};
    }
}

Node *merge(Node *root1, Node *root2) {
    if (!root1) {
        return root2;
    }
    if (!root2) {
        return root1;
    }
    if (root1->y > root2->y) {
        root1->right = merge(root1->right, root2);
        update(root1);
        return root1;
    } else {
        root2->left = merge(root1, root2->left);
        update(root2);
        return root2;
    }
}

Node *insert(Node *root, int val) {
    Node *root2 = new Node(val);
    return merge(root, root2);
}

int get_elem(Node *root, int k) {
    if (!root) return 0;
    int s1 = get_size(root->left);
    if (k == s1) {
        return root->data;
    } else if (k < s1) {
        return get_elem(root->left, k);
    } else {
        return get_elem(root->right, k - 1 - s1);
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    srand(time(0));
    int n, m;
    cin >> n >> m;
    Node *root = nullptr;
    for (int i = 1; i <= n; i++) {
        root = insert(root, i);
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        auto[root12, root3] = split(root, r);
        auto[root1, root2] = split(root12, l - 1);
        root = merge(root2, merge(root1, root3));
    }
    for (int i = 0; i < n; i++) {
        cout << get_elem(root, i) << " ";
    }
}
