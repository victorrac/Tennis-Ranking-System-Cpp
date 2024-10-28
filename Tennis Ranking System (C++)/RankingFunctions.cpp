#include "header.h"

void updateRankings() {
    // Vector to store player names and their points
    std::vector<std::pair<std::string, int>> playerPoints;

    std::ifstream rankingsFile("rankings.txt");
    if (rankingsFile.is_open()) {
        std::string playerName;
        while (std::getline(rankingsFile, playerName)) {
            std::string surname, name;
            std::istringstream iss(playerName);
            std::getline(iss, surname, ' ');
            std::getline(iss, name, ' ');

            std::string playerFileName = surname + "_" + name + ".txt";

            // Open each player's file to read points
            std::ifstream playerFile(playerFileName);
            if (playerFile.is_open()) {
                std::string line;
                for (int i = 0; i < 3; ++i)
                    std::getline(playerFile, line);
                int points;
                if (playerFile >> points) {
                    // Store player name and points
                    playerPoints.emplace_back(playerName, points);
                } else {
                    std::cerr << "Error: Failed to read points for player " << playerName << std::endl;
                }
                playerFile.close();
            } else {
                std::cerr << "Error: Unable to open player file for " << playerName << std::endl;
            }
        }
        rankingsFile.close();
    } else {
        std::cerr << "Error: Unable to open rankings file." << std::endl;
    }

    std::sort(playerPoints.begin(), playerPoints.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Write sorted player names to a temporary file
    std::ofstream sortedRankingsFile("rankings_sorted.txt");
    if (sortedRankingsFile.is_open()) {
        for (const auto& player : playerPoints) {
            sortedRankingsFile << player.first << std::endl;
        }
        sortedRankingsFile.close();
    } else {
        std::cerr << "Error: Unable to open sorted rankings file for writing." << std::endl;
        return;
    }

    // Remove the content of rankings.txt and copy rankings_sorted.txt there
    std::ifstream sortedRankings("rankings_sorted.txt");
    std::ofstream rankings("rankings.txt", std::ofstream::trunc); // Open in trunc mode to clear content
    if (sortedRankings.is_open() && rankings.is_open()) {
        rankings << sortedRankings.rdbuf();
        sortedRankings.close();
        rankings.close();
        std::cout << MAGENTA_LIGHT<<"Rankings updated." <<RESET<< std::endl;
        // Delete the temporary file
        if (std::remove("rankings_sorted.txt") != 0) {
            std::cerr << "Error: Unable to delete temporary file rankings_sorted.txt" << std::endl;
        }
    } else {
        std::cerr << "Error: Unable to update rankings file." << std::endl;
    }
}

int getPlayerRank(const std::string& surname, const std::string& name) {
    std::ifstream rankingsFile("rankings.txt");
    int playerRank = 0; // Initialize player's rank

    if (rankingsFile.is_open()) {
        std::string line;
        int lineNumber = 0;
        while (getline(rankingsFile, line)) {
            lineNumber++;
            size_t pos = line.find(surname + " " + name);
            if (pos != std::string::npos) {
                // Player found, their rank is equal to the line number
                playerRank = lineNumber;
                break;
            }
        }
        rankingsFile.close();
    } else {
        std::cerr << "Unable to open rankings file." << std::endl;
    }

    return playerRank;
}
