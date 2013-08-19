#pragma once

enum TokenType
{
  InvalidTokenType = -1,

  Empty,
  TokenX,
  TokenO,

  NumTokenTypes
};

class DummyBoard
{
public:
  DummyBoard(void);
  ~DummyBoard(void);

  void init();
  void shutdown();

  bool checkWinCondition(TokenType playerIdx) const;
  bool checkDrawCondition() const;

  bool isSquareEmpty(int rowIdx, int colIdx) const;
  bool setSquare(int rowIdx, int colIdx, TokenType content);

  void dump() const;

protected:
  TokenType** squares;
};

