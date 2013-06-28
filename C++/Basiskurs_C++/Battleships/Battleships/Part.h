//Ein teil eines Schiffes
#pragma once
#include <iostream>

#include "Koordinaten.h"

using namespace std;

class Part
{
private:
	Koordinaten* k;
	bool hit;

public:
	Part(Koordinaten* k);

	//GET
	Koordinaten* getKoordinaten();

	//SET
	void setKoordinaten( Koordinaten* newKoordinaten);
	void setHit( bool gotHitten );
};
