#pragma once
#include <string>
#include <vector>
#include <random>
#include "rng.hpp"

struct Node {
    std::string Name;
    int value = 0;

    void setRandomValue(int min = 0, int max = 100) {
        std::uniform_int_distribution<int> dist(min, max);
        value = dist(rng::get());
    }
};

// Global container
inline std::vector<Node> nodes;

// Helper to add a Node with a random value
inline void addRandomNode(const std::string& name = "", int min = 0, int max = 100) {
    Node n;
    n.Name = name;
    n.setRandomValue(min, max);
    nodes.push_back(std::move(n));
}
