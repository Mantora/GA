#pragma once

#include <sstream>

class CustomTime
{
	public:
		CustomTime(void);
		~CustomTime(void);

		void add( int minutesToAdd );
		std::string toString( void );

//	private:
		int currentTime;

};
