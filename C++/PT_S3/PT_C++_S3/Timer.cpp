//eine einfache Timer Klasse
#include "Timer.h"

Timer::Timer(void)
{
	reset();
}

Timer::~Timer(void)
{

}

void Timer::reset(void)
{
	_start = clock();
}

int Timer::getMSecSinceStart(void)
{
	int tmp = 0;

	tmp = clock() - _start;

	return tmp;
}
