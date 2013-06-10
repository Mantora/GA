#include <iostream>

#include "Battleships.h"

using namespace std;

int main(void)
{
	system("title CJs Battleships v201306082222");
	Battleships* game = new Battleships();

	//Ein neues Spiel erstellen
	game->createPlayers();

	//P1 schiffe plazieren
	game->setupShipsPlayer1();

	//P2 schiffe plazieren
	game->setupShipsPlayer2();

	//TODEL 4 DEV:
//	game->DEV_createPlayersFULL();
	
	//Alle spieler haben ihre Schiffe gesetzt, GameLoop starten
	Player* winner = game->runGameLoop();

	//Das Spiel ist vorbei, verlierer Ehren
	game->playerWin( winner );

	system("pause");
	return 0;
}
