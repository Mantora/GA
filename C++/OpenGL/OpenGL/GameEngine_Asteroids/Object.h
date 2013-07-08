#include "Polygone2D.h"

class Object
{
	private:
		int ID; //Id um doppelte Kollision mit dem SPielerschl‰ger auszuschlieﬂen
		bool movement;
		Point p_mid;
		Point p_movement; //Bewegungsrichtung
		Point p_bildschirm; //Bildschirmabmessungen

	public:
		Polygone2D* polygone;

		Object( Polygone2D* p);
		void draw();
		
		Point getMid();
		Point getPosition();
		void setPosition(double x, double y);
		void setMovement(double x, double y);
		Point getMovement();
		Point getBildschirm();
		void move();

		int getID();
		void setID(int id);

		void setRandomMovement(double speedX, double speedY, double maxX, double maxY);
		void negateX();
		void negateY();

		bool hit( Object* ziel );
};
