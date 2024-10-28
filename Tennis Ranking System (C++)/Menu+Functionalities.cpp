#include "header.h"

int menu() {
    std::cout << MAGENTA_LIGHT << "Welcome to the Tennis Ranking System!" << RESET << std::endl;
    std::cout << "Please select an option:" << std::endl;
    std::cout << MAGENTA << "1. See Rankings" << std::endl;
    std::cout << MAGENTA << "2. See Player Stats" << std::endl;
    std::cout << MAGENTA << "3. Enter Tournament Results" << std::endl;
    std::cout << MAGENTA << "4. Add a New Player" << std::endl;
    std::cout << MAGENTA << "5. Delete a Player" << std::endl;

    int choice,choice1;
    std::cout << RESET << "Enter your choice (" << MAGENTA << "1" << RESET << ", " << MAGENTA << "2" << RESET
              << ", " << MAGENTA << "3" << RESET << ", " << MAGENTA << "4" << RESET << ", or " << MAGENTA << "5" << RESET << "): ";
    std::cin >> choice;
    std::string surname, name;
    switch (choice) {
        case 1:
            std::cout << MAGENTA_LIGHT << "--- Top 16 WTA ---" << RESET << std::endl;
            displayRankings();
            break;
        case 2:
            std::cout << "Enter player's surname: ";
            std::cin >> surname;
            std::cout << "Enter player's name: ";
            std::cin >> name;
            displayPlayerStats(surname, name);
            break;
        case 3:
            std::cout << "Select tournament level:" << std::endl;
            std::cout << MAGENTA << "1. WTA250" << std::endl;
            std::cout << MAGENTA << "2. WTA500" << std::endl;
            std::cout << MAGENTA << "3. WTA1000" << std::endl;
            std::cout << RESET << "Enter your choice (" << MAGENTA << "1" << RESET << ", " << MAGENTA << "2" << RESET
                      << ", or " << MAGENTA << "3" << RESET << "): ";
            std::cin >> choice1;
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            switch (choice1) {
                case 1:
                    std::cout << MAGENTA_LIGHT << "--- WTA250 ---" << RESET << std::endl;
                    runTournament250();
                    break;
                case 2:
                    std::cout << MAGENTA_LIGHT << "--- WTA500 ---" << RESET << std::endl;
                    runTournament500();
                    break;
                case 3:
                    std::cout << MAGENTA_LIGHT << "--- WTA1000 ---" << RESET << std::endl;
                    runTournament1000();
                    break;
                default:
                    std::cout  << RED << "Invalid choice!"<<RESET
                               << std::endl;
                    break;}
            break;
        case 4:
            std::cout << "You chose to add a new player." << std::endl;
            addNewPlayer();
            break;
        case 5:
            std::cout << "You chose to delete a player." << std::endl;
            std::cout << "Enter player's surname: ";
            std::cin >> surname;
            std::cout << "Enter player's name: ";
            std::cin >> name;
            deletePlayer(surname, name);
            break;
        default:
            std::cout  << RED << "Invalid choice!"<<RESET
                       << std::endl;
            break;
    }

    return 0;
}

void displayRankings() {
    std::ifstream file("rankings.txt");
    if (file.is_open()) {
        std::string player;
        int rank = 1;
        while (getline(file, player) && rank<17) {
            std::cout << rank << ". " << player << std::endl;
            rank++;
        }
        file.close();
    } else {
        std::cerr << RED << "Unable to open file. Make sure 'rankings.txt' exists in the current directory." << RESET << std::endl;
    }
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
            break;
    }
}

