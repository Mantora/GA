#include "RpcSendBoard.h"

RpcSendBoard::RpcSendBoard( void ) : RpcBase( RpcTypeSendBoard )
{

}

RpcSendBoard::~RpcSendBoard( void )
{

}

void RpcSendBoard::fillFromString( const std::string& s)
{
	for( int i = 0; i < 9; i++ )
	{
		this->boardAsString[i] = s[i];
	}

	this->boardAsString[10] = 0;
}

std::string RpcSendBoard::getAsString() const
{
	return std::string( this->boardAsString );
}
