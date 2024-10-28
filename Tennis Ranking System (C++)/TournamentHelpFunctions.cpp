#include "header.h"

bool playerExists(const std::string& fullName) {
    // Split the full name into surname and name
    std::istringstream iss(fullName);
    std::string surname, name;
    iss >> surname >> name;

    // Open the rankings file
    std::ifstream file("rankings.txt");
    if (file.is_open()) {
        std::string player;
        while (getline(file, player)) {
            // Split the name in the file into surname and name
            std::istringstream issPlayer(player);
            std::string playerSurname, playerName;
            issPlayer >> playerSurname >> playerName;

            // Compare surname and name separately
            if (surname == playerSurname && name == playerName) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

void assignFirstRound(std::vector<std::pair<std::string, std::string>>& matches, const std::vector<std::string>& players) {
    std::vector<std::string> shuffledPlayers = players;
    // Seed the random number generator
    std::random_device rd;
    std::default_random_engine rng(rd());
    // Shuffle the players
    std::shuffle(shuffledPlayers.begin(), shuffledPlayers.end(), rng);

    // Assign matches
    for (size_t i = 0; i < matches.size(); ++i) {
        matches[i].first = shuffledPlayers[i * 2];
        matches[i].second = shuffledPlayers[i * 2 + 1];
    }
}

void displayBracket(const std::vector<std::pair<std::string, std::string>>& matches) {
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << MAGENTA<<"Match " << i + 1 << ": " <<RESET<< matches[i].first << MAGENTA<<" vs. " << RESET<<matches[i].second << std::endl;
    }
}
