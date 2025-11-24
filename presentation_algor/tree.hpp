#ifndef tree
#define tree
#include<iostream>
#include<queue>
#include<vector>
#include"node.hpp"

using namespace std;

template <typename T>
node<T>* tournament_tree(const vector<T>& items){
    queue<node<T>*> q;
    for(const T& item:items){
        node<T>* leaf = new node<T>();
        leaf->left = nullptr;
        leaf->right = nullptr;
        leaf->data = item;
        q.push(leaf);
    }

    while (q.size() >1)
    {
        node<T>* a = q.front(); q.pop();
        node<T>* b = q.front(); q.pop();

        node<T>* parent = new node<T>();
        parent->left = a;
        parent->right = b;
        q.push(parent);
    }
    
    return q.front();
}

template <typename T>
void print_tree(node<T>* root){
    if(root == nullptr) return;

    queue<node<T>*> q;
    q.push(root);

    while(!q.empty()){
        node<T>* current = q.front();
        q.pop();

        cout << current->data << " ";

        if(current->left != nullptr)
            q.push(current->left);
        if(current->right != nullptr)
            q.push(current->right);
    }
}

#endif