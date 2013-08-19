#pragma once
#include "rpcbase.h"

class RpcLogin : public RpcBase
{
	public:
		RpcLogin(void);
		~RpcLogin(void);

		char name[33];
		char password[33];
};
