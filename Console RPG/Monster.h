#pragma once
#include <vector>
#include <string>

class Monster
{
public:
	Monster();

	int monsterDamage, monsterHP, monsterXP, monsterLevel, levelTracker;
	std::vector<std::string> monsterName;
	std::string currentMonster;

	void CreateMonster();
};
