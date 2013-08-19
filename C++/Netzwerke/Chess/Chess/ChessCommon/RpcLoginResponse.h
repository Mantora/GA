#pragma once
#include "rpcbase.h"

#include "GamePlayer.h"

class RpcLoginResponse : public RpcBase
{
	public:
		RpcLoginResponse(void);
		~RpcLoginResponse(void);

		GamePlayer playerInfo;
};
