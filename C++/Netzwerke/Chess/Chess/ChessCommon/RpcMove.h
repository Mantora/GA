#pragma once

#include "RpcBase.h"
#include "DummyBoard.h"

class RpcMove : public RpcBase
{
	public:
		RpcMove(void);
		virtual ~RpcMove(void);

		int row;
		int col;
		TokenTypePlayer player;
};

