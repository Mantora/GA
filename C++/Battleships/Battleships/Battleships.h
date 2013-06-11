#pragma once

#include <iostream>
#include <conio.h> //4 input

#include "Player.h"

class Battleships
{
public:
	//Player Public ??!
	Player* p1;
	Player* p2;

	Battleships();

	//1: SetUp function
	void createPlayers();
	void setupShips( Player* currentPlayer );

	//2: Game Scene funktions
	Player* runGameLoop();

	//3: GameOver Scene
	void playerWin( Player* winner );

	//ToDel 4 DEV:
	void DEV_createPlayersFULL();
};
