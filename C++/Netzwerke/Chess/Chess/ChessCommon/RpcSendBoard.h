#pragma once

#include "rpcbase.h"

#include <string>

class RpcSendBoard : public RpcBase
{
	public:
		RpcSendBoard(void);
		~RpcSendBoard(void);

		void fillFromString( const std::string& s);
		std::string getAsString() const;

		char boardAsString[10];
};
