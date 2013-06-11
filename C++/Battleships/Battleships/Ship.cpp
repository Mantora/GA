#include "Ship.h"

Ship::Ship(int size, Koordinaten* k)
{
	this->maxParts = SHIP_MAX_PARTS;
	this->partsHitten = 0;

	//parts[] initialisieren:
	for( int init = 0; init < 5; init++)
		this->parts[init] = NULL;

	this->size = size;

	this->parts[0] = new Part( k );

	for( int i = 1; i < size; i++)
		parts[i] = new Part( new Koordinaten( k->x+i, k->y) );
}

//alle koordinaten der Teile
Koordinaten* Ship::getKoordinatenFromHead()
{
	return this->parts[0]->getKoordinaten();
}

bool Ship::hasNextPart(int index)
{
	//gibt es diesen Part ?
	if( index < this->size )
	{
		//Frage: Hier auf gesetzten pointer prüfen notwendig ?
		//sicherheitshalber ja:
		if( this->parts[index] != NULL )
			return true;
		else
			return false;
	}
	else
		return false;
}

Koordinaten* Ship::getKoordinatenFromPart( int partNumber )
{
	return this->parts[ partNumber ]->getKoordinaten();
}

//GET
int Ship::partsCount()
{
	return this->size;
}

//SET
void Ship::setPart(int partIndex, Koordinaten* newPos)
{
	this->parts[partIndex]->setKoordinaten( newPos );

}

//Drehung
void Ship::rotate_right()
{
	//punkt ermitteln, von dem aus sich gedreht wird
	Koordinaten* ursprung = this->parts[0]->getKoordinaten();

	int index = 1;
	while( this->hasNextPart(index) )
	{
		Koordinaten* posToRotate = parts[index]->getKoordinaten();

		if( posToRotate->x > ursprung->x )
		{
			//HSSS

			//H
			//S
			//S
			//S
		
			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x, ursprung->y+index );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}
		else if( posToRotate->y > ursprung->y )
		{
			//H
			//S
			//S
			//S

			//SSSH

			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x-index, ursprung->y );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}
		else if( posToRotate->x < ursprung->x )
		{
			//SSSH

			//S
			//S
			//S
			//H

			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x, ursprung->y-index );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}
		else
		{
			//S
			//S
			//S
			//H

			//HSSS

			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x+index, ursprung->y );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}

		index++;
	}
}

void Ship::rotate_left()
{
	//punkt ermitteln, von dem aus sich gedreht wird
	Koordinaten* ursprung = this->parts[0]->getKoordinaten();

	int index = 1;
	while( this->hasNextPart(index) )
	{
		Koordinaten* posToRotate = parts[index]->getKoordinaten();

		if( posToRotate->x > ursprung->x )
		{
			//HSSS

			//S
			//S
			//S
			//H
		
			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x, ursprung->y-index );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}
		else if( posToRotate->y < ursprung->y )
		{
			//S
			//S
			//S
			//H

			//SSSH

			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x-index, ursprung->y );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}
		else if( posToRotate->x < ursprung->x )
		{
			//SSSH

			//H
			//S
			//S
			//S

			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x, ursprung->y+index );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}
		else
		{
			//H
			//S
			//S
			//S

			//HSSS

			Koordinaten* newKoordinaten = new Koordinaten( ursprung->x+index, ursprung->y );

			this->parts[index]->setKoordinaten( newKoordinaten );
		}

		index++;
	}
}

//Hit
void Ship::hitPartWithPos( Koordinaten* pos )
{
	for( int i = 0; i < this->size; i++ )
	{
		if( pos->Equals( parts[i]->getKoordinaten() ) )
		{
			parts[i]->setHit( true );
			this->partsHitten++;
			break;
		}
	}
}

bool Ship::isShipDead()
{
	return( this->partsHitten == this->size );
}
