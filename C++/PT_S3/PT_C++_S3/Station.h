#pragma once

#include <string>
#include <vector>

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

		std::vector<Station*> possible_next_stations;
		int getGUID( void );

		void addPosibleNextStation( Station* possibleNextStation );

		std::string getStationName( void );

		bool isVisited( void );
		void setVisited( bool b_visited );

		std::string getFormatedStation( void );

		STATION_TYP typ;

		std::string str_routeToThisStation;

//	private:
		//Performance Boost: nicht string station_name immer wieder vergleich sondern nur zur Identifizierung und dann über GUID
		int GUID; // GlobalUnicIDentification 

		int journey_time;
		std::string station_name;
		std::string line_name;


		bool visited;
};
