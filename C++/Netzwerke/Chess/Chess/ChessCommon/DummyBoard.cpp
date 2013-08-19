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
    this->squares = new TokenTypePlayer*[3];

    for (int rowIdx=0; rowIdx<3; ++rowIdx)
    {
        this->squares[rowIdx] = new TokenTypePlayer[3];

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
DummyBoard::checkWinCondition(TokenTypePlayer playerIdx) const
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

bool DummyBoard::isSquareEmpty(int rowIdx, int colIdx) const
{
	if( rowIdx > 2 ) return false;
	if( rowIdx < 0 ) return false;
	if( colIdx > 2 ) return false;
	if( colIdx < 0 ) return false;
	return (Empty == this->squares[rowIdx][colIdx]);
}

bool DummyBoard::setSquare(int rowIdx, int colIdx, TokenTypePlayer content)
{
	if (!this->isSquareEmpty(rowIdx, colIdx)) return false;

	this ->squares[rowIdx][colIdx] = content;

	return true;
}

void DummyBoard::dump() const
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
			case Empty:  std::cout << "."; break;
			}
		}
		std::cout << "|" << std::endl;
		std::cout << "+-+-+-+" << std::endl;
	}
}

std::string DummyBoard::toString() const
{
	std::string retVal;

	for (int rowIdx=0; rowIdx<3; ++rowIdx)
	{
		for (int colIdx=0; colIdx<3; ++colIdx)
		{
			switch(this->squares[rowIdx][colIdx])
			{
				case TokenX:	retVal.append("X"); break;
				case TokenO:	retVal.append("O"); break;
				case Empty:		retVal.append("."); break;
			}
		}
	}

	return retVal;
}

void DummyBoard::fromString(const std::string &boardAsString)
{
	for (int rowIdx=0; rowIdx<3; ++rowIdx)
	{
		for (int colIdx=0; colIdx<3; ++colIdx)
		{
			int index = colIdx + 3 * rowIdx;
			char currentToken = boardAsString[ index ];

			switch( currentToken )
			{
				case 'X': this->squares[rowIdx][colIdx] = TokenX; break;
				case 'O': this->squares[rowIdx][colIdx] = TokenO; break;
				case '.': this->squares[rowIdx][colIdx] = Empty; break;
			}
		}
	}
}