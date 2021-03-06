//Ein Schiff besteht aus einzelteilen
#pragma once
#include <iostream>

#include "Part.h"
#include "Koordinaten.h"

using namespace std;

#define SHIP_MAX_PARTS 5

class Ship
{
private:
	int size;
	int partsHitten;
	Part* parts[SHIP_MAX_PARTS];
	int maxParts;

public:
	Ship( int size, Koordinaten* k);

	//alle koordinaten der Teile
	Koordinaten* getKoordinatenFromHead();
	bool hasNextPart(int index);
	Koordinaten* getKoordinatenFromPart( int partNumber );

	//GET
	int partsCount();

	//SET
	void setPart(int partIndex, Koordinaten* newPos);

	//Drehung
	void rotate_right();
	void rotate_left();

	//Hit
	void hitPartWithPos( Koordinaten* pos );
	bool isShipDead();
};
