#pragma once
#include <queue>
#include <vector>

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode* parent = nullptr;
};

// Build tournament tree
template <typename T>
TreeNode<T>* tournament_tree(const std::vector<T>& items, bool (*isWinner)(T, T)) {
    std::queue<TreeNode<T>*> q;

    // create leaf nodes
    for (const T& item : items) {
        TreeNode<T>* leaf = new TreeNode<T>();
        leaf->data = item;
        q.push(leaf);
    }

    // build tournament
    while (q.size() > 1) {
        TreeNode<T>* a = q.front(); q.pop();
        TreeNode<T>* parent;

        if (!q.empty()) {
            TreeNode<T>* b = q.front(); q.pop();
            parent = new TreeNode<T>();
            parent->left = a;
            parent->right = b;
            a->parent = parent;
            b->parent = parent;
            parent->data = isWinner(a->data, b->data) ? a->data : b->data;
        } else {
            parent = a; // odd player
        }

        q.push(parent);
    }

    //return q.front();
}