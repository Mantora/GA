#include "Polygone.h"

class Object
{
	private:
		int ID; //Id um doppelte Kollision mit dem SPielerschl‰ger auszuschlieﬂen
		bool movement;
		Point p_position;
		Point p_movement; //Bewegungsrichtung
		Point p_bildschirm;

	public:
		Polygone* polygone;

		Object( Polygone* p);
		void draw();

		Point getPosition();
		void setPosition(double x, double y);

		int getID();
		void setID(int id);

		void setRandomMovement(double x, double y, double bildX, double bildY);
		void addPosition(double x, double y);
		void negateX();
		void negateY();

		bool hit( Object* ziel );
};
