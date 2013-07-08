#include "Object.h"

Object::Object(Polygone* p)
{
	this->polygone = p;
	this->movement = false;
}

void Object::draw()
{
	this->polygone->draw(p_position.x, p_position.y);

	if( this->movement )
	{
		if( this->p_position.y+10 > this->p_bildschirm.y || this->p_position.y < 0)
			p_movement.y *= (-1);

		this->p_position.x += p_movement.x;
		this->p_position.y += p_movement.y;
	}
}

void Object::setPosition(double x, double y)
{
	this->p_position.x = x;
	this->p_position.y = y;
}

Point Object::getPosition()
{
	return p_position;
}

void Object::setID(int id)
{
	this->ID = id; 
}

int Object::getID()
{
	return this->ID; 
}

void Object::setRandomMovement(double x, double y, double bildX, double bildY)
{
	this->movement = true;

	this->p_movement.x = x;
	this->p_movement.y = y;

	this->p_bildschirm.x = bildX;
	this->p_bildschirm.y = bildY;
}
void Object::addPosition(double x, double y)
{
	this->p_position.x += x;
	this->p_position.y += y;
}

void Object::negateX()
{
	this->p_movement.x *= (-1);
}

void Object::negateY()
{
	this->p_movement.y *= (-1);
}

bool Object::hit( Object* ziel )
{
								//vorn															//hinten
	if( (this->p_position.x) > ziel->getPosition().x && (ziel->getPosition().x+ziel->polygone->getMaxXPoliLenght()) > (this->p_position.x) )
	{
		//Kollision auf der X Achse
		if( (this->p_position.y) > ziel->getPosition().y && (ziel->getPosition().y+ziel->polygone->getMaxYPoliLenght()) > (this->p_position.y) )
		{
			//Kollision auf der Y Achse
			return true;
			//negateY();
		}
	}
	return false;
}
