#pragma once

#include "condidate.hpp"
#include "rng.hpp"
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
    std::uniform_int_distribution<int> d(0, 1);
    return d(rng::get()) ? a : b;
}

// Run a single-elimination tournament on a vector of Nodes.
// If the number of players is not a power of two, byes are given randomly.
inline Node runKnockout(std::vector<Node> players) {
    if (players.empty()) throw std::runtime_error("No players provided");

    // Shuffle players first for randomness
    std::shuffle(players.begin(), players.end(), rng::get());

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

// Match record for history
struct Match {
    Node a;
    // b may be empty (bye) - use Name=="" to indicate no opponent
    Node b;
    Node winner;
};

// Result structure containing champion and per-round match history
struct KnockoutResult {
    Node champion;
    // rounds[i] are the matches that happened in round i (0-based)
    std::vector<std::vector<Match>> rounds;
};

// Run knockout and also return per-round match history.
inline KnockoutResult runKnockoutWithHistory(std::vector<Node> players) {
    if (players.empty()) throw std::runtime_error("No players provided");
    KnockoutResult result;

    // Shuffle players first for randomness
    std::shuffle(players.begin(), players.end(), rng::get());

    while (players.size() > 1) {
        std::vector<Node> nextRound;
        std::vector<Match> matchesThisRound;
        size_t i = 0;
        for (; i + 1 < players.size(); i += 2) {
            Node winner = playMatch(players[i], players[i+1]);
            Match m{players[i], players[i+1], winner};
            matchesThisRound.push_back(m);
            nextRound.push_back(winner);
        }
        if (i < players.size()) {
            // bye
            Match m{players[i], Node{}, players[i]};
            matchesThisRound.push_back(m);
            nextRound.push_back(players[i]);
        }
        result.rounds.push_back(std::move(matchesThisRound));
        players.swap(nextRound);
    }

    result.champion = players.front();
    return result;
}

// Return a vector of opponents that the champion faced in each round (0-based).
// If the champion had a bye in a round, the corresponding entry will have an empty Name.
inline std::vector<Node> championOpponents(const KnockoutResult &res) {
    std::vector<Node> opponents;
    for (const auto &round : res.rounds) {
        bool found = false;
        for (const auto &m : round) {
            if (m.winner.Name == res.champion.Name) {
                // opponent is the other player
                if (m.a.Name == res.champion.Name) opponents.push_back(m.b);
                else opponents.push_back(m.a);
                found = true;
                break;
            }
        }
        if (!found) {
            // champion did not appear as a winner in this round (e.g., didn't play)
            opponents.push_back(Node{});
        }
    }
    return opponents;
}

// Return the actual Match records that the champion played (one per round they played).
inline std::vector<Match> championMatches(const KnockoutResult &res) {
    std::vector<Match> out;
    for (const auto &round : res.rounds) {
        bool found = false;
        for (const auto &m : round) {
            if (m.winner.Name == res.champion.Name) {
                out.push_back(m);
                found = true;
                break;
            }
        }
        if (!found) {
            // champion didn't have a winning match this round (e.g., didn't play)
            out.push_back(Match{Node{}, Node{}, Node{}});
        }
    }
    return out;
}

} // namespace tournament
