#include "header.h"

void enterTournamentResults250(std::vector<std::pair<std::string, std::string>>& matches) {
    for (size_t i = 0; i < matches.size(); ++i) {
        std::string winnerSurname, winnerName;
        std::cout << MAGENTA << "Enter winner of match " << i + 1 << " (" << RESET << matches[i].first << MAGENTA << " vs. " << RESET << matches[i].second << MAGENTA << "): " << RESET;
        std::cin >> winnerSurname >> winnerName;
        std::string winnerFullNameSpace = winnerSurname + " " + winnerName;
        if (winnerFullNameSpace != matches[i].first && winnerFullNameSpace != matches[i].second) {
            std::cout << RED << "Wrong input!" << RESET;
            exit(0);
        }

        // Concatenate surname and name for the winner
        std::string winnerFullName = winnerSurname + "_" + winnerName;

        // Open the file for the winner
        std::string filename = winnerFullName + ".txt";
        std::ifstream winnerFile(filename);

        if (winnerFile.is_open()) {
            std::ofstream tempFile("temp.txt");
            if (tempFile.is_open()) {
                std::string line;
                int lineNumber = 0;
                while (getline(winnerFile, line)) {
                    lineNumber++;
                    if (lineNumber == 4) { // Update the fourth line
                        int currentPoints;
                        std::istringstream iss(line);
                        iss >> currentPoints;
                        currentPoints += 62; // Increment the points by 62
                        tempFile << currentPoints << std::endl; // Write updated points to temp file
                    } else if (lineNumber == 5) { // Update the fifth line
                        std::istringstream iss(line);
                        std::vector<std::string> results;
                        std::string result;
                        while (iss >> result) {
                            if (result == "R16" && matches.size() == 8) {
                                result = "R8";
                            } else if (result == "R8" && matches.size() == 4) {
                                result = "R4";
                            } else if (result == "R4" && matches.size() == 2) {
                                result = "R2";
                            } else if (result == "R2" && matches.size() == 1) {
                                result = "1";
                            } else if (result == "1" && matches.size() == 1) {
                                result = "2";
                            } else if (result == "2" && matches.size() == 1) {
                                result = "3";
                            } else if (result == "3" && matches.size() == 1) {
                                result = "4";
                            } else if (result == "4" && matches.size() == 1) {
                                result = "5";
                            } else if (result == "5" && matches.size() == 1) {
                                result = "6";
                            } else if (result == "6" && matches.size() == 1) {
                                result = "7";
                            } else if (result == "7" && matches.size() == 1) {
                                result = "8";
                            }else if (result == "6" && matches.size() == 1) {
                                result = "7";
                            } else if (result == "7" && matches.size() == 1) {
                                result = "8";
                            } else if (result == "8" && matches.size() == 1) {
                                result = "9";
                            } else if (result == "9" && matches.size() == 1) {
                                result = "10";
                            } else if (result == "10" && matches.size() == 1) {
                                result = "11";
                            } else if (result == "11" && matches.size() == 1) {
                                result = "12";
                            } else if (result == "12" && matches.size() == 1) {
                                result = "13";
                            } else if (result == "13" && matches.size() == 1) {
                                result = "14";
                            } else if (result == "14" && matches.size() == 1) {
                                result = "15";
                            }
                            results.push_back(result);

                        }
                        // Write updated best result back to temp file
                        for (const auto& res : results) {
                            tempFile << res << " ";
                        }
                        tempFile << std::endl;
                    } else {
                        tempFile << line << std::endl; // Copy other lines as is to temp file
                    }
                }
                winnerFile.close();
                tempFile.close();

                // Remove the original file and rename the temp file
                remove(filename.c_str());
                rename("temp.txt", filename.c_str());
            } else {
                std::cerr << "Error: Unable to create temporary file." << std::endl;
            }
        } else {
            std::cerr << "Error: Unable to open winner's file." << std::endl;
        }

        matches[i].first = winnerSurname + " " + winnerName; // Concatenate surname and name for the winner
        matches[i].second.clear(); // Clear the loser's name
    }
}

