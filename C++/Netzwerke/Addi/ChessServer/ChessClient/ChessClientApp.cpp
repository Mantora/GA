#include "StdAfx.h"
#include "ChessClientApp.h"

#include <ZeroMqConnector.h>
#include <string>
#include <iostream>

#include <DummyBoard.h>
#include <RpcMove.h>
#include <RpcRequestBoard.h>

ChessClientApp::ChessClientApp(void)
  : connector(0)
{
}


ChessClientApp::~ChessClientApp(void)
{
}

void
ChessClientApp::run()
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

  // setup board
  this->board = new DummyBoard();
  this->board->init();;

  TokenType currentPlayer = TokenO;
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
      // Send Move Command
      while( !this->sendMove(rowIdx, colIdx, currentPlayer) )
      {}

      // Wait for response
      bool* response;
      while( !this->recieveResponse(&response) )
      {}

      // dump board
      this->board->dump();

      // inform server about move
      // request current board
    
      if (this->board->checkDrawCondition())
      {
        std::cout << "A draw!" << std::endl;
      }

      if (this->board->checkWinCondition(currentPlayer))
      {
        std::cout << "You have won!" << std::endl;
        quitRequest;
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
ChessClientApp::sendMove(int row, int col, TokenType player)
{
  RpcMove rpc;
  rpc.row = row;
  rpc.col = col;
  rpc.player = player;

  return this->connector->send(&rpc, sizeof(rpc));
}

bool
ChessClientApp::requestBoard()
{
  RpcRequestBoard rpc;
  
  return this->connector->send(&rpc, sizeof(rpc));
}

bool
ChessClientApp::recieveResponse(bool** response)
{
  size_t size;
  return this->connector->receive((void**)response, &size);
}