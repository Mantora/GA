#include "Koordinaten.h"

Koordinaten::Koordinaten(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->o = 0.0F;
};

Koordinaten::Koordinaten(Koordinaten* pos)
{
	this->x = pos->x;
	this->y = pos->y;
	this->z = pos->z;

	this->o = 0.0F;
};

Koordinaten::Koordinaten(unsigned char* stream )
{
	x = decodieren( &stream[0] );
	y = decodieren( &stream[3] );
	z = decodieren( &stream[6] );
	o = stream[9];
};

void Koordinaten::anzeigen()
{
	cout.precision(7);
	cout << "\tKoordinaten (" << x << "|" << y << "|" << z << ") o:" << o << endl;
};

void Koordinaten::codieren(unsigned char* stream, int anfang)
{
// Koordinaten verschlüsseln um Bandbreite zu sparen

	static int dez = x;
	stream[0+anfang] = dez >> 8;
	stream[1+anfang] = dez;
	stream[2+anfang] = (x-dez)*256;

	dez = y;
	stream[3+anfang] = dez >> 8;
	stream[4+anfang] = dez;
	stream[5+anfang] = (y-dez)*256;

	dez = z;
	stream[6+anfang] = dez >> 8;
	stream[7+anfang] = dez;
	stream[8+anfang] = (z-dez)*256;

	stream[9+anfang] = o;
};

float Koordinaten::decodieren(unsigned char* stream)
{
	//Aus 3 Byte Float erzeugen
	//	char stream[] = { 117,48,92 }; // entspricht 30000.36F;

	//Decodieren: char[3] --> float
	float f_zahl = (stream[0] << 8);
	f_zahl += stream[1];
	f_zahl += stream[2]*0.00390625F;

//	cout.precision(7);
//	cout << "Decodiert: " << f_zahl << endl;
	return f_zahl;
};
