#pragma once

#include "DummyBoard.h" //für TokenTyp: schlecht, besser TokenTyp in extra header

class GamePlayer
{
	public:
		GamePlayer(void);
		~GamePlayer(void);

		TokenTypePlayer token;
		int sessionId;

};
