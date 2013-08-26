#pragma once

#include <iostream>

#include "polyeder.h"

#include "Ball.h"

class Spieler2 : public Polyeder
{
	private:
		float width;
		float hight;
		float deep;

	public:
		Spieler2( void );
		~Spieler2( void );

		//zur positionsbestimmung
		vertex* localPosition;
		vertex* v_globalPos;

		//BOT: auto follow ball
		void PerfectBotMovement( Ball* ball );

		//funktion zum überprüfen, ob der ball am spieler abprallt
		void check4BallContakt( Ball* ball );

		//punkte dieses spielers
		int points;
		int ballHits;

		bool isBot;
};
