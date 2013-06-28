#include "Word.h"

#include <string.h>

Word::Word()
{
//	this->data = new char(MAX_WORT_LENGTH);

	for( int i = 0; i < MAX_WORT_LENGTH; i++)
		this->data[i] = 0;

	this->currentIndex = 0;

	this->appearance = 1;
}

Word::Word( char* initWord )
{
	strncpy( this->data, initWord, strlen(initWord) );
}

Word::~Word()
{
	delete [] &this->data;
}

void Word::finished()
{
	this->data[ this->currentIndex + 1 ] = '\0';
}

//SET
void Word::addChar( char c )
{
	// 65 A
	// 90 Z

	// 97 a
	// 122 z

	//GROSS zu klein
	if( c >= 65 && c <= 90 )
		c += 32;

	//klein zu GROSS
	if( c >= 97 && c <= 122 )
		c -= 32;

	this->data[ this->currentIndex ] = c;
	this->currentIndex++;
}

void Word::increateAppearence()
{
	this->appearance++;
}
//GET
char* Word::getWord()
{
	return this->data;
}

char Word::getCharakter( int index )
{
	return this->data[index];
}

int Word::getCharakterCount()
{
	return this->currentIndex;
}

int Word::getAppearence()
{
	return this->appearance;
}

//vergleich
bool Word::Equals( Word* w )
{
	for( int i = 0; i < currentIndex; i++)
	{
		char currentChar = w->getCharakter( i );
		if( this->data[i] != currentChar )
			return false;
	}

	return true;
}