void runTournament250() {
    // Read player names from input
    std::vector<std::string> players(16);
    std::cout << "Enter 16 player names:" << std::endl;
    for (int i = 0; i < 16; ++i) {
        std::string surname, name;
        std::cout << MAGENTA<<"Player " << i + 1 << " (Surname Name): "<<RESET;
        std::cin >> surname >> name;
        players[i] = surname + " " + name;
    }

    // Check if all players exist in rankings.txt
    bool allPlayersExist = true; // Assume all players exist initially
    for (const auto& player : players) {
        if (!playerExists(player)) {
            allPlayersExist = false; // At least one player is missing
            break; // No need to continue checking if one player is missing
        }
    }

    if (!allPlayersExist) {
        std::vector<std::string> missingPlayers;
        for (const auto& player : players) {
            if (!playerExists(player)) {
                missingPlayers.push_back(player);
            }
        }
        std::cout << "The following players do not exist in the rankings:" << std::endl;
        for (const auto& player : missingPlayers) {
            std::cout << player << std::endl;
        }
        return;
    }

    // If all players exist, proceed with the tournament

    // Assign matches for the first round randomly
    std::vector<std::pair<std::string, std::string>> firstRoundMatches(8);
    assignFirstRound(firstRoundMatches, players);

    // Display the first round matches
    std::cout <<MAGENTA_LIGHT<< "First Round Matches:" <<RESET<< std::endl;
    displayBracket(firstRoundMatches);

    // Enter tournament results for the first round
    enterTournamentResults250(firstRoundMatches);

    // Display the winners of the first round
    std::cout << "Winners of the First Round:" << std::endl;
    for (size_t i = 0; i < firstRoundMatches.size(); ++i) {
        std::cout << "Match " << i + 1 << " Winner: " << firstRoundMatches[i].first << std::endl;
    }

    // Determine second round matches based on the winners of the first round
    std::vector<std::pair<std::string, std::string>> secondRoundMatches = {
            {firstRoundMatches[0].first, firstRoundMatches[1].first}, // Match A
            {firstRoundMatches[2].first, firstRoundMatches[3].first}, // Match B
            {firstRoundMatches[4].first, firstRoundMatches[5].first}, // Match C
            {firstRoundMatches[6].first, firstRoundMatches[7].first}  // Match D
    };

    // Display the second round matches
    std::cout <<MAGENTA_LIGHT<< "Second Round Matches:" <<RESET<< std::endl;
    displayBracket(secondRoundMatches);

    // Enter tournament results for the second round
    enterTournamentResults250(secondRoundMatches);

    // Display the winners of the second round
    std::cout << "Winners of the Second Round:" << std::endl;
    for (size_t i = 0; i < secondRoundMatches.size(); ++i) {
        std::cout << "Match " << static_cast<char>('A' + i) << " Winner: " << secondRoundMatches[i].first << std::endl;
    }

    // Determine semifinal matches based on the winners of the second round
    std::vector<std::pair<std::string, std::string>> semifinalMatches = {
            {secondRoundMatches[0].first, secondRoundMatches[1].first}, // Match E
            {secondRoundMatches[2].first, secondRoundMatches[3].first}  // Match F
    };

    // Display the semifinal matches
    std::cout <<MAGENTA_LIGHT<< "Third Round Matches:"<<RESET << std::endl;
    displayBracket(semifinalMatches);

    // Enter tournament results for the semifinals
    enterTournamentResults250(semifinalMatches);

    // Display the winners of the semifinals
    std::cout << "Winners of the Semifinals:" << std::endl;
    std::cout << "Match E Winner: " << semifinalMatches[0].first << std::endl;
    std::cout << "Match F Winner: " << semifinalMatches[1].first << std::endl;

    // Determine the final match based on the winners of the semifinals
    std::vector<std::pair<std::string, std::string>> finalMatch = {
            {semifinalMatches[0].first, semifinalMatches[1].first} // Final Match
    };

    // Display the final match
    std::cout <<MAGENTA_LIGHT<< "Final Match:" <<RESET<< std::endl;
    displayBracket(finalMatch);

    // Enter tournament results for the final match
    enterTournamentResults250(finalMatch);

    // Display the winner of the tournament
    std::cout <<GOLD<< "Tournament Winner: " <<RESET<< finalMatch[0].first << std::endl;
    updateRankings();
    std::cout << "Please select an option:" << std::endl;
    std::cout << MAGENTA << "1. Back to menu" << std::endl;
    std::cout << MAGENTA << "2. Exit" << std::endl;
    int choice;
    std::cout << RESET << "Enter your choice (" << MAGENTA << "1" << RESET << ", or " << MAGENTA << "2" << RESET
              << "): ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            menu();
            break;
        case 2:
            exit(0);
        default:
            std::cout << MAGENTA_LIGHT << RED << "Invalid choice!"<< RESET
                      << std::endl;
            break;}
}