#include "stdafx.h"

//text Color
const int t_black	  = 0x0000;
const int t_blue	  = 0x0001;
const int t_green	  = 0x0002;
const int t_red		  = 0x0004;
const int t_intensity = 0x0008;

//background Color
const int b_black		= 0x0000;
const int b_blue		= 0x0010;
const int b_green		= 0x0020;
const int b_red			= 0x0040;
const int b_intensity	= 0x0080;


#include <iostream>
#include <windows.h>

void color( int c )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), c);
}

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main(void)
{
	gotoxy( 50, 20);
	color( t_black | b_intensity);
	std::cout << "* <--(x=50,y=20)";
	gotoxy( 1, 0);
	color( t_green | b_blue );
	std::cout << "* <--(x=1,y=0)";
	std::cin.get();
}

/* LINUX

ncurses.h
*/