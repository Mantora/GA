#pragma once

#include <vector>

#define DEBUG true

class Station;

class PF
{
	public:
		PF();;
		~PF( void );

		void setStations( std::vector<Station*> stations );

		void startSearch( Station* station_start, Station* station_end );
		std::string printBestConnection( void );
	private:
		Station* station_start;
		Station* station_end;

		int startStation_GUID;
		int endStation_GUID;

		std::vector<Station*>::iterator it_stationToCheck;
		std::vector<Station*> stationsToCheck;
		std::string str_bestConnection;

		//funktions 4 pathfinding
		void initWithStation( Station* stationToUse4Init );
		void analyseStation( Station* stationToAnalyse );
		bool isTargetStation( Station* stationToCheck );
};
