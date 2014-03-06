#include "DatenPaket.h"

#include <cstring>

 //copykonstruktor
DatenPaket::DatenPaket( const DatenPaket& other )
{
	this->Adresse = other.Adresse;
	
	this->buffer = new unsigned char[ other.uiAnzahlByte ];
	memcpy( this->buffer, other.buffer, other.uiAnzahlByte );

	this->uiAnzahlByte = other.uiAnzahlByte;
}

//f�r ausgehende Daten
DatenPaket::DatenPaket( unsigned char* datenstream, unsigned int bytes )
{
	this->buffer = new unsigned char[ bytes ];
	memcpy( this->buffer, datenstream, bytes );
//	this->buffer = datenstream;
	this->uiAnzahlByte = bytes;
}

//f�r ankommende Daten
DatenPaket::DatenPaket( sockaddr_in von, unsigned char* datenstream, unsigned int bytes )
{
	//Adresse �bergeben
	this->Adresse = von;

	this->buffer = datenstream;

	this->uiAnzahlByte = bytes;
}


DatenPaket::~DatenPaket(void)
{
	
}
