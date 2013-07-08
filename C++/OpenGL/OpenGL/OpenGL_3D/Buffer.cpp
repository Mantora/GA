#include "Buffer.h"
#include "matrix.h"

using namespace std;

Buffer::Buffer( pixel bildschirmPixel)
{
	this->bildschirm = bildschirmPixel;

	currentpositionIndex = 0;
	maxIndex = 0;
}

Buffer::Buffer()
{
	currentpositionIndex = 0;
	maxIndex = 0;
}


void Buffer::updatePos( Vector3* v)
{
	for( int i = 0; i < maxIndex; i++)
	{
		this->position[i].x += v->x;
		this->position[i].y += v->y;
		this->position[i].z += v->z;
	}
}

void Buffer::updatePos( matrix m )
{
	for( int i = 0; i < this->maxIndex; i++)
	{
		this->position[i] = m * this->position[i];
	}
}

void Buffer::createSphere( float durchmesser, MyColor col )
{
	this->col = col;
	durchmesser *= 2;

	for( int x = 0; x < durchmesser; x++)
	{
		for( int y = 0; y < durchmesser; y++)
		{
			//position
			if(  sqrt( (x-durchmesser/2)*(x-durchmesser/2) + (y-durchmesser/2)*(y-durchmesser/2) ) < durchmesser/2 )
			{
				//position
				this->position[this->currentpositionIndex].x = x-(0.5f*durchmesser);
				this->position[this->currentpositionIndex].y = y-(0.5f*durchmesser);
				this->position[this->currentpositionIndex].z = 0;

				//index erhöhen
				this->currentpositionIndex++;
			}
		}
	}
	//letzen index für die ausgabe merken
	this->maxIndex = this->currentpositionIndex;
}

void Buffer::createCube( int side, MyColor col )
{
	this->col = col;
	for( int x = 0; x < side; x++)
	{
		for( int y = 0; y < side; y++)
		{
			//position
			this->position[this->currentpositionIndex].x = x-(0.5f*side);
			this->position[this->currentpositionIndex].y = y-(0.5f*side);
			this->position[this->currentpositionIndex].z = 0;

			//index erhöhen
			this->currentpositionIndex++;
		}
	}
	//letzen index für die ausgabe merken
	this->maxIndex = this->currentpositionIndex;
}

void Buffer::draw( void )
{
	for( int i = 0; i < maxIndex; i++)
	{
		glColor3d( this->col.r, this->col.g, this->col.b);
		glVertex3d( this->position[i].x, this->position[i].y, this->position[i].z);
	}
}