void displayPlayerStats(const std::string& surname, const std::string& name) {
    int playerRank = getPlayerRank(surname, name);
    std::string filename = surname + "_" + name + ".txt";
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string fname, country, age, points, rank, t1, t2, t3;
        getline(file, fname);
        getline(file, country);
        getline(file, age);
        getline(file, points);
        getline(file, t1);
        getline(file, t2);
        getline(file, t3);


        std::cout << MAGENTA_LIGHT << "Player Stats for " << surname << " " << name << ":" << std::endl;
        std::cout << RESET << MAGENTA << "Name: " << RESET << fname << std::endl;
        std::cout << MAGENTA << "Country: " << RESET << country << std::endl;
        std::cout << MAGENTA << "Age: " << RESET << age << std::endl;
        std::cout << MAGENTA << "Rank: " << RESET << playerRank << std::endl;
        std::cout << MAGENTA << "Points: " << RESET << points << std::endl;
        std::cout << MAGENTA << "Best Results at Different Levels: " << RESET << std::endl;

        char* endPtr;
        int converted_number = std::strtol(t1.c_str(), &endPtr, 10);
        if (*endPtr == '\0') {
            if (converted_number > 1)
                std::cout << MAGENTA << "WTA250: " << RESET << converted_number << " titles" << std::endl;
            else
                std::cout << MAGENTA << "WTA250: 1 title" << std::endl;
        } else {
            std::cout << MAGENTA << "WTA250: " << RESET << t1 << std::endl;
        }

        char* endPtr1;
        int converted_number2 = std::strtol(t2.c_str(), &endPtr1, 10);
        if (*endPtr1 == '\0') {
            if (converted_number2 > 1)
                std::cout << MAGENTA << "WTA500: " << RESET << converted_number2 << " titles" << std::endl;
            else
                std::cout << MAGENTA << "WTA500: 1 title" << std::endl;
        } else {
            std::cout << MAGENTA << "WTA500: " << RESET << t2 << std::endl;
        }

        char* endPtr2;
        int converted_number3 = std::strtol(t3.c_str(), &endPtr2, 10);
        if (*endPtr2 == '\0') {
            if (converted_number3 > 1)
                std::cout << MAGENTA << "WTA1000: " << RESET << converted_number3 << " titles" << std::endl;
            else
                std::cout << MAGENTA << "WTA1000: 1 title" << std::endl;
        } else {
            std::cout << MAGENTA << "WTA1000: " << RESET << t3 << std::endl;
        }

        file.close();
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
    } else {
        std::cerr << RESET << RED << "Player: " << surname << " " << name <<" does not exist in the Top 16."<< RESET << std::endl;
    }

}

void addNewPlayer() {
    std::string surname, name, country, age;
    int points;
    std::cout << "Enter player's surname: ";
    std::cin >> surname;
    std::cout << "Enter player's name: ";
    std::cin >> name;
    std::cout << "Enter player's country: ";
    std::cin >> country;
    std::cout << "Enter player's age: ";
    std::cin >> age;
    std::cout << "Enter player's points: ";
    std::cin >> points;
    // Create new file for the player
    std::string filename = surname + "_" + name + ".txt";
    std::ofstream playerFile(filename);
    if (playerFile.is_open()) {
        // Write player details to the file
        playerFile << surname <<" "<<name<< std::endl;
        playerFile << country << std::endl;
        playerFile << age << std::endl;
        playerFile << points << std::endl;
        playerFile << "R16" << std::endl;
        playerFile << "R16" << std::endl;
        playerFile << "R16" << std::endl;
        std::cout <<MAGENTA<< "Player " << surname << " " << name << " was added successfully." <<RESET<< std::endl;
        playerFile.close();
    } else {
        std::cerr << "Unable to create player file." << std::endl;
        return;
    }

    // Append new player's name to rankings.txt
    std::ofstream outputFile("rankings.txt", std::ios_base::app);
    if (outputFile.is_open()) {
        outputFile << surname << " " << name << std::endl;
        outputFile.close();
    } else {
        std::cerr << "Unable to open rankings file for appending." << std::endl;
        return;
    }
    updateRankings();

}

void deletePlayer(const std::string& surname, const std::string& name) {
    std::string filename = surname + "_" + name + ".txt";
    if (remove(filename.c_str()) != 0) {
        std::cerr << "\033[31mError deleting player: " << surname << " " << name << "\033[0m" << std::endl;
        return; // Exit function if deletion fails
    } else {
        std::cout << "\033[35mPlayer " << surname << " " << name << " has been successfully deleted." << "\033[0m" << std::endl;
    }

    // Remove player from rankings.txt
    std::ifstream inputFile("rankings.txt");
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line)) {
        // Check if the line contains the player's name
        if (line.find(surname + " " + name) == std::string::npos) {
            // If not, add it to the lines vector
            lines.push_back(line);
        }
    }
    inputFile.close();

    // Rewrite the remaining lines to the rankings.txt file
    std::ofstream outputFile("rankings.txt");
    for (const auto& l : lines) {
        outputFile << l << std::endl;
    }
    outputFile.close();
    std::cout << MAGENTA_LIGHT<<"Rankings updated." <<RESET<< std::endl;
}

