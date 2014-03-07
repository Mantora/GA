#pragma once

#include <vector>

#define DEBUG true

class Station;

class PF
{
	public:
		PF();
		~PF( void );

		void startSearch( Station* station_start, Station* station_end );
		std::string printBestConnection( void );
//	private:
		Station* station_start;
		Station* station_end;

		int startStation_GUID;
		std::vector<int> endStation_GUIDs;

		bool b_endStationFound;
		std::vector<Station*>::iterator it_stationToCheck;
		int index_stationsToCheck;
		std::vector<Station*> stationsToCheck;
		std::string str_bestConnection;

		//funktions 4 pathfinding
		void analyseStation( Station* stationToAnalyse );
		bool isTargetStation( Station* stationToCheck );
		void addAllStationsFrom( Station* baseStation );
		bool isTargetStationInVector( void );
		void updateCurrentStationsToCheck( void );
		bool isStationInVector( Station* s );
};
