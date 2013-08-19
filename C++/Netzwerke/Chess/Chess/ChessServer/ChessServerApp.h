#pragma once

#include <map>
#include "GamePlayer.h"
#include "GameStates.h"

class ZeroMqConnector;
class MySqlConnector;

class DummyBoard;

class RpcBase;
class RpcMove;
class RpcRequestBoard;
class RpcLogin;

class ChessServerApp
{
	public:
		ChessServerApp(void);
		~ChessServerApp(void);

		bool setup();
		void shutdown();

		void run();

	private:
		bool receiveRpc(RpcBase** rpc);
		RpcBase* handleRpc(RpcBase* rpc, size_t& outSize);
		bool sendResponse(RpcBase* response, size_t size);

		RpcBase* handleRpcMove(RpcMove* rpc, size_t& outSize);
		RpcBase* handleRpcRequestBoard(RpcRequestBoard* rpc, size_t& outSize);
		RpcBase* handleRpcLogin(RpcLogin* rpc, size_t& outSize);

		ZeroMqConnector* connector;
		MySqlConnector* dbConnector;

		DummyBoard* board;
		GameState gamestate;

		//mapping von einem wert auf einen anderen
		//Wie bei meinem Server: welcher hat welche ID und spielerId (das bool array)
		//map<KEY,WERT>
		std::map<TokenTypePlayer, GamePlayer> players;

};

