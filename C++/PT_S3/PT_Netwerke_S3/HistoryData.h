#pragma once

#include <iomanip>// ::std::setw

#define DEBUG false

enum BUTTONSTATE
{
	NO_INPUT	= -1, 
	FALSE		=  0,
	TRUE		=  1
};

struct HistoryData
{
	int timestamp;
	CVector3 pos;
	CVector3 dir;
	BUTTONSTATE buttonState;

	HistoryData( void  )
	{
		this->timestamp = 0;
		this->pos = CVector3();
		this->dir = CVector3();
		this->buttonState = NO_INPUT;
	};

	HistoryData( int timestamp, CVector3 position = CVector3(), CVector3 direction = CVector3(), BUTTONSTATE buttonDown = NO_INPUT )
	{
		this->timestamp = timestamp;
		this->pos = position;
		this->dir = direction;
		this->buttonState = buttonDown;
	};

	void print( void )
	{
		cout << setw(5) << left << this->timestamp << ": on pos:" << this->pos << " dir:" << this->dir << " buttonState:" << this->buttonState << endl;
	};
};
