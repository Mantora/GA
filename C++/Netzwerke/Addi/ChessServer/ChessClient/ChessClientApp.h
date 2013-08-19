#pragma once

class ZeroMqConnector;

#include <DummyBoard.h>

class ChessClientApp
{
public:
  ChessClientApp(void);
  ~ChessClientApp(void);

  void run();

  bool sendMove(int row, int col, TokenType player);
  bool requestBoard();

  bool recieveResponse(bool** response);

private:
    ZeroMqConnector* connector;

    DummyBoard* board;
};

