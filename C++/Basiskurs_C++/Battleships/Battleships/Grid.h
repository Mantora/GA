#pragma once

#include <iostream>

#include "Ship.h"
#include "Koordinaten.h"

using namespace std;

#define GRID_MAX_X 10
#define GRID_MAX_Y 10

#define GRID_MAX_SHIPS_COUNT 5

class Grid
{
private:
	int data[GRID_MAX_X][GRID_MAX_Y];
	Koordinaten* currentPosition;
	Ship* ships[GRID_MAX_SHIPS_COUNT]; //Speichern aller Schiffe in diesem Grid

public:
	Grid();
	
	//anzeigefunktionen
	void showGrid();
	void showCurrentPosition();
	void showExplanation_GAME();

	//SET
	void selectRight();
	void selectLeft();
	void selectUp();
	void selectDown();
	void updateSelection();
	void setShip( int ID, Ship* newShip );
	void makeLockedArea( Ship* shipToLock );
	void clearLockedArea( Ship* shipToLock );

	//GET
	Koordinaten* getCurrentPosition();
	int getValueAt( Koordinaten* pos );
	Ship* getShipWithID(int ID);

	//arbeitsfunktionen
	void clear();
	void drawShips();

	void copy( Grid* gridToCopy );
	bool isFieldsFree4Ship( Ship* shipToCheck );
	bool checkOneField( Koordinaten* pos );
	
	//drehung
	bool rotateShip( Ship* shipToRotate );
	bool canRotate_right( Ship* shipToRotate );

	//Game funktionen
	bool fireToGrid( Grid* targetGrid );
	void gotHitOnPosition( Koordinaten* hit );
	Ship* getShipOnPosition( Koordinaten* pos );
	void gotMissOnPosition( Koordinaten* miss );
};
