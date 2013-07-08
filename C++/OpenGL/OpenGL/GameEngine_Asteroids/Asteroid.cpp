#include "Asteroid.h"

#include <stdlib.h>
#include <time.h>

int Asteroid::destroyed = 0;
int Asteroid::countALL = 0;

int Asteroid::counterGood = 0;
int Asteroid::counterEvil = 0;

void Asteroid::drawAllAsteroids()
{
	if( !this->isVisible )
	{
		this->child1->drawAllAsteroids();
		this->child2->drawAllAsteroids();
	}
	else
	{
		this->draw();
	}
}

void Asteroid::hit()
{
	if( this->isVisible )
	{
		//Diesen Asteroiden ausblenden
		this->isVisible = false;

		//counter erhöhen
		Asteroid::destroyed++;

		//dieses Asteroid ist zerstört:
		Asteroid::countALL--;

		//den Radius diese Asteroids halbieren
		double newRadius = this->polygone->getRadius()*0.75f;
		
		if( this->isVater )
		{
			this->child1 = createGood(newRadius);
			this->child2 = createEvil(newRadius);
		}
		else
		{
			if( this->isEvil )
			{
				Asteroid::counterEvil--;
				this->child1 = createEvil(newRadius);
				this->child2 = createEvil(newRadius);
			}
			else
			{
				Asteroid::counterGood--;
				this->child1 = createGood(newRadius);
				this->child2 = createGood(newRadius);
			}
		}
	}
}

Asteroid* Asteroid::createGood(double newRadius)
{
	//anzahl böse erhöhen
	Asteroid::counterGood++;

	//Richtung zufällig bestimmen
	srand( (unsigned)time(NULL) );
	int zufall = rand() % 2;
	switch( zufall )
	{
		case 0:	this->negateX(); break;
		case 1:	this->negateY(); break;
	}

	/* Kind 1 */
	//Neues Polygone erzeugen
	Polygone2D* p1 = new Polygone2D();
	p1->makeCircle( newRadius, 4 );
	p1->setColor(0, 1, 0);

	//Neuen Asteoriden erzeugen
	Asteroid* child1 = new Asteroid( p1 );
	child1->setPosition(this->getPosition().x - newRadius, this->getPosition().y );
	child1->setRandomMovement( this->getMovement().x*1.1f, this->getMovement().y*1.1f, this->getBildschirm().x, this->getBildschirm().y);
//toDO: Spawnfix, damit die guten nicht außerhalb der map gespawned werden
	return child1;
}

Asteroid* Asteroid::createEvil(double newRadius)
{
	//anzahl böse erhöhen
	Asteroid::counterEvil++;

	//Richtung zufällig bestimmen
	srand( (unsigned)time(NULL) );
	int zufall = rand() % 2;
	switch( zufall )
	{
		case 0:	this->negateX(); break;
		case 1:	this->negateY(); break;
	}

	/* Kind 2 */
	//Neues Polygone erzeugen
	Polygone2D* p2 = new Polygone2D();
	p2->makeCircle( newRadius, 3 );
	p2->setColor(1,0,0);

	//Neuen Asteoriden erzeugen
	Asteroid* child2 = new Asteroid( p2 );


	double spawnX = this->getPosition().x;
//	if( spawnX + newRadius > this->getBildschirm().x ) spawnX -= newRadius;
//	else spawnX += newRadius;
	
	double spawnY = this->getPosition().y;
//	if( spawnY + newRadius > this->getBildschirm().y ) spawnY -= newRadius;
//	else spawnY += newRadius;

	child2->setPosition(spawnX, spawnY );
	child2->setRandomMovement( this->getMovement().x*1.1f, this->getMovement().y*1.1f, this->getBildschirm().x, this->getBildschirm().y);
	child2->setEvil();

	return child2;
}

void Asteroid::setVater()
{
	this->isVater = true;
}

void Asteroid::setEvil()
{
	this->isEvil = true;
}

void Asteroid::isAnyAsteroidHit(double mouseX, double mouseY)
{
	if( this->isVisible )
	{
		double distance = sqrt( (mouseX - this->getPosition().x)*(mouseX - this->getPosition().x) + (mouseY - this->getPosition().y)*(mouseY - this->getPosition().y) );
		if( distance < this->polygone->getRadius() )
		{
			this->hit();
		}
	}
	else
	{
		this->child1->isAnyAsteroidHit( mouseX, mouseY );
		this->child2->isAnyAsteroidHit( mouseX, mouseY );
	}
}

