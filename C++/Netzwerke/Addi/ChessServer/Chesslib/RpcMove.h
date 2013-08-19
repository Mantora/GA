#pragma once

#include "rpcbase.h"
#include "DummyBoard.h"

class RpcMove : public RpcBase
{
public:
  RpcMove(void);
  virtual ~RpcMove(void);

  int row;
  int col;
  TokenType player;
};

