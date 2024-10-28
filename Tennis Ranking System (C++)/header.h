#ifndef UNTITLED2_HEADER_H
#define UNTITLED2_HEADER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <utility>
#define RESET   "\033[0m"
#define MAGENTA "\033[35m"
#define MAGENTA_LIGHT "\033[95m"
#define RED "\033[31m"
#define GOLD "\033[38;5;220m"

int menu();
void updateRankings();
bool playerExists(const std::string& fullName);
void assignFirstRound(std::vector<std::pair<std::string, std::string>>& matches, const std::vector<std::string>& players);
void displayBracket(const std::vector<std::pair<std::string, std::string>>& matches);
void enterTournamentResults250(std::vector<std::pair<std::string, std::string>>& matches);
void runTournament250();
void enterTournamentResults500(std::vector<std::pair<std::string, std::string>>& matches);
void runTournament500();
void enterTournamentResults1000(std::vector<std::pair<std::string, std::string>>& matches);
void runTournament1000();
int getPlayerRank(const std::string& surname, const std::string& name);
void displayRankings();
void displayPlayerStats(const std::string& surname, const std::string& name);
void deletePlayer(const std::string& surname, const std::string& name);
void addNewPlayer();
int menu();


#endif //UNTITLED2_HEADER_H
