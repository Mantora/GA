#pragma once

#include <time.h>

class Timer
{
	private:
		clock_t _start;
		clock_t _end;
		clock_t _diff;

	public:
		Timer(void);
		~Timer(void);

		void reset(void);

		int getMSecSinceStart(void);
};
