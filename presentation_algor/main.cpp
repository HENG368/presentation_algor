#include "condidate.hpp"
#include "tournament.hpp"
#include "rng.hpp"
#include <iostream>
#include <vector>

int main() {
    // Seed RNG with nondeterministic value so each competition is random
    rng::setSeed(static_cast<uint32_t>(std::random_device{}()));

    nodes.clear();
    addRandomNode("Alice", 1, 100);
    addRandomNode("Bob", 1, 100);
    addRandomNode("Carol", 1, 100);
    addRandomNode("Dave", 1, 100);
    addRandomNode("caroy", 1, 100);
    addRandomNode("Eve", 1, 100);
    addRandomNode("Frank", 1, 100);
    addRandomNode("Niko",1,100);
    std::vector<Node> players = nodes; // copy local list

    // If number of candidates is not a power of two, inform and exit
    auto isPowerOfTwo = [](size_t x){ return x && ((x & (x - 1)) == 0); };
    if (!isPowerOfTwo(players.size())) {
        // compute how many more candidates are needed to reach next power of two
        size_t target = 1;
        while (target < players.size()) target <<= 1;
        size_t need = target - players.size();
        std::cout << "need " << need << " more condidate " << std::endl;
        return 0;
    }

    // Preassign first-match scores for each candidate and clear usage flags
    std::uniform_int_distribution<int> dist(0, 100);
    for (const auto &p : players) {
        tournament::firstMatchScore[p.Name] = dist(rng::get());
        tournament::firstMatchUsed[p.Name] = false;
    }

    // Run tournament with history so we can show champion's matches and scores
    auto result = tournament::runKnockoutWithHistory(players);
    const Node &champion = result.champion;

    // Print candidates with their first-match score
    std::cout << "Candidates:\n";
    for (const auto &p : players) {
        int s = tournament::firstMatchScore[p.Name];
        std::cout << p.Name << "(" << s << ")\n";
    }

    // Determine champion's final match score (look for last non-empty match)
    auto champMatches = tournament::championMatches(result);
    int finalChampionScore = champion.value;
    for (int i = (int)champMatches.size() - 1; i >= 0; --i) {
        const auto &m = champMatches[i];
        if (m.winner.Name.empty()) continue;
        if (m.a.Name == champion.Name) finalChampionScore = m.scoreA;
        else finalChampionScore = m.scoreB;
        break;
    }

    // Print only the champion (with final match score)
    std::cout << "\nChampion: " << champion.Name << " (" << finalChampionScore << ")\n";

    // Print champion's matches per round in the form: Round1: Alice(18) vs Bob(15)
    for (size_t r = 0; r < champMatches.size(); ++r) {
        const auto &m = champMatches[r];
        if (m.winner.Name.empty()) continue; // skip rounds without a match for champion
        std::cout << "Round " << (r+1) << ": ";
        std::cout << m.a.Name << "(" << m.scoreA << ") vs " << m.b.Name << "(" << m.scoreB << ")\n";
    }

    return 0;
}