#pragma once

#include <string>

enum TokenTypePlayer
{
	InvalidTokenType = -1	,

	Empty					,
	TokenX					,
	TokenO					,

	NumTokenTypes
};

class DummyBoard
{
	public:
		DummyBoard(void);
		~DummyBoard(void);

		void init();
		void shutdown();

		bool checkWinCondition(TokenTypePlayer playerIdx) const;
		bool checkDrawCondition() const;

		bool isSquareEmpty(int rowIdx, int colIdx) const;
		bool setSquare(int rowIdx, int colIdx, TokenTypePlayer content);

		void dump() const;

		std::string toString() const;
		void fromString( const std::string& boardAsString );

	protected:
		TokenTypePlayer** squares;
};

