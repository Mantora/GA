#include "Station.h"

#include "Utility.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Station::Station( int journey_time, std::string station_name, std::string line_name)
{
	this->journey_time = this->journey_time_pf = journey_time;
	this->station_name = station_name;
	this->line_name = line_name;

	this->analysed = false;
	this->visited = false;

	this->GUID = Utility::getNewGUID();
	this->typ = STATION_NORMAL;

	this->pathfindingOrder = 0;
	this->routeTimeToThisStation = CustomTime();
	this->totalRouteTime = CustomTime();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Station::~Station( void )
{
	this->possible_next_stations.clear();
	this->connections_to_other_line.clear();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void 
Station::setOperationTime( std::string start, std::string end )
{
	this->operation_time_start = CustomTime(start);
	this->operation_time_end = CustomTime(end);

	//24h fix if start > end
//	if( this->operation_time_end.currentTime < this->operation_time_start.currentTime )
//		this->operation_time_end.add( 24*60 );
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void 
Station::addPosibleNextStation( Station* possibleNextStation )
{
	this->possible_next_stations.push_back( possibleNextStation );
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void 
Station::addConnectionToOtherLine( Station* stationToOtherLine )
{
	this->connections_to_other_line.push_back( stationToOtherLine );
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string Station::getFormatedStation( void )
{
	ostringstream oss;
	oss << "(" << this->line_name << ") " << station_name << " " << this->operation_time_start.toString() << " - " << this->operation_time_end.toString();
	return oss.str();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string Station::getFormatedStation4Route( void )
{
	ostringstream oss;
	oss << this->line_name;
	
	for( int i = this->line_name.length(); i < 7; i++)
		oss << " ";

	oss << this->station_name;
	for( int i = this->station_name.length(); i < 40; i++)
		oss << " ";

	oss << this->routeTimeToThisStation.toString();

	return oss.str();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Station::AddRouteTimeToAllStations( int additionalMinutes )
{
	this->routeTimeToThisStation.add( additionalMinutes );
	for( std::vector<Station*>::iterator it = this->connections_to_other_line.begin(); it != this->connections_to_other_line.end(); it++ )
	{
		(*it)->routeTimeToThisStation.add( additionalMinutes );
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Station::SetTotalRouteTimeToAllStations( int minutes )
{
	this->totalRouteTime.currentTime = minutes;
	for( std::vector<Station*>::iterator it = this->connections_to_other_line.begin(); it != this->connections_to_other_line.end(); it++ )
	{
		(*it)->totalRouteTime.currentTime = minutes;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Station::AddTotalRouteTimeToAllStations( int additionalMinutes )
{
	this->totalRouteTime.add( additionalMinutes );
	for( std::vector<Station*>::iterator it = this->connections_to_other_line.begin(); it != this->connections_to_other_line.end(); it++ )
	{
		(*it)->totalRouteTime.add( additionalMinutes );
	}
}