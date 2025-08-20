#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>


struct HighScoreData
{
    int HighScore;          // Player's score at the end of the game
    float TimeToComplete;   // Time taken to complete the game in seconds

    HighScoreData(int highScore = 0, float timeToComplete = 0.0f)
        : HighScore(highScore), TimeToComplete(timeToComplete) {
    }
};

class Player {
private:
    // The current health of the player
    int Health;

public:
    // Constructor to initialize the player's health
    Player(int initialHealth) : Health(initialHealth) {}

    // Returns the current health of the player
    int GetHealth() {
        return Health;
    }

    // Sets the player's health (optional for better usability)
    void SetHealth(int newHealth) {
        Health = newHealth;
    }
};


class HighScoreManager
{
private:
    static const std::string filePath;

public:
    static void SaveHighScore(const HighScoreData& highScoreData)
    {
        std::ofstream outFile(filePath, std::ios::binary);
        if (outFile.is_open())
        {
            outFile.write(reinterpret_cast<const char*>(&highScoreData), sizeof(HighScoreData));
            outFile.close();
        }
        else
        {
            std::cerr << "Error: Unable to open file for saving high score.\n";
        }
    }

    static HighScoreData LoadHighScore()
    {
        HighScoreData highScoreData;
        std::ifstream inFile(filePath, std::ios::binary);
        if (inFile.is_open())
        {
            inFile.read(reinterpret_cast<char*>(&highScoreData), sizeof(HighScoreData));
            inFile.close();
        }
        else
        {
            std::cerr << "Error: Unable to open file for loading high score. Returning default values.\n";
        }
        return highScoreData;
    }
};

const std::string HighScoreManager::filePath = "highscores.dat";

int main()
{
    // Create a Player object with initial health of 100
    Player player(100);

    // Display the player's current health
    std::cout << "Player's Health: " << player.GetHealth() << std::endl;

    // Update the player's health
    player.SetHealth(80);
    std::cout << "Player's Health after taking damage: " << player.GetHealth() << std::endl;
    // Create a new high score
    HighScoreData newHighScore(1500, 120.5f);

    // Save the high score
    HighScoreManager::SaveHighScore(newHighScore);

    // Load the high score
    HighScoreData loadedHighScore = HighScoreManager::LoadHighScore();

    std::cout << "High Score: " << loadedHighScore.HighScore
        << ", Time: " << loadedHighScore.TimeToComplete << " seconds\n";

    return 0;
}
