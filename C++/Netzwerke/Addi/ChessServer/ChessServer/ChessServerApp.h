#pragma once

class ZeroMqConnector;
class DummyBoard;

class RpcBase;
class RpcMove;
class RpcRequestBoard;

class ChessServerApp
{
public:
  ChessServerApp(void);
  ~ChessServerApp(void);

  void run();
  
private:
  bool receiveRpc(RpcBase** rpc);
  bool handleRpc(RpcBase* rpc);
  bool sendResponse(bool response);
  
  bool handleRpcMove(RpcMove* rpc);
  bool handleRpcRequestBoard(RpcRequestBoard* rpc);

  ZeroMqConnector* connector;

  DummyBoard* board;
};

