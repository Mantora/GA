#pragma once

#include "polyeder.h"

#include "matrix.h"

class Spielfeld : public Polyeder
{
	public:
		vertex* v_globalPos;

		vertex* v_boundsOHL;
		vertex* v_boundsOVL;
		vertex* v_boundsOVR;
		vertex* v_boundsOHR;

		vertex* v_boundsUHL;
		vertex* v_boundsUVL;
		vertex* v_boundsUVR;
		vertex* v_boundsUHR;

		Spielfeld( void );
		~Spielfeld( void );

		//funktion zum updaten der Bounds bei drehung
		void updateBounds( Matrix m );
};
