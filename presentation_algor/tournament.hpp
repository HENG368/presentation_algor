#pragma once

#include "condidate.hpp"
#include <algorithm>
#include <random>
#include <iostream>

// Simple single-elimination knockout tournament utilities.
// - Works with `Node` (Name + value).
// - Plays matches by comparing `value`; higher wins. If equal, random tie-breaker.

namespace tournament {

// Play a match between two players and return the winner (by value).
inline Node playMatch(const Node &a, const Node &b) {
    if (a.value > b.value) return a;
    if (b.value > a.value) return b;
    // tie -> random winner
    static thread_local std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> d(0, 1);
    return d(gen) ? a : b;
}

// Run a single-elimination tournament on a vector of Nodes.
// If the number of players is not a power of two, byes are given randomly.
inline Node runKnockout(std::vector<Node> players) {
    if (players.empty()) throw std::runtime_error("No players provided");

    static thread_local std::mt19937 gen{std::random_device{}()};

    // Shuffle players first for randomness
    std::shuffle(players.begin(), players.end(), gen);

    while (players.size() > 1) {
        std::vector<Node> nextRound;
        // If odd number, give a bye to last player
        size_t i = 0;
        for (; i + 1 < players.size(); i += 2) {
            Node winner = playMatch(players[i], players[i+1]);
            nextRound.push_back(winner);
        }
        if (i < players.size()) {
            // bye
            nextRound.push_back(players[i]);
        }
        players.swap(nextRound);
    }

    return players.front();
}

} // namespace tournament
