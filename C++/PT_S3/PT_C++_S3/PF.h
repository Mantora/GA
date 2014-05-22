#pragma once

/***************************************************************************
Main class 4 pathfindung (PF) for Stations

feel free to do your worst
***************************************************************************/

#include <vector>
#include "Config.h"

#include "CustomTime.h"

class Station;

class PF
{
	public:
		PF();
		~PF( void );

		void startSearch( Station* station_start, Station* station_end, CustomTime& ct_startTravel );
		std::string printBestConnection( void );
//	private: //<- no time 4 get/set
		Station* station_start;
		Station* station_end;
		CustomTime ct_startTravel;

		int startStation_GUID;
		std::vector<int> endStation_GUIDs;

		bool b_endStationFound;
		std::vector<Station*>::iterator it_stationToCheck;
		int index_stationsToCheck;
		std::vector<Station*> stationsToCheck;
		std::string str_bestConnection;

		//DEBUG variables
		int i_CalculationSteps;

		//funktions 4 pathfinding
		void analyseStation( Station* stationToAnalyse );
		bool isTargetStation( Station* stationToCheck );
		void init_addAllStationsFrom( Station* startingStation ); //extra init function 
		void addAllStationsFrom( Station* baseStation );
		bool isTargetStationInVector( void );
		void updateCurrentStationsToCheck( void );
		bool isStationInVector( Station* s );
		void checkOperationTime( Station* currentStation, Station* prefStation ); //<- current Time comes from this
};
