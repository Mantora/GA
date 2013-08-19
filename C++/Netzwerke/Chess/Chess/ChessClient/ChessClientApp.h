#pragma once

class ZeroMqConnector;

#include <DummyBoard.h>
#include <GameStates.h>

class RpcBase;
class RpcSuccess;
class RpcSendBoard;
class GamePlayer;
class RpcLoginResponse;

class ChessClientApp
{
	public:
		ChessClientApp(void);
		~ChessClientApp(void);

		void run();

		bool sendLoginRequest( const std::string& name, const std::string& password );
		bool sendMove(int row, int col, TokenTypePlayer player);
		bool requestBoard();

		bool recieveResponse(RpcBase** response);
		bool handleResponse( const RpcBase* response );
		bool handleLoginResponse( RpcLoginResponse* response );

		bool handleRpcSuccess(RpcSuccess* response);
		bool handleRpcSendBoard( RpcSendBoard* response );

	private:
		ZeroMqConnector* connector;

		DummyBoard* board;
		GameState gamestate;
		GamePlayer* player;
};

