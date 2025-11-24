#ifndef CONDIDATE_HPP
#define CONDIDATE_HPP

#include <string>
#include <random>
#include <vector>
#include "rng.hpp"

using namespace std;

struct Node {
    string Name;
    int value = 0;
    void setRandomValue(int min = 0, int max = 100) {
        std::uniform_int_distribution<int> dist(min, max);
        value = dist(rng::get());
    }
};
// Global container for nodes. Use `inline` to allow inclusion from multiple TUs.
inline std::vector<Node> nodes;

// Helper to add a Node with a random value
inline void addRandomNode(const std::string& name = "", int min = 0, int max = 100) {
    Node n;
    n.Name = name;
    n.setRandomValue(min, max);
    nodes.push_back(std::move(n));
}


#endif // CONDIDATE_HPP