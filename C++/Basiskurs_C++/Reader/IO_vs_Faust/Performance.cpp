#include "Performance.h"

Performance::Performance()
{
	if( ! QueryPerformanceFrequency( (LARGE_INTEGER*)&this->frequency) )
		cout << "Performance.h: Error, Performance Counter nicht vorhanden" << endl;
	else
		this->start();
}

Performance::~Performance()
{
	//cout << "~Performance: zeit: " << this->stop() << endl;
}

void Performance::start()
{
	QueryPerformanceCounter( (LARGE_INTEGER*)&this->startCount );
}

double Performance::stop()
{
	QueryPerformanceCounter( (LARGE_INTEGER*)&this->endCount );
	double diff = ( ((double)(this->endCount - this->startCount)) / ((double)(this->frequency)) );
	return diff;
}
