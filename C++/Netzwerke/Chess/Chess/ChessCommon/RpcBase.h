#pragma once

#include "RpcType.h"

class RpcBase
{
public:
  RpcBase(RpcType type);
  virtual ~RpcBase(void);

  RpcType type;
};

