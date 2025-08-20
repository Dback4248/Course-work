#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

// Struct to represent a Player
struct Player {
    int id;
    std::string name;
    struct Stats {
        int attack;
        int defense;
        int speed;
    } stats;
};

// Function to generate players with semi-randomized stats
void generatePlayers(std::vector<Player>& playerArray, int numberOfPlayers) {
    std::srand(std::time(0)); // Seed for random number generation
    for (int i = 0; i < numberOfPlayers; ++i) {
        Player player;
        player.id = i + 1;
        player.name = "Player_" + std::to_string(i + 1);
        player.stats.attack = std::rand() % 50 + 50; // Attack: 50-99
        player.stats.defense = std::rand() % 50 + 50; // Defense: 50-99
        player.stats.speed = std::rand() % 50 + 50; // Speed: 50-99
        playerArray.push_back(player);
    }
}

// Function to print player details
void printPlayerDetails(const Player& player) {
    std::cout << "ID: " << player.id << std::endl;
    std::cout << "Name: " << player.name << std::endl;
    std::cout << "Stats:" << std::endl;
    std::cout << "  Attack: " << player.stats.attack << std::endl;
    std::cout << "  Defense: " << player.stats.defense << std::endl;
    std::cout << "  Speed: " << player.stats.speed << std::endl;
    std::cout << "-------------------------" << std::endl;
}

// Main function to demonstrate functionality
int main() {
    std::vector<Player> players;
    int numberOfPlayers = 5; // Generate 5 players
    generatePlayers(players, numberOfPlayers);

    // Print details of all players
    for (const auto& player : players) {
        printPlayerDetails(player);
    }

    return 0;
}