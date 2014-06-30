#pragma once

/***************************************************************************
This class represent a Station and hold spezific information
such as the LINE_NAME this station belongs

Alle Stationen sind doppelt verkette listen und kennen:
- Ihre Linienverbindung (this->possible_next_stations)
- Ihre Verbindungen zu einer anderen Linie
***************************************************************************/

#include <string>
#include <vector>

#include "CustomTime.h"

enum STATION_TYP
{
	STATION_NORMAL, // selbe Linie
	STATION_CROSS	// verbindung zu einer anderen Linie
};

class Station
{
	public:
		Station( int journey_time, std::string station_name, std::string line_name );
		~Station( void );
		void setOperationTime( std::string start, std::string end );

		std::vector<Station*> possible_next_stations;
		std::vector<Station*> connections_to_other_line;

		void addPosibleNextStation( Station* possibleNextStation );
		void addConnectionToOtherLine( Station* stationToOtherLine );

		std::string getFormatedStation( void );
		std::string getFormatedStation4Route( void );

		STATION_TYP typ;

		//Performance Boost: nicht string station_name immer wieder vergleich sondern nur zur Identifizierung und dann über GUID (int schneller als std::string)
		int GUID; // GlobalUnicIDentification 

		int journey_time;
		int journey_time_pf;

		std::string station_name;
		std::string line_name;
		CustomTime operation_time_start;
		CustomTime operation_time_end;

		CustomTime routeTimeToThisStation;
		void AddRouteTimeToAllStations( int additionalMinutes );

		bool analysed;
		bool visited;
		int pathfindingOrder;

		CustomTime totalRouteTime;
		void SetTotalRouteTimeToAllStations( int minutes ); 
		void AddTotalRouteTimeToAllStations( int additionalMinutes );
};
