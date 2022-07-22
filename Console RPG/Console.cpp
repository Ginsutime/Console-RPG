#include "Console.h"

/*
4. Follow along with rest of video (pt 6)
5. Fix invalid number option so that it allows the user to type again, currently continues looping through else portion of code
6. Find a better place to store all the global/local vars if possible (struct or class?)
*/

std::string name = " ", race = " ", sex = " ";
int level = 0, xp = 0, health = 0, totalHealth = 0, xpToNextLevel = 0, heal = 0;
int monsterHP = 0, monsterXP = 0, monsterLevel = 0;

std::string monsterName[] = { "Goblin", "Dwarf", "Ogre", "Witch", "Demon", "Wizard" };
std::string currentMonster = " ";
bool playerTurnComplete = false;

std::random_device dev;
std::mt19937 rng(dev());

void HUD()
{
	Sleep(500);
	Clear();
	std::cout << "|" << std::left << std::setw(7) << "Name: " << std::setw(12) << name <<
		"|" << std::setw(8) << "Health: " << std::setw(11) << health << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(7) << "Race: " << std::setw(12) << race <<
		"|" << std::setw(8) << "Sex: " << std::setw(11) << sex << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(7) << "Level: " << std::setw(12) << level <<
		"|" << std::setw(8) << "XP: " << std::setw(11) << xp << "|" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "|" << std::internal << std::setw(30) << "XP Needed To Level Up: " <<
		xpToNextLevel << std::right << std::setw(8) << "|" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

void CombatHUD()
{
	Sleep(500);
	Clear();
	std::cout << "|" << std::left << std::setw(8) << "Name: " << std::setw(12) << name <<
		std::setw(7) << "|" << std::right << std::setw(16) << "Monster Name: " <<
		std::setw(6) << currentMonster << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(8) << "Health: " << std::setw(12) << health <<
		std::setw(7) << "|" << std::right << std::setw(16) << "Monster Health: " <<
		std::setw(6) << monsterHP << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(8) << "Level: " << std::setw(12) << level <<
		std::setw(7) << "|" << std::right << std::setw(16) << "Monster Level: " <<
		std::setw(6) << monsterLevel << "|" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
}

void CreatePlayer()
{
	// Char creation
	std::cout << "Enter Character Name: ";
	std::cin >> name;
	ValidateRace();
	ValidateSex();

	// Flavor creation text
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0)
			std::cout << "Creating Character.\n";
		else if (i == 1)
			std::cout << "Creating Character..\n";
		if (i == 2)
			std::cout << "Creating Character...\n";

		Sleep(600);
		Clear();
	}
}

void ValidateRace()
{
	std::string playerRace[] = { "Gnome", "Elf", "Human", "Aasimar", "Goliath" };
	int raceNumberInput = 0;
	bool correctRaceInput = false;

	std::cout << '\n' << "Playable Character Races: " << std::endl;
	std::cout << "1: Gnome" << std::endl;
	std::cout << "2: Elf" << std::endl;
	std::cout << "3: Human" << std::endl;
	std::cout << "4: Aasimar" << std::endl;
	std::cout << "5: Goliath" << std::endl;
	std::cout << '\n' << "Enter Character Race #: ";
	std::cin >> raceNumberInput;

	while (!correctRaceInput)
	{
		switch (raceNumberInput)
		{
		case 1:
			race = playerRace[0];
			health = 60;
			correctRaceInput = true;
			break;
		case 2:
			race = playerRace[1];
			health = 80;
			correctRaceInput = true;
			break;
		case 3:
			race = playerRace[2];
			health = 100;
			correctRaceInput = true;
			break;
		case 4:
			race = playerRace[3];
			health = 120;
			correctRaceInput = true;
			break;
		case 5:
			race = playerRace[4];
			health = 120;
			correctRaceInput = true;
			break;
		default:
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "That is not a valid numerical option for a race. Try again: ";
			std::cin >> raceNumberInput;
			break;
		}
	}
}

void ValidateSex()
{
	char sexInput;
	bool correctSexInput = false;

	std::cout << "Enter Letter Denoting Character Sex (M or F)" << std::endl;
	std::cin.ignore(INT_MAX, '\n');
	sexInput = std::cin.get();
	std::cin.ignore(INT_MAX, '\n');

	while (!correctSexInput)
	{
		switch (sexInput)
		{
		case 'm':
		case 'M':
			sex = "Male";
			correctSexInput = true;
			break;
		case 'f':
		case 'F':
			sex = "Female";
			correctSexInput = true;
			break;
		default:
			std::cin.clear();
			std::cout << "Invalid answer for sex. Try again." << std::endl;
			sexInput = std::cin.get();
			std::cin.ignore(INT_MAX, '\n');
			break;
		}
	}
}

void CreateMonster()
{
	size_t monsterArrSize = sizeof(monsterName) / sizeof(monsterName[0]);

	std::uniform_int_distribution<std::size_t> monsterName_distribution(0, monsterArrSize - 1);
	auto random_monsterName = monsterName_distribution(rng);
	std::uniform_int_distribution<std::size_t> monsterHP_distribution(20, 50);
	auto random_monsterHP = monsterHP_distribution(rng);
	std::uniform_int_distribution<std::size_t> monsterLevel_distribution(0, 2);
	auto random_monsterLevel = monsterLevel_distribution(rng);

	currentMonster = monsterName[random_monsterName];

	monsterHP = random_monsterHP;
	monsterLevel = random_monsterLevel + level;
	monsterXP = monsterHP;
}

