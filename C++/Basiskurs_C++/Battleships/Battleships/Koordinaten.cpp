#include "Koordinaten.h"

Koordinaten::Koordinaten(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Koordinaten::Equals(Koordinaten* other)
{
	return( (this->x == other->x) && (this->y == other->y) );
}