#include <gl\glew.h>


#include "matrix.h"

class Landscape
{
	private:
		int size;
		vertex* points;
		//variable zum speichern der verschiebung mit "matrix.translate"
		vertex* translation;

	public:
		Landscape( int size );
		~Landscape();

		//anzeigefunktionen
		void draw();

		//matrixfunktionen
		void updatePos( matrix m );

		//funktionen zum speichern der verschiebung
		void setTranslation( double x, double y, double z );
		vertex* getTranslation();
};
