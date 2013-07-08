#include "Object.h"

class Asteroid : public Object
{
private:
	Asteroid* child1;
	Asteroid* child2;
	bool isVisible;
	bool isVater;
	bool isEvil;
	Asteroid* createEvil(double newRadius);
	Asteroid* createGood(double newRadius);

public:
	Asteroid( Polygone2D* p ) : Object( p )
	{
		this->isVisible = true;
		this->isVater = false;
		this->isEvil = false;
		Asteroid::countALL++;

	}
	void hit();
	void isAnyAsteroidHit(double mousX, double mouseY);
	void drawAllAsteroids();
	void moveAllAsteroids();

	//
	void setVater();
	void setEvil();

	/* static Variables */
	static int countALL;
	static int counterGood;
	static int counterEvil;
	static int destroyed;
};

