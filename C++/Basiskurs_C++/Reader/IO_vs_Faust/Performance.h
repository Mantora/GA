#pragma once
//Klasse zum ermittlen der verbrauchten CPU Zeit

/**********************VERWENDUNG**********************

//Performancetest starten
Performance p;

[...]

//Performancetest beenden um zeit zu ermitteln
double verbrauchteZeit = p.stop();

***********************ALTERNATIV***********************
//Bereiche festlegen, in denen getestet werden soll

[...]
{
	Performance p;
	
	[...]

	double verbrauchteZeit = p.stop();
}
[...}

*******************************************************/
#include <windows.h>
#include <iostream>

using namespace std;

class Performance
{
	private:
		LONGLONG frequency;
		LONGLONG startCount;
		LONGLONG endCount;

	public:
		Performance();
		~Performance();

		void start();
		double stop();
};

/*


*/