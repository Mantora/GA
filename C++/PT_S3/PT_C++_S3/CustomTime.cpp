#include "CustomTime.h"

#include <iostream>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CustomTime::CustomTime( void )
{
	this->currentTime = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CustomTime::CustomTime( CustomTime& other )
{
	this->currentTime = other.currentTime;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CustomTime::CustomTime( int minutes )
{
	this->currentTime = minutes;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CustomTime::CustomTime( std::string customTimeAsString )
{
	int i_str_length = customTimeAsString.length();
	if( i_str_length != 5 )
	{
		std::cout << "TO IMPLEMENT: exception handling on  CustomTime::CustomTime( std::string customTimeAsString:" << customTimeAsString << " )" << std::endl;
		this->currentTime = 0;
		return;
	}

	std::string str_h = customTimeAsString.substr( 0, 2 );
	std::string str_min = customTimeAsString.substr( 3, 5 );

	int h = atoi(str_h.c_str());
	int min = atoi(str_min.c_str());

	this->currentTime = ( 60 * h );
	this->currentTime += min;

	if( h > 24 || h < 0 )
	{
		std::cout << "TO IMPLEMENT: exception handling on  CustomTime::CustomTime( std::string customTimeAsString:" << customTimeAsString << " )" << std::endl;
		this->currentTime = 0;
	}

	if( min > 59 || min < 0 ) 
	{
		std::cout << "TO IMPLEMENT: exception handling on  CustomTime::CustomTime( std::string customTimeAsString:" << customTimeAsString << " )" << std::endl;
		this->currentTime = 0;
	}

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CustomTime::CustomTime( std::string str_h, std::string str_min )
{
	int h = atoi(str_h.c_str());
	int min = atoi(str_min.c_str());
	std::cout << "str_h:" << h << std::endl;
	std::cout << "str_min:" << min << std::endl;

	if( h > 24 || h < 0 ) std::cout << "TO IMPLEMENT: exception handling on  CustomTime::CustomTime( str_h:" << h << ", str_min:" << min << " )" << std::endl;
	if( min > 59 || min < 0 ) std::cout << "TO IMPLEMENT: exception handling on  CustomTime::CustomTime( str_h:" << h << ", str_min:" << min << " )" << std::endl;

	this->currentTime = ( 60 * h );
	this->currentTime += min;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CustomTime::~CustomTime( void )
{

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void 
CustomTime::add( int minutesToAdd )
{
	this->currentTime += minutesToAdd;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string 
CustomTime::toString( void )
{
	std::stringstream ss;

	int tmp = currentTime;

	int h = tmp / 60;
	int min = (tmp - (60*h) );

	//some formating
	if( h < 10 )ss << "0" << h;
	else		ss << h;

	if( min < 10 )  ss << ":0" << min << "h";
	else			ss << ":" << min << "h";

	return ss.str();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int 
CustomTime::combare( CustomTime& other )
{
	if( this->currentTime > other.currentTime )
		return 1;	//1 if this is greater
	else if( this->currentTime < other.currentTime )
		return -1;	//-1 if other is greater
	else// if( this->currentTime == other.currentTime )
		return 0;	//0 on equal
}
