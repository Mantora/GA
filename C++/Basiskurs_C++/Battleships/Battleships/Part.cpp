#include "Part.h"

Part::Part( Koordinaten* k)
{
	this->k = k;
	this->hit = false;
}
	
//GET
Koordinaten* Part::getKoordinaten()
{
	return this->k;
}

//SET
void Part::setKoordinaten( Koordinaten* newKoordinaten)
{
	this->k = newKoordinaten;
}

void Part::setHit( bool gotHitten )
{
	this->hit = gotHitten;
}