#include "Character.h"

void CharacterPos(short c, short r) {
	COORD xy;
	xy.X = c;
	xy.Y = r;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void CharacterClear() {
	CharacterPos(0, 0);
	for (int i = 0; i < 100; i++)
	{
		std::cout << std::string(100, '\n');
	}
	CharacterPos(0, 0);
}

Character::Character()
{
	name = " "; race = " "; sex = " ";
	playerRace = { "Gnome", "Elf", "Human", "Aasimar", "Goliath" };
	level = 1; xp = 0; xpToNextLevel = 76; 
	health = totalHealth; totalHealth = 100; 
	restHeal = 10 * level; blockHeal = level * 10 / 2;
	playerDamage = 8 * level / 2;
	playerTurnComplete = false;
}

void Character::CreatePlayer()
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
		CharacterClear();
	}
}

void Character::ValidateRace()
{
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
			health = 60; totalHealth = health;
			correctRaceInput = true;
			break;
		case 2:
			race = playerRace[1];
			health = 80; totalHealth = health;
			correctRaceInput = true;
			break;
		case 3:
			race = playerRace[2];
			health = 100; totalHealth = health;
			correctRaceInput = true;
			break;
		case 4:
			race = playerRace[3];
			health = 120; totalHealth = health;
			correctRaceInput = true;
			break;
		case 5:
			race = playerRace[4];
			health = 140; totalHealth = health;
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

void Character::ValidateSex()
{
	char sexInput;
	bool correctSexInput = false;

	std::cout << "Enter Letter Denoting Character Sex (M or F): ";
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
			std::cout << "Invalid answer for sex. Try again: ";
			sexInput = std::cin.get();
			std::cin.ignore(INT_MAX, '\n');
			break;
		}
	}
}