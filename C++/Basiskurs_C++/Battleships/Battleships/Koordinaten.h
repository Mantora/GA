#pragma once

class Koordinaten
{
public:
	Koordinaten( int x, int y);
	int x;
	int y;

	//vergleich von dieser Klasse
	bool Equals(Koordinaten* other); 
};
