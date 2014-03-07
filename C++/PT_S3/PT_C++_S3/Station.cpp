#include "Station.h"

#include "Utility.h"

Station::Station( int journey_time, std::string station_name, std::string line_name)
{
	this->journey_time = journey_time;
	this->station_name = station_name;
	this->line_name = line_name;

	this->visited = false;

	this->GUID = Utility::getNewGUID();
	this->typ = STATION_NORMAL;

	this->route_time = CustomTime();
}

Station::~Station( void )
{

}

void Station::setOperationTime( std::string start, std::string end )
{
	this->operation_time_start = CustomTime(start);
	this->operation_time_end = CustomTime(end);
};

int Station::getGUID( void )
{
	return this->GUID;
};

void Station::addPosibleNextStation( Station* possibleNextStation )
{
	this->possible_next_stations.push_back( possibleNextStation );
};

void Station::addConnectionToOtherLine( Station* stationToOtherLine )
{
	this->connections_to_other_line.push_back( stationToOtherLine );
};

std::string Station::getStationName( void )
{
	return this->station_name;
};

bool Station::isVisited( void )
{
	return this->visited;
};

void Station::setVisited( bool b_visited )
{
	this->visited = b_visited;
};

std::string Station::getFormatedStation( void )
{
	string str_return;
	str_return += "(" + this->line_name + ") " + station_name;

	return str_return;
};
