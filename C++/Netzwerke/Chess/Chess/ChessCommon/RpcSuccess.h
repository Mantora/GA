#pragma once
#include "rpcbase.h"

class RpcSuccess : public RpcBase
{
	public:
		RpcSuccess(void);
		~RpcSuccess(void);

		bool success;
};
