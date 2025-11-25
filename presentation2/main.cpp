#include <iostream>
#include <vector>
#include "condidate.hpp"
#include "tree.hpp"
#include "rng.hpp"
#include <type_traits>
#include <cmath>
// Structure to store match results
struct Match {
    std::string p1;
    int v1;
    std::string p2;
    int v2;
    std::string winner;
};

std::vector<std::vector<Match>> rounds;  // rounds[0] = round 1, etc.

// Winner function + match recorder
Node fight(Node a, Node b) {
    Node winner = (a.value > b.value) ? a : b;

    // Save match into latest round
    if (!rounds.empty()) {
        rounds.back().push_back({a.Name, a.value, b.Name, b.value, winner.Name});
    }
    return winner;
}

// Build tournament and track rounds
Node runTournament(std::vector<Node> players) {
    while (players.size() > 1) {
        std::vector<Node> nextRound;
        rounds.push_back({});  // new round

        for (size_t i = 0; i < players.size(); i += 2) {
            if (i + 1 < players.size())
                nextRound.push_back(fight(players[i], players[i + 1]));
        }
        players = nextRound;
    }
    return players[0]; // final champion
}

int main() {
    rng::setSeed(static_cast<uint32_t>(std::random_device{}()));

    

    // Players
    addRandomNode("Alice");
    addRandomNode("Bob");
    addRandomNode("Charlie");
    addRandomNode("David");
    

    int size = nodes.size(); 
    double result = std::log2(size);

    if (result == std::floor(result)) {
        //print all condidates
        std::cout<<"This is our participation"<<"\n";
        for(Node n:nodes){
            std::cout<<n.Name<<"\n";
        }
        // Copy to local vector (tree nodes system stores globally)
        std::vector<Node> players = nodes;

        // Run tournament
        Node champion = runTournament(players);

        // Print results
        for (size_t r = 0; r < rounds.size(); r++) {
            std::cout << "Round " << r+1 << ":\n";
            for (auto &m : rounds[r]) {
                std::cout << "  " 
                        << m.p1 << "(" << m.v1 << ") vs "
                        << ","
                        << m.p2 << "(" << m.v2 << ") "<<"\n";
            }
            std::cout << "\n";
        }
        
        std::cout << "Final Winner: " << champion.Name 
                << " (" << champion.value << ")\n";

    }
    else{
        std::cout<<"you need more condidate";
    }
    return 0;
}
