#pragma once
#include <iostream>

#include "Grid.h"

#include "Inputs.h"
#include <conio.h> //4 input

class Player
{
private:
	char name[32];
	Grid* ShipGrid;
	Grid* SelectionGrid;
	bool ready;
	int x,y;
	Ship* ship_two1;
	Ship* ship_two2;
	Ship* ship_three;
	Ship* ship_four;
	Ship* ship_five;
	//Variabeln für Setup
	int currentSelectedShip;
	bool allShipsPlaced;

public:
	Player();
	void init();

	//funktionen zum Anzeigen
	void showSelectionGrid();
	void showShipGrid();

	//GET
	bool isReady();
	char* getName();
	Grid* getSelectionGrid();
	Grid* getShipGrid();

	//SET
	void setReady( bool newState );

	//input
	void handleInput_setup( int KB_code );

	//Setup functions
	void showShips4Setup();
	void confirmSelection();
	void updateCurrentSelectedShip();

	//Game functions
	void makeTurn( int gameRound );
	void handleInput_game( int KB_code );
	void showGameGUI();
	bool allShipsSunk();

	//Feedback funktions
	void doFeedback_NORMAL();
	void doFeedback_OK();
	void doFeedback_ERROR();

	//ToDelet 4 Development
	Player( char* );

};
