#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <Windows.h>
#include "Character.h"
#include "Monster.h"

void HUD();
void CombatHUD();
void LevelUp();
void Moving();
void Combat();

Character character;
Monster monster;

std::random_device dev;
std::mt19937 rng(dev());

void ConsolePos(short c, short r) {
	COORD xy;
	xy.X = c;
	xy.Y = r;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void ConsoleClear() {
	ConsolePos(0, 0);
	for (int i = 0; i < 100; i++)
	{
		std::cout << std::string(100, '\n');
	}
	ConsolePos(0, 0);
}

void HUD()
{
	Sleep(500);
	ConsoleClear();
	std::cout << "|" << std::left << std::setw(7) << "Name: " << std::setw(12) << character.name <<
		"|" << std::setw(8) << "Health: " << std::setw(11) << character.health << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(7) << "Race: " << std::setw(12) << character.race <<
		"|" << std::setw(8) << "Sex: " << std::setw(11) << character.sex << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(7) << "Level: " << std::setw(12) << character.level <<
		"|" << std::setw(8) << "XP: " << std::setw(11) << character.xp << "|" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "|" << std::internal << std::setw(30) << "XP Needed To Level Up: " <<
		character.xpToNextLevel << std::right << std::setw(8) << "|" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

void CombatHUD()
{
	Sleep(500);
	ConsoleClear();
	std::cout << "|" << std::left << std::setw(8) << "Name: " << std::setw(12) << character.name <<
		std::setw(7) << "|" << std::right << std::setw(16) << "Monster Name: " <<
		std::setw(6) << monster.currentMonster << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(8) << "Health: " << std::setw(12) << character.health <<
		std::setw(7) << "|" << std::right << std::setw(16) << "Monster Health: " <<
		std::setw(6) << monster.monsterHP << "|" << std::endl;
	std::cout << "|" << std::left << std::setw(8) << "Level: " << std::setw(12) << character.level <<
		std::setw(7) << "|" << std::right << std::setw(16) << "Monster Level: " <<
		std::setw(6) << monster.monsterLevel << "|" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
}

void LevelUp()
{
	character.xp += monster.monsterXP;

	if (character.xp >= character.xpToNextLevel)
	{
		character.level++; monster.levelTracker++;
		character.xpToNextLevel = character.xpToNextLevel * 3 / 2;
		character.totalHealth += 20; character.health += 20;

		std::cout << "You have leveled up and are now level " << character.level
			<< ". Your total health has increased 20 points to " << character.totalHealth << "!" << std::endl;

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
			monster.CreateMonster();
			std::cout << "A " << monster.currentMonster << " appears! Prepare to fight!" << std::endl;
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

		if (character.health < character.totalHealth)
			character.health += character.restHeal;

		if (character.health >= character.totalHealth)
			character.health = character.totalHealth;

		std::cout << "You healed by resting. Health is now: " << character.health << std::endl;
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
			monster.CreateMonster();
			std::cout << "A " << monster.currentMonster << " appears! Prepare to fight!" << std::endl;
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
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Invalid input. Try again with a proper #." << std::endl;

		Sleep(1000);
		HUD();
		Moving();
	}
}

void Combat()
{
	CombatHUD();

	std::uniform_int_distribution<std::size_t> successChance_distribution(1, 100);
	auto random_successChance = successChance_distribution(rng);
	int combatOption;

	// If player turn and both sides not dead
	if (character.health >= 1 && monster.monsterHP >= 1 && !character.playerTurnComplete)
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
			std::cout << "You attack and deal " << character.playerDamage << " damage to the " << monster.currentMonster << "!" << std::endl;
			monster.monsterHP -= character.playerDamage;
			character.playerTurnComplete = true;

			Sleep(1000);
			Combat();
		}
		// Block
		else if (combatOption == 2)
		{
			std::cout << "You attempt to block..." << std::endl;

			if (random_successChance >= 1)
			{
				std::cout << "You manage to block the attack and regain " << character.blockHeal << " health!" << std::endl;

				if (character.health < character.totalHealth)
					character.health += character.blockHeal;

				if (character.health >= character.totalHealth)
					character.health = character.totalHealth;
			}
			else
				std::cout << "You fail to block the attack and take full damage!" << std::endl;

			character.playerTurnComplete = true;

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
				character.playerTurnComplete = true;

				Sleep(1000);
				Combat();
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid input. Try again with a proper #." << std::endl;

			Sleep(1000);
			Combat();
		}
	}
	// If enemy turn and both sides not dead
	else if (character.health >= 1 && monster.monsterHP >= 1 && character.playerTurnComplete)
	{
		monster.monsterDamage = 4 * monster.monsterLevel / 2;

		std::cout << '\n' << monster.currentMonster << " attacks and deals " << monster.monsterDamage << "!" << std::endl;
		character.health -= monster.monsterDamage;
		character.playerTurnComplete = false;

		Sleep(1000);
		Combat();
	}
	// If player dies
	else if (character.health <= 0)
	{
		character.health = 0;

		ConsoleClear();
		std::cout << "You died!" << '\n' << "You were level: " << character.level
			<< ". You got killed by: " << monster.currentMonster << std::endl;
		Sleep(2000);
		exit(0);
	}
	// If monster dies
	else if (monster.monsterHP <= 0)
	{
		character.playerTurnComplete = false; // Set back to player turn for next fight

		monster.monsterHP = 0;

		std::cout << '\n' << "You defeated: " << monster.currentMonster << ". You gain "
			<< monster.monsterXP << " XP!" << std::endl;
		Sleep(2000);
		LevelUp();

		HUD();
		Moving();
	}
}

int main()
{
	character.CreatePlayer();

	HUD();
	Moving();

	std::cin.get();
	return 0;
}