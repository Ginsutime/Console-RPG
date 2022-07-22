#include "Monster.h"
#include <random>

Monster::Monster()
{
	monsterHP = 0; monsterXP = 0; monsterLevel = 0, levelTracker = 1; monsterDamage = 0;
	std::string currentMonster = " ";
	monsterName = { "Goblin", "Dwarf", "Ogre", "Witch", "Demon", "Wizard" };
}

void Monster::CreateMonster()
{
	std::random_device dev;
	std::mt19937 rng(dev());

	std::uniform_int_distribution<std::size_t> monsterName_distribution(0, monsterName.size() - 1);
	auto random_monsterName = monsterName_distribution(rng);
	std::uniform_int_distribution<std::size_t> monsterHP_distribution(20, 50);
	auto random_monsterHP = monsterHP_distribution(rng);
	std::uniform_int_distribution<std::size_t> monsterLevel_distribution(0, 2);
	auto random_monsterLevel = monsterLevel_distribution(rng);

	currentMonster = monsterName[random_monsterName];

	monsterHP = random_monsterHP;
	monsterLevel = random_monsterLevel + levelTracker;
	monsterXP = monsterHP;
}