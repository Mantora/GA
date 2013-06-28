#include <iostream>

#include "Battleships.h"

using namespace std;

int main(void)
{
	system("title CJs Battleships v201306101736");
	Battleships* BSmain = new Battleships();

	//Ein neues Spiel erstellen
	BSmain->createPlayers();

	//P1 schiffe plazieren
	BSmain->setupShips( BSmain->p1 );

	//P2 schiffe plazieren
	BSmain->setupShips( BSmain->p2 );

	//TODEL 4 DEV:
//	BSmain->DEV_createPlayersFULL();
	
	//Alle spieler haben ihre Schiffe gesetzt, GameLoop starten
	Player* winner = BSmain->runGameLoop();

	//Das Spiel ist vorbei, verlierer Ehren
	BSmain->playerWin( winner );

	system("pause");
	return 0;
}
