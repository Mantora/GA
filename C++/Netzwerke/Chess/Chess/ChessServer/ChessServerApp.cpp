#include "ChessServerApp.h"

#include <ZeroMqConnector.h>
#include <MySqlConnector.h>

//#include <password.h>

#include <string>
#include <iostream>
#include <time.h>

#include <DummyBoard.h>

#include <RpcMove.h>
#include <RpcRequestBoard.h>
#include <RpcSuccess.h>
#include <RpcSendBoard.h>
#include <RpcLoginResponse.h>
#include <RpcLogin.h>

#include <GameStates.h>

ChessServerApp::ChessServerApp(void) : connector(0), dbConnector(0), board(0), gamestate(GSPreMatch)
{
	//setup random seed 4 login sessionId
	srand( time(0) );
}


ChessServerApp::~ChessServerApp(void)
{
}

bool ChessServerApp::setup()
{
	this->connector = new ZeroMqConnector(ZMQ_REP);

	if( !this->connector->setup() )
	{
		std::cout << "failed set up" << std::endl;
		return false;
	}
	else
	{
		std::cout << "set up" << std::endl;
	}

	if( !this->connector->bind("tcp://*:55555") )
	{
		std::cout << "failed bind" << std::endl;
		return false;
	}
	else
	{
		std::cout << "bind" << std::endl;
	}

	this->dbConnector = new MySqlConnector();
	if( !this->dbConnector->init() )
	{
		std::cout << "failed setting up db connector" << std::endl;
		return false;
	}
	else
	{
		this->dbConnector->connect("127.0.0.1", "root", "2011#myroot!", "titan_dev" );

		std::cout << "connected to MySQL" << std::endl;
	}

	this->board = new DummyBoard();
	this->board->init();
	
	return true;
}

void ChessServerApp::shutdown()
{
	this->board->shutdown();

	delete this->board;
	this->board = NULL;

	this->dbConnector->shutdown();
	delete this->dbConnector;
	this->dbConnector = NULL;

	this->connector->shutdown();
	delete this->connector;
	this->connector = NULL;
}

void ChessServerApp::run()
{
	while( true )
	{
		RpcBase* rpc;
		while( !this->receiveRpc(&rpc) )
		{
			//sleep
		}

		size_t responseSize = 0;
		RpcBase* response = this->handleRpc(rpc, responseSize);
		while( !this->sendResponse(response, responseSize) )
		{
			//sleep
		}
	}


	this->board->shutdown();
	delete this->board;
}

bool ChessServerApp::receiveRpc(RpcBase** rpc)
{
    size_t size;

    return this->connector->receive((void**)rpc, &size);
}

RpcBase* ChessServerApp::handleRpc(RpcBase* rpc, size_t& outSize)
{
    switch(rpc->type)
    {
		case RpcTypeMove: return this->handleRpcMove((RpcMove*)rpc, outSize);
		case RpcTypeRequestBoard: return this->handleRpcRequestBoard((RpcRequestBoard*)rpc, outSize);
		case RpcTypeLogin: return this->handleRpcLogin( (RpcLogin*)rpc, outSize);
	}
    return false;
}

RpcBase* ChessServerApp::handleRpcMove(RpcMove* rpc, size_t& outSize)
{
	RpcSuccess* retVal = new RpcSuccess;

	outSize = sizeof( RpcSuccess );

    retVal->success = this->board->setSquare(rpc->row, rpc->col, rpc->player);

    if( retVal->success )
    {
        this->board->dump();
    }

    return retVal;
}

RpcBase* ChessServerApp::handleRpcRequestBoard(RpcRequestBoard* rpc, size_t& outSize)
{
	RpcSendBoard* response = new RpcSendBoard;
	outSize = sizeof( RpcSendBoard );

	response->fillFromString( this->board->toString() );
   
	return response;
}

RpcBase* ChessServerApp::handleRpcLogin(RpcLogin* rpc, size_t& outSize)
{
	RpcLoginResponse* response = new RpcLoginResponse;
	outSize = sizeof( RpcLoginResponse );

	//login
	//login möglich?
	if( this->players.size() > 2 ||	GSPreMatch != this->gamestate)
	{
		response->playerInfo.token = InvalidTokenType;
		return response;
	}

	//check player name und password
	/***************************MySQL teil*****************************/
	std::string name( rpc->name);
	std::string password( rpc->password );

	MySqlResult outResult;
/*	std::string query = "SELECT * FROM benutzer WHERE name='";
	query.append( name );
	query.append( "' AND SHA(CONCAT('salt','" );
	query.append( password );
	query.append( "')) = passwordHash;" );
*/
	std::string query = "SELECT * FROM benutzer WHERE name='";
	query.append( name );
	query.append( "' AND '" );
	query.append( password );
	query.append( "' = passwort;" );

	//debugging
	std::cout << query << std::endl;

	this->dbConnector->sendQuery(query.c_str(), &outResult );
	if( 1 != outResult.getNumberOfRows() )
	{
		response->playerInfo.token = InvalidTokenType;
		return response;
	}
	/***************************MySQL teil*****************************/

	//login success
	response->playerInfo.sessionId = rand(); //random als ID nicht so gut da deterministisch

	//wenn kein spieler
	if( this->players.empty() )
	{
		response->playerInfo.token = TokenX;
	}
	else
	{
		response->playerInfo.token = TokenO;
	}

	//neuen spieler in die map
	//Anmerkung: so wie assotiatives Array in php
	this->players[ response->playerInfo.token ] = response->playerInfo;

	return response;
}

bool ChessServerApp::sendResponse(RpcBase* response, size_t size)
{
	return this->connector->send(response, size);
	//reservierten speicher wieder freigeben
	delete [] response;
}
