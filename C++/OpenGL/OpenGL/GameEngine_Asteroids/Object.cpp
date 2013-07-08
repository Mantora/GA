#include "Object.h"

Object::Object(Polygone2D* p)
{
	this->polygone = p;
	this->movement = false;
}

void Object::draw()
{
	this->polygone->draw();

	if( this->movement )
	{
		this->move();
	}
}

void Object::move()
{
	double radius = this->polygone->getRadius();

	if( this->p_mid.x+radius > p_bildschirm.x || this->p_mid.x-radius < 0 ) p_movement.x *= (-1);
	if( this->p_mid.y+radius > p_bildschirm.y || this->p_mid.y-radius < 0 ) p_movement.y *= (-1);

	this->p_mid.x += p_movement.x;
	this->p_mid.y += p_movement.y;
	this->polygone->setPosition( this->p_movement.x, this->p_movement.y );
}

void Object::setPosition(double x, double y)
{
	this->p_mid.x = x;
	this->p_mid.y = y;
	this->polygone->setPosition( x, y );
}

void Object::setMovement(double x, double y)
{
	this->p_movement.x = x;
	this->p_movement.y = y;
	this->movement = true;
}

Point Object::getMovement()
{
	return this->p_movement;
}

Point Object::getBildschirm()
{
	return this->p_bildschirm;
}

Point Object::getMid()
{
	return this->p_mid;
}

Point Object::getPosition()
{
	return p_mid;
}

void Object::setID(int id)
{
	this->ID = id; 
}

int Object::getID()
{
	return this->ID; 
}

void Object::setRandomMovement(double speedX, double speedY, double maxX, double maxY)
{
	this->movement = true;

	this->p_movement.x = speedX;
	this->p_movement.y = speedY;

	this->p_bildschirm.x = maxX;
	this->p_bildschirm.y = maxY;
}

void Object::negateX()
{
	this->p_movement.x *= (-1);
}

void Object::negateY()
{
	this->p_movement.y *= (-1);
}

/*
bool Object::hit( Object* ziel )
{
	//vorn															//hinten
	if( (this->p_mid.x) > ziel->getPosition().x && (ziel->getPosition().x+ziel->polygone->getMaxXPoliLenght()) > (this->p_mid.x) )
	{
		//Kollision auf der X Achse
		if( (this->p_mid.y) > ziel->getPosition().y && (ziel->getPosition().y+ziel->polygone->getMaxYPoliLenght()) > (this->p_mid.y) )
		{
			//Kollision auf der Y Achse
			return true;
			//negateY();
		}
	}
	return false;
}
*/
