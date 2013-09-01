#include "ChessClientApp.h"

#include <ZeroMqConnector.h>
#include <string>
#include <iostream>

#include <DummyBoard.h>
#include <RpcSendBoard.h>
#include <RpcMove.h>
#include <RpcRequestBoard.h>
#include <RpcSuccess.h>
#include <RpcLogin.h>
#include <RpcLoginResponse.h>

ChessClientApp::ChessClientApp(void) : connector(0) , board(0), gamestate(InvalidGameState), player(0)
{
}


ChessClientApp::~ChessClientApp(void)
{

}

void ChessClientApp::run()
{
	this->connector = new ZeroMqConnector(ZMQ_REQ);

	if ( !this->connector->setup() )
	{
		std::cout << "failed set up" << std::endl;
	}
	else
	{
		std::cout << "set up" << std::endl;
	}

	if ( !this->connector->connect("tcp://127.0.0.1:55555") )
	{
		std::cout << "failed connect" << std::endl;
	}
	else
	{
		std::cout << "connect" << std::endl;
	}

	//handle login
	while( player == NULL )
	{
		std::string name;
		std::string password;

		std::cout << "Enter name: ";
		std::cin >> name;

		std::cout << "Enter Password: ";
		std::cin >> password;

		while( !sendLoginRequest(name,password) )
		{}

		// Wait for response
		RpcLoginResponse* response;
		while( !this->recieveResponse((RpcBase**)&response) )
		{}
		this->handleLoginResponse( response );
	}
	std::cout << "Logged in as player " << (int)this->player->token << std::endl;

  // setup board
  this->board = new DummyBoard();
  this->board->init();;

  TokenTypePlayer currentPlayer = TokenO;
  bool quitRequest = false;
  while (!quitRequest)
  {
    switch(currentPlayer)
    {
      case TokenO: std::cout << "Player O's turn" << std::endl; break;
      case TokenX: std::cout << "Player X's turn" << std::endl; break;
    }

    // ask for input
    int rowIdx;
    std::cout << "Row: ";
    std::cin >> rowIdx;

    int colIdx;
    std::cout << "Colum: ";
    std::cin >> colIdx;

    while ( 1 > rowIdx || rowIdx > 3 || 1 > colIdx || colIdx > 3 )
    {
      std::cout << "Values must be between 1 and 3!" << std::endl;
      // ask for input again
      std::cout << "Row: ";
      std::cin >> rowIdx;

      std::cout << "Colum: ";
      std::cin >> colIdx;
    }

    --rowIdx;
    --colIdx;

    // set square contents
    if (this->board->setSquare(rowIdx, colIdx, currentPlayer))
    {
      // inform server about move
      while( !this->sendMove(rowIdx, colIdx, currentPlayer) )
      {}

      // Wait for response
      RpcBase* response;
      while( !this->recieveResponse(&response) )
      {}
	  this->handleResponse( response );

      // dump board (prediction)
	  std::cout << "predicted:" << std::endl;
      this->board->dump();

      // inform server about move
      // request current board
	  while( !this->requestBoard() )
	  {}

	  response = NULL;
	  while( !this->recieveResponse( &response ) )
	  {}
	  this->handleResponse( response );

	  //dump board (server version)
	  std::cout << "validated:" << std::endl;
	  this->board->dump();

      if (this->board->checkDrawCondition())
      {
        std::cout << "A draw!" << std::endl;
		system("pause");
		quitRequest = true;
      }

      if (this->board->checkWinCondition(currentPlayer))
      {
        std::cout << "You have won!" << std::endl;
		system("pause");
        quitRequest = true;
      }

      // switch current player
      switch(currentPlayer)
      {
        case TokenO: currentPlayer = TokenX; break;
        case TokenX: currentPlayer = TokenO; break;
      }
    }
    else
    {
        std::cout << "Square is already occupied!" << std::endl;
    }
  }

  // shutdown board
  this->board->shutdown();
  delete this->board;
}

bool
ChessClientApp::sendMove(int row, int col, TokenTypePlayer player)
{
  RpcMove rpc;
  rpc.row = row;
  rpc.col = col;
  rpc.player = player;

  return this->connector->send(&rpc, sizeof(rpc));
}

bool ChessClientApp::requestBoard()
{
  RpcRequestBoard rpc;
  
  return this->connector->send(&rpc, sizeof(rpc));
}

bool ChessClientApp::recieveResponse(RpcBase** response)
{
  size_t size;
  return this->connector->receive((void**)response, &size);
}

bool ChessClientApp::handleResponse( const RpcBase* response )
{
    switch(response->type)
    {
      case RpcTypeSuccess: return this->handleRpcSuccess((RpcSuccess*)response); break;
      case RpcTypeSendBoard: return this->handleRpcSendBoard((RpcSendBoard*)response); break;
    }

	return false;
}

bool ChessClientApp::handleRpcSuccess(RpcSuccess* response)
{
	return response->success;
}

bool ChessClientApp::handleRpcSendBoard( RpcSendBoard* response )
{
	this->board->fromString( response->getAsString() );
	return true;
}

bool ChessClientApp::sendLoginRequest(const std::string& name, const std::string& password )
{
	RpcLogin rpc;

	//name
	int nameLength = 32;
	if( name.length() < 32 )
	{
		nameLength = name.length();
	}
	memcpy( rpc.name, name.c_str(), nameLength);
	rpc.name[ nameLength ] = 0;

	//password
	int pwdLength = 32;
	if( password.length() < 32 )
	{
		pwdLength = password.length();
	}
	memcpy( rpc.password, password.c_str(), pwdLength);
	rpc.password[ pwdLength ] = 0;

	return this->connector->send( &rpc, sizeof(rpc) );
}

bool ChessClientApp::handleLoginResponse(RpcLoginResponse *response)
{
	if( response->playerInfo.token == InvalidTokenType )
	{
		return true;
	}

	this->player = new GamePlayer;
	this->player->token = response->playerInfo.token;
	this->player->sessionId = response->playerInfo.sessionId;

	return true;
}
