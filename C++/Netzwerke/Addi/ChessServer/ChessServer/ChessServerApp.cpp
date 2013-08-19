#include "StdAfx.h"
#include "ChessServerApp.h"

#include <ZeroMqConnector.h>
#include <string>
#include <iostream>

#include <DummyBoard.h>

#include <RpcMove.h>
#include <RpcRequestBoard.h>

ChessServerApp::ChessServerApp(void)
  : connector(0)
{
}


ChessServerApp::~ChessServerApp(void)
{
}

void
ChessServerApp::run()
{
  this->connector = new ZeroMqConnector(ZMQ_REP);

  if ( !this->connector->setup() )
  {
    std::cout << "failed set up" << std::endl;
  }
  else
  {
    std::cout << "set up" << std::endl;
  }

  if ( !this->connector->bind("tcp://*:55555") )
  {
    std::cout << "failed bind" << std::endl;
  }
  else
  {
    std::cout << "bind" << std::endl;
  }
  
  this->board = new DummyBoard();
  this->board->init();

  while (true)
  {
    RpcBase* rpc;
    while ( !this->receiveRpc(&rpc) )
    {
      //sleep
    }

    bool succes = this->handleRpc(rpc);
    while ( !this->sendResponse(succes) )
    {
      //sleep
    }
  }

  this->board->shutdown();
  delete this->board;
}

bool
ChessServerApp::receiveRpc(RpcBase** rpc)
{
    size_t size;

    return this->connector->receive((void**)rpc, &size);
}

bool
ChessServerApp::handleRpc(RpcBase* rpc)
{
    switch(rpc->type)
    {
      case RpcTypeMove:
        return this->handleRpcMove((RpcMove*)rpc);
      case RpcTypeRequestBoard:
        return this->handleRpcRequestBoard((RpcRequestBoard*)rpc);
    }
    return false;
}

bool
ChessServerApp::handleRpcMove(RpcMove* rpc)
{
    bool success = this->board->setSquare(rpc->row, rpc->col, rpc->player);

    if (success)
    {
        this-> board->dump();
    }

    return success;
}

bool
ChessServerApp::handleRpcRequestBoard(RpcRequestBoard* rpc)
{
    return true;
}

bool
  ChessServerApp::sendResponse(bool response)
{
    return this->connector->send(&response, sizeof(response));
}