void LevelUp()
{
	xp += monsterXP;

	if (xp >= xpToNextLevel)
	{
		level++;
		xpToNextLevel = xpToNextLevel * 3 / 2;
		totalHealth += 20; health += 20;

		std::cout << "You have leveled up and are now level " << level
			<< ". Your total health has increased 20 points to " << totalHealth << "!" << std::endl;

		Sleep(2000);
		HUD();
		Moving();
	}
}

void Moving()
{
	std::uniform_int_distribution<std::size_t> encounterChance_distribution(1, 100);
	auto random_encounterChance = encounterChance_distribution(rng);
	int moveOption;

	std::cout << std::endl;
	std::cout << "1. Move Forward" << std::endl;
	std::cout << "2. Rest" << std::endl;
	std::cout << "3. Move Backward" << std::endl;
	std::cout << std::endl;

	std::cin >> moveOption;

	// Move forward
	if (moveOption == 1)
	{
		std::cout << "You begin moving forward..." << std::endl;
		if (random_encounterChance >= 50)
		{
			// Encounter monster
			CreateMonster();
			std::cout << "A " << currentMonster << " appears! Prepare to fight!" << std::endl;
			Sleep(1000);
			Combat();
		}
		else
		{
			std::cout << "You find nothing of interest." << std::endl;
			Sleep(1000);
			HUD();
			Moving();
		}
	}
	// Rest
	else if (moveOption == 2)
	{
		std::cout << "You rest for the time being." << std::endl;
		if (health >= totalHealth)
		{
			health = totalHealth;
		}
		else
		{
			health += 10 * level;
		}
		std::cout << "You healed by resting. Health is now: " << health << std::endl;
		Sleep(1000);
		HUD();
		Moving();
	}
	// Move backward
	else if (moveOption == 3)
	{
		std::cout << "You begin moving backward..." << std::endl;
		if (random_encounterChance >= 50)
		{
			// Encounter monster
			CreateMonster();
			std::cout << "A " << currentMonster << "appears! Prepare to fight!" << std::endl;
			Sleep(1000);
			Combat();
		}
		else
		{
			std::cout << "You find nothing of interest." << std::endl;
			Sleep(1000);
			HUD();
			Moving();
		}
	}
	else
	{
		std::cout << "Invalid Number" << std::endl;
		Sleep(500);
		Moving();
	}
}

void Combat()
{
	CombatHUD();

	std::uniform_int_distribution<std::size_t> successChance_distribution(1, 100);
	auto random_successChance = successChance_distribution(rng);
	int combatOption;

	int playerDamage = 8 * level / 2;
	int monsterDamage = 4 * monsterLevel / 2;

	// If player turn and both sides not dead
	if (health >= 1 && monsterHP >= 1 && !playerTurnComplete)
	{
		std::cout << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Block" << std::endl;
		std::cout << "3. Flee" << std::endl;
		std::cout << std::endl;

		std::cin >> combatOption;

		// Attack
		if (combatOption == 1)
		{
			std::cout << "You attack and deal " << playerDamage << " damage to the " << currentMonster << "!" << std::endl;
			monsterHP -= playerDamage;
			playerTurnComplete = true;

			Sleep(1000);
			Combat();
		}
		// Block
		else if (combatOption == 2)
		{
			std::cout << "You attempt to block..." << std::endl;

			if (random_successChance >= 1)
			{
				heal = level * 10 / 2;
				std::cout << "You manage to block the attack and regain " << heal << " health!" << std::endl;

				if (health < totalHealth)
					health += heal;

				if (health >= totalHealth)
					health = totalHealth;
			}
			else
				std::cout << "You fail to block the attack and take full damage!" << std::endl;

			playerTurnComplete = true;

			Sleep(1000);
			Combat();
		}
		// Flee
		else if (combatOption == 3)
		{
			std::cout << "You attempt to run!" << std::endl;

			if (random_successChance >= 66)
			{
				std::cout << "You run away!" << std::endl;
				HUD();
				Moving();
			}
			else
			{
				std::cout << "You fail to flee, opening yourself up to an attack!" << std::endl;
				playerTurnComplete = true;

				Sleep(1000);
				Combat();
			}
		}
		else
		{
			std::cout << "Invalid Number" << std::endl;
			Sleep(500);
			Combat();
		}
	}
	// If enemy turn and both sides not dead
	else if (health >= 1 && monsterHP >= 1 && playerTurnComplete)
	{
		std::cout << '\n' << currentMonster << " attacks and deals " << monsterDamage << "!" << std::endl;
		health -= monsterDamage;
		playerTurnComplete = false;

		Sleep(1000);
		Combat();
	}
	// If player dies
	else if (health <= 0)
	{
		health = 0;

		Clear();
		std::cout << "You died!" << '\n' << "You were level: " << level
			<< ". You got killed by: " << currentMonster << std::endl;
		Sleep(2000);
		exit(0);
	}
	// If monster dies
	else if (monsterHP <= 0)
	{
		playerTurnComplete = false; // Set back to player turn for next fight

		monsterHP = 0;

		std::cout << '\n' << "You defeated: " << currentMonster << ". You gain "
			<< monsterXP << " XP!" << std::endl;
		Sleep(2000);
		LevelUp();

		HUD();
		Moving();
	}
}

int main()
{
	// Init
	level = 1;
	xp = 0;
	xpToNextLevel = 76;
	health = 100;
	totalHealth = health;

	CreatePlayer();

	HUD();
	Moving();

	std::cin.get();
	return 0;
}