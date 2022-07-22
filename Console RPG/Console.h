#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <Windows.h>

void HUD();
void CombatHUD();
void LevelUp();

void CreatePlayer();
void ValidateRace();
void ValidateSex();
void CreateMonster();

void Moving();
void Combat();

void Pos(short c, short r) {
	COORD xy;
	xy.X = c;
	xy.Y = r;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void Clear() {
	Pos(0, 0);
	for (int i = 0; i < 100; i++)
	{
		std::cout << std::string(100, '\n');
	}
	Pos(0, 0);
}