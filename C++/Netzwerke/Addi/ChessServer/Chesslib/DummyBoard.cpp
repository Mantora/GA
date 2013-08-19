#include "DummyBoard.h"

#include <iostream>


DummyBoard::DummyBoard(void)
  : squares(0)
{
}


DummyBoard::~DummyBoard(void)
{
}

void
DummyBoard::init()
{
    this->squares = new TokenType*[3];

    for (int rowIdx=0; rowIdx<3; ++rowIdx)
    {
        this->squares[rowIdx] = new TokenType[3];

        for (int colIdx=0; colIdx<3; ++colIdx)
        {
            this->squares[rowIdx][colIdx] = Empty;
        }
    }
}

void
DummyBoard::shutdown()
{
    for (int rowIdx=0; rowIdx<3; ++rowIdx)
    {
      delete[] this->squares[rowIdx];
    }
    delete[] this->squares;
}

bool
DummyBoard::checkWinCondition(TokenType playerIdx) const
{
    for (int rowIdx=0; rowIdx<3; ++rowIdx)
    {
      bool hasWon = true;
      
      for (int colIdx=0; colIdx<3; ++colIdx)
      {
          hasWon &= (playerIdx == this->squares[rowIdx][colIdx]);
      }
      if (hasWon)
      {
        return true;
      }
    }
    for (int colIdx=0; colIdx<3; ++colIdx)
    {
      bool hasWon = true;
      
      for (int rowIdx=0; rowIdx<3; ++rowIdx)
      {
          hasWon &= (playerIdx == this->squares[rowIdx][colIdx]);
      }
      if (hasWon)
      {
        return true;
      }
    }
    if (playerIdx == this->squares[0][0]
        && playerIdx ==this->squares[1][1]
        && playerIdx ==this->squares[2][2])
    {
      return true;
    }
    if (playerIdx == this->squares[2][0]
        && playerIdx ==this->squares[1][1]
        && playerIdx ==this->squares[0][2])
    {
      return true;
    }
    return false;
}

bool
DummyBoard::checkDrawCondition() const
{
  if (this->checkWinCondition(TokenX)) return false;
  if (this->checkWinCondition(TokenO)) return false;
  
  for (int rowIdx=0; rowIdx<3; ++rowIdx)
  {
      for (int colIdx=0; colIdx<3; ++colIdx)
      {
          if (this->isSquareEmpty(rowIdx, colIdx))
          {
            return false;
          }
      }
  }
  return false;
}

bool
DummyBoard::isSquareEmpty(int rowIdx, int colIdx) const
{
  return (Empty == this->squares[rowIdx][colIdx]);
}

bool
DummyBoard::setSquare(int rowIdx, int colIdx, TokenType content)
{
  if (!this->isSquareEmpty(rowIdx, colIdx)) return false;

  this ->squares[rowIdx][colIdx] = content;

  return true;
}

void
DummyBoard::dump() const
{
  std::cout << "+-+-+-+" << std::endl;
  for (int rowIdx=0; rowIdx<3; ++rowIdx)
  {
      for (int colIdx=0; colIdx<3; ++colIdx)
      {
      std::cout << "|";
          switch(this->squares[rowIdx][colIdx])
          {
          case TokenX:  std::cout << "X"; break;
          case TokenO:  std::cout << "O"; break;
          case Empty:  std::cout << " "; break;
          }
      }
      std::cout << "|" << std::endl;
      std::cout << "+-+-+-+" << std::endl;
  }
}