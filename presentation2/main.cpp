
#include <iostream>
#include "condidate.hpp"
#include "tree.hpp"
#include "rng.hpp"

// Custom winner function: highest value wins
bool nodeWinner(Node a, Node b) {
    return a.value > b.value;
}

// Optional: Print the tournament tree
void printTree(TreeNode<Node>* root, int level = 0) {
    if (!root) return;
    printTree(root->right, level + 1);
    for(int i = 0; i < level; i++) std::cout << "    ";
    std::cout << root->data.Name << "(" << root->data.value << ")\n";
    printTree(root->left, level + 1);
}

int main() {
    // Seed RNG
    rng::setSeed(static_cast<uint32_t>(std::random_device{}()));

    // Add players
    addRandomNode("Alice");
    addRandomNode("Bob");
    addRandomNode("Charlie");
    addRandomNode("David");
    addRandomNode("Eve");

    // Build tournament
    TreeNode<Node>* root = tournament_tree(nodes, nodeWinner);

    // Print winner
    std::cout << "Winner: " << root->data.Name 
              << " with value " << root->data.value << "\n\n";

    // Optional: print full tournament tree
    std::cout << "Tournament tree:\n";
    printTree(root);

    return 0;
}
