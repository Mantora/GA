#pragma once

#include <time.h>

#include "polyeder.h"

#include "Spielfeld.h"

#define BALL_MOVMENT_SPEED 0.01f

class Ball : public Polyeder
{
	public:
		Ball( void );
		~Ball( void );

		//zur positionsbestimmung
		vertex* localPosition;
		vertex* v_globalPos;
		vertex* v_direction;

		Matrix* m_movment;
		void doRandomMovement( Spielfeld* spielfeld );

		//public funktion zum richtungsändern bei Spielerkontakt
		void contactPlayer1();
		bool b_hasContactP1;
		void contactPlayer2();
		bool b_hasContactP2;

		//respawnfunktion bei einem punkt
		void respawn();

};
