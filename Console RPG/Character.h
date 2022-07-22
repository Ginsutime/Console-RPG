#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

class Character
{
public:
	Character();

	std::string name, race, sex;
	std::vector<std::string> playerRace;
	int level, xp, health, totalHealth, xpToNextLevel, restHeal, blockHeal, playerDamage;
	bool playerTurnComplete;

	void CreatePlayer();
	void ValidateRace();
	void ValidateSex();
};