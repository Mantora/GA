#pragma once

/***************************************************************************
Main class 4 pathfindung (PF) for Stations

benutzt "Wassertropfen" Methode
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

		//variable zum speichern der gesamten Station daten
		std::vector<Station*> stations;
		void setDatas( std::vector<Station*> stationDatas );

		// 4 return
		std::vector<Station*> routeData;

		//variable für Stations zur analyse
		std::vector<Station*> stationsToAnalyse;
		std::vector<Station*> stationsToAnalyseNext;

		std::vector<Station*> startSearch( Station* station_start, Station* station_end, CustomTime& ct_startTravel );

		// funktion zum untersuchen einer Station
		void analyseStation( Station* s );
		void finalStationFound( Station* s );

		bool isFinalStation( Station* s );
		bool isStartStation( Station* s );

		// funktion zum berechnen der benötigen zeit bis zu der Station ( fahren oder laufen )
		void calculateJourneyTime( Station* s, int ct_current );

	private:
		void cleanup();
};
