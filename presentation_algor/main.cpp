#include <iostream>
#include "condidate.hpp"
#include "tournament.hpp"
#include "rng.hpp"

bool nodeWinner(Node a, Node b) {
    return a.value > b.value;
}

int main() {
    rng::setSeed(static_cast<uint32_t>(std::random_device{}()));

    // Add players and show their values
    addRandomNode("Alice");
    addRandomNode("Bob");
    addRandomNode("Charlie");
    addRandomNode("David");
    addRandomNode("Eve");

    std::cout << "Players and their values:\n";
    for (const auto& p : nodes) {
        std::cout << p.Name << " : " << p.value << "\n";
    }

    // Run tournament
    TreeNode<Node>* winnerTree = tournament_tree(nodes, nodeWinner);

    std::cout << "\nWinner: " 
              << winnerTree->data.Name 
              << " with value " 
              << winnerTree->data.value << "\n";

    return 0;
}
