#pragma once

/***************************************************************************
This class represent a Station and hold spezific information
such as the LINE_NAME this station belongs

All Stations are "double linked lists" and know there
normalTrainConnections (this->possible_next_stations)
and there connectionsToOtherLines (this->connections_to_other_line)
to use "raindrop" technique
***************************************************************************/

#include <string>
#include <vector>

#include "CustomTime.h"

enum STATION_TYP
{
	STATION_NORMAL, // same line
	STATION_CROSS	// connection to different line
};

class Station
{
	public:
		Station( int journey_time, std::string station_name, std::string line_name );
		~Station( void );
		void setOperationTime( std::string start, std::string end );

		std::vector<Station*> possible_next_stations;
		std::vector<Station*> connections_to_other_line;
		int getGUID( void );

		void addPosibleNextStation( Station* possibleNextStation );
		void addConnectionToOtherLine( Station* stationToOtherLine );

		std::string getStationName( void );

		bool isVisited( void );
		void setVisited( bool b_visited );

		std::string getFormatedStation( void );

		STATION_TYP typ;

		std::string str_routeToThisStation;

//	private://<- no time 4 get/set
		//Performance Boost: nicht string station_name immer wieder vergleich sondern nur zur Identifizierung und dann über GUID (int schneller als std::string)
		int GUID; // GlobalUnicIDentification 

		int journey_time;

		CustomTime route_time; // zeit bis zu dieser station

		std::string station_name;
		std::string line_name;
		CustomTime operation_time_start;
		CustomTime operation_time_end;

		bool visited;
};
