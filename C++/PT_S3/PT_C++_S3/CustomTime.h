#pragma once

/***************************************************************************
This class holds time related informations
Internal working with "minutes"

Some construktors 4 this specific projekt

TODO: Exception handling 4 wrong construktor arguments
***************************************************************************/

#include <sstream>

class CustomTime
{
	public:
		CustomTime( void );
		CustomTime( int minutes );
		CustomTime( CustomTime& other );
		CustomTime( std::string customTimeAsString );
		CustomTime( std::string str_h, std::string str_min );
		~CustomTime( void );

		void add( int minutesToAdd );
		std::string toString( void );

		int combare( CustomTime& other );

		int currentTime; //<- minutes
};
