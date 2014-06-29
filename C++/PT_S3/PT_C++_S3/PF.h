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

		Station* s_start;
		Station* s_end;
		CustomTime ct_start;

		// steuervariable, ob das ziel gefunden wurde
		bool stop;

		//variable für die anzahl der schritte
		int calculationSteps;

		//variable to hold the hole station datas
		std::vector<Station*> stations;
		void setDatas( std::vector<Station*> stationDatas );

		// 4 return
		std::vector<Station*> routeData;

		//variable to hold the stations 4 analyse
		std::vector<Station*> stationsToAnalyse;
		std::vector<Station*> stationsToAnalyseNext;

		std::vector<Station*> startSearch( Station* station_start, Station* station_end, CustomTime& ct_startTravel );

		// funktion zum untersuchen einer Station
		void analyseStation( Station* s );
		void finalStationFound( Station* s );

		bool isFinalStation( Station* s );
		bool isStartStation( Station* s );

	private:
		void cleanup();
};
