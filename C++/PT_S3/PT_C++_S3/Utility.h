#pragma once

/***************************************************************************
This class represent very simple utility class to generate and reset 
GUIDs (Global Unic IDentifyer)
***************************************************************************/

#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Utility
{
	private:
		static int runningGUID;

	public:
		Utility();
		~Utility();

		static int getNewGUID();

		static void resetGUIDs();

		static int getRandomInt( int min, int max )
		{
			int tmp = 0;

			if( max >= min && (max-min) != 0 )
				tmp = rand()%( max - min ) + min;

//			int tmp = rand()%( max * 10 * precision ) + min;
//			float rand = tmp / (float)(10*precision);

//beispiel:
//		int angle = rand()%(5*GENAUIGKEIT);
//		float randAngle = angle / 100.0f;

			return tmp;
		};

		//LINUX ONLY: get public IP with the curl linux comand
		static const char* getPublicIP()
		{
			string buffer;
	
			system( "curl icanhazip.com > myAdress" );
			
			ifstream infile;
			infile.open( "myAdress" );
			getline( infile, buffer );

			return buffer.c_str();
		};

		static void PrintToConsol( const char* message )
		{	
			#ifdef _WIN32 //Windows Header
				cout << message << endl;
			#else //Linux Header
				
			#endif
		};

};
