#include "CustomTime.h"

CustomTime::CustomTime(void)
{
	this->currentTime = 0;
}

CustomTime::~CustomTime(void)
{

}

void CustomTime::add( int minutesToAdd )
{
	this->currentTime += minutesToAdd;
};

std::string CustomTime::toString( void )
{
	std::stringstream ss;

	int h = currentTime/60;
	int min = (currentTime - (60*h) );

	ss << h << ":" << min << "h";

	return ss.str();
};
