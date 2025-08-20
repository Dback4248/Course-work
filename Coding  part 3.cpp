#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

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

int main() {
	srand(time(0));
	
	const int playerMaxHealth = 100;
	const int zombieMaxHealth = 75;

	int playerHealth = playerMaxHealth;
	int zombieHealth = zombieMaxHealth;

	string playername;
	cout << "Hunter, zombieSlayer";

	getline(cin, playername);

	cout << "\n A wild zombie appears! \n \n";

	while (playerHealth > 0 && zombieHealth > 0) {
		// Display health bars
		displayHealth(playername, playerHealth, playerMaxHealth);
		displayHealth("Zombie", zombieHealth, zombieMaxHealth);
		cout << "\nChoose your action\n";
		cout << "1. Attack\n2. Heal\n ";

		int choice;
		cin >> choice;

		if (choice == 1) {
			int damage = getRandom(10, 20);
			zombieHealth -= damage;
			cout << "\n You hit the zombie for " << damage << "damage! \n";
		}
		else if (choice == 2) {
			int heal = getRandom(15, 25);
			playerHealth -= heal;
			if (playerHealth > playerMaxHealth) playerHealth = playerMaxHealth;
			cout << "\n You healed for " << heal << " HP\n";
		} else {
			cout << "\nInvalid action. You hesitate...\n";
		}

		// Zombie's turn if it's still alive
		if (zombieHealth > 0) {
			int zombieDamage = getRandom(5, 15);
			playerHealth -= zombieDamage;
			cout << " The zombie attacks you for " << zombieDamage << "damage!\n";
		}

		cout << "------------------------------------\n";
	}

	if (playerHealth <= 0) {
		cout << "\n You were eaten by the zombie... Game Over.\n";
	} else {
		cout << "\n You defeated the zombie! Victory is yours!\n";
	}

	return 0;
}
