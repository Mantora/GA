#pragma once

#include <iostream>
#include <conio.h> //4 input

#include "Player.h"

class Battleships
{
private:
	Player* p1;
	Player* p2;

public:
	Battleships();

	//1: SetUp function
	void createPlayers();
	void setupShipsPlayer1();
	void setupShipsPlayer2();

	//2: Game Scene funktions
	Player* runGameLoop();

	//3: GameOver Scene
	void playerWin( Player* winner );

	//ToDel 4 DEV:
	void DEV_createPlayersFULL();
};
