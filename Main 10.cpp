#include <iostream>
#include <string>
using namespace std;

class Fighter {
private:
    std::string name;
    int health;
    int attackPower;
    // Function to generate random numbers in range

    int getRandom(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    // Function to display health bars
    void displayHealth(const string& name, int health, int maxHealth) {
        cout << name << "}";
        int barWidth = 20;
        int healthBars = (health * barWidth) / maxHealth;
        for (int i = 0; i < barWidth; ++i) {
            if (i < healthBars) cout << "#";
            else cout << " ";
        }
        cout << "}" << health << "/" << maxHealth << "HP\n";
    }
public:
    // Constructor
    Fighter(const std::string& fighterName, int fighterHealth, int fighterAttackPower)
        : name(fighterName), health(fighterHealth), attackPower(fighterAttackPower) {}

    // Copy Constructor (Rule of Three)
    Fighter(const Fighter& other)
        : name(other.name), health(other.health), attackPower(other.attackPower) {
        std::cout << "Copy Constructor called for " << name << "\n";
    }

    // Copy Assignment Operator (Rule of Three)
    Fighter& operator=(const Fighter& other) {
        if (this != &other) {
            name = other.name;
            health = other.health;
            attackPower = other.attackPower;
            std::cout << "Copy Assignment Operator called for " << name << "\n";
        }
        return *this;
    }

    // Destructor (Rule of Three)
    ~Fighter() {
        std::cout << "Destructor called for " << name << "\n";
    }

    // Move Constructor (Rule of Five)
    Fighter(Fighter&& other) noexcept
        : name(std::move(other.name)), health(other.health), attackPower(other.attackPower) {
        other.health = 0; // Reset the moved-from object's state
        other.attackPower = 0;
        std::cout << "Move Constructor called for " << name << "\n";
    }

    // Move Assignment Operator (Rule of Five)
    Fighter& operator=(Fighter&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            health = other.health;
            attackPower = other.attackPower;

            other.health = 0; // Reset the moved-from object's state
            other.attackPower = 0;
            std::cout << "Move Assignment Operator called for " << name << "\n";
        }
        return *this;
    }

    // Display Fighter Info
    void display() const {
        std::cout << "Fighter: " << name << ", Health: " << health
                  << ", Attack Power: " << attackPower << "\n";
    }
};

int main() {
    Fighter fighter1("Warrior", 100, 50);
    Fighter fighter2("Mage", 80, 70);

    // Copy Constructor
    Fighter fighter3 = fighter1;

    // Copy Assignment
    fighter2 = fighter1;

    // Move Constructor
    Fighter fighter4 = std::move(fighter1);

    // Move Assignment
    fighter2 = std::move(fighter3);

    // Display remaining fighters
    fighter2.display();
    fighter4.display();


    return 0;
}
