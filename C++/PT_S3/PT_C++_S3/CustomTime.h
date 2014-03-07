#pragma once

#include <sstream>

class CustomTime
{
	public:
		CustomTime( void );
		CustomTime( CustomTime& other );
		CustomTime( std::string customTimeAsString );
		CustomTime( std::string str_h, std::string str_min );
		~CustomTime( void );

		void add( int minutesToAdd );
		std::string toString( void );

		int combare( CustomTime& other );

//	private:
		int currentTime;

};
