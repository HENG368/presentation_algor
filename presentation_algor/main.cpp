#include "condidate.hpp"
#include "tournament.hpp"
#include "rng.hpp"
#include <iostream>
#include <vector>

int main() {
    // Deterministic seed for reproducible runs (change or remove for randomness)
    rng::setSeed(12345);

    nodes.clear();
    addRandomNode("Alice", 1, 100);
    addRandomNode("Bob", 1, 100);
    addRandomNode("Carol", 1, 100);
    addRandomNode("Dave", 1, 100);
    addRandomNode("Eve", 1, 100);


    std::vector<Node> players = nodes; // copy local list

    // Run tournament with history so we can show champion's matches and scores
    auto result = tournament::runKnockoutWithHistory(players);
    const Node &champion = result.champion;

    // Print candidates and their scores
    std::cout << "Candidates:\n";
    for (const auto &p : players) {
        std::cout << p.Name << " (" << p.value << ")\n";
    }

    // Determine champion's final match score (look for last non-empty match)
    auto champMatches = tournament::championMatches(result);
    int finalChampionScore = champion.value;
    for (int i = (int)champMatches.size() - 1; i >= 0; --i) {
        const auto &m = champMatches[i];
        if (m.winner.Name.empty()) continue;
        if (m.a.Name == champion.Name) finalChampionScore = m.a.value;
        else finalChampionScore = m.b.value;
        break;
    }

    // Print only the champion (with final match score)
    std::cout << "\nChampion: " << champion.Name << " (" << finalChampionScore << ")\n";

    // Print champion's matches per round in the form: Round1: Alice(18) vs Bob(15)
    for (size_t r = 0; r < champMatches.size(); ++r) {
        const auto &m = champMatches[r];
        if (m.winner.Name.empty()) continue; // skip rounds without a match for champion
        std::cout << "Round " << (r+1) << ": ";
        std::cout << m.a.Name << "(" << m.a.value << ") vs " << m.b.Name << "(" << m.b.value << ")\n";
    }

    return 0;
}