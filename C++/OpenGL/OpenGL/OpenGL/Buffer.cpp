#include "Buffer.h"

#include <iostream>

using namespace std;

Buffer::Buffer( pixel bildschirmPixel)
{
	this->bildschirm = bildschirmPixel;

	currentArrayIndex = 0;
	maxIndex = 0;
	side = 0;
}

Buffer::Buffer()
{
	currentArrayIndex = 0;
	maxIndex = 0;
	side = 0;
}


void Buffer::updatePos( Vector2* v)
{
	for( int i = 0; i < maxIndex; i++)
	{
		this->array[i].x += v->x;
		this->array[i].y += v->y;
	}
}

void Buffer::createCube( int side, MyColor col )
{
	this->side = side;
	this->col = col;
	for( int x = 0; x < side; x++)
	{
		for( int y = 0; y < side; y++)
		{
			//position
			array[this->currentArrayIndex].x = x-(0.5*side);
			array[this->currentArrayIndex].y = y-(0.5*side);
			array[this->currentArrayIndex].z = -10;

			//index erhöhen
			this->currentArrayIndex++;
		}
	}
	//letzen index für die ausgabe merken
	this->maxIndex = this->currentArrayIndex;
}

void Buffer::draw( void )
{
	for( int i = 0; i < maxIndex; i++)
	{
		glColor3d( this->col.r, this->col.g, this->col.b);
//		glVertex2d( this->array[i].x, this->array[i].y );
		glVertex3d( this->array[i].x, this->array[i].y, this->array[i].z);
	}
	
/*	if( (pos.x+side) > bildschirm.x || pos.x < 0 )
	{
		speed.x *= (-1);
	}
	if( (pos.y+side) > bildschirm.y || pos.y < 0 )
	{
		speed.y *= (-1);
	}
*/
//	updatePos(speed.x, speed.y);
}
