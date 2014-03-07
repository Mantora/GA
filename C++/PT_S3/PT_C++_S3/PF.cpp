#include "PF.h"

#include <iostream>

#include "Station.h"

using namespace std;

PF::PF()
{
	this->index_stationsToCheck = 0;
	this->b_endStationFound = false;
}

PF::~PF( void )
{

}

void PF::startSearch( Station* station_start, Station* station_end )
{
	this->station_start = station_start;
	this->station_start->str_routeToThisStation = "Start at "+station_start->getFormatedStation()+"\n";
	this->station_end = station_end;

	this->startStation_GUID = station_start->getGUID();

	//init the return string
	this->str_bestConnection = "From " + station_start->getFormatedStation() + " to " + station_end->getFormatedStation() + "\n";

	//station_start is first point to check
	this->analyseStation( station_start );

	//BEGINN SEARCH
	if( DEBUG ) cout << endl << "Beginn at " << station_start->getFormatedStation() << endl;

	int i_steps = 0;
	while( !this->b_endStationFound )
	{
		//no target_Station found,
		i_steps++;
		if( isTargetStationInVector() )
		{
			this->b_endStationFound = true;
			break;
		}
		else
		{
			//all current known stations checked but no target_Station found
			this->updateCurrentStationsToCheck();
		}


	}

	if( DEBUG ) std::cout << "EndStation found after " << i_steps << " steps." << std::endl;
};

std::string PF::printBestConnection( void )
{
	return this->str_bestConnection;
};

//funktion zum hinzufügen von neuen Knotenpunkten
void PF::analyseStation( Station* stationToAnalyse )
{
	//1) check 4 target station
	if( this->isTargetStation( stationToAnalyse ) )
	{
		this->b_endStationFound = true;
		return;
	}
	else
	{
		this->addAllStationsFrom( stationToAnalyse );
	}

};

//function to check, if stationToCheck is our targetStation
bool PF::isTargetStation( Station* stationToCheck )
{
	stationToCheck->setVisited( true );

	if( stationToCheck->getStationName().compare( this->station_end->getStationName() ) == 0 )
	{
		return true;
	}

/*	if( this->station_end->GUID == stationToCheck->GUID )
		return true;
	else
	{
		std::vector<Station*>::iterator it;
		for( it = stationToCheck->connections_to_other_line.begin(); it != stationToCheck->connections_to_other_line.end(); it++ )
		{
			(*it)->setVisited( true );

			std::vector<int>::iterator it_possibleGUIDS;
			for( it_possibleGUIDS = this->endStation_GUIDs.begin(); it_possibleGUIDS != this->endStation_GUIDs.end(); it_possibleGUIDS++ )
			{
				if( (*it)->GUID == (*it_possibleGUIDS) )
				{
					return true;
				}
			}
		}
	}
*/
	return false;
};


void PF::addAllStationsFrom( Station* baseStation )
{
	//STATION_NORMAL
	std::vector<Station*>::iterator it;
	for( it = baseStation->possible_next_stations.begin(); it != baseStation->possible_next_stations.end(); it++ )
	{
		//only add unvisted Stations
		if( !(*it)->isVisited() )
			this->stationsToCheck.push_back( (*it) );
	}

	//CROSS_STATION
	for( it = baseStation->connections_to_other_line.begin(); it != baseStation->connections_to_other_line.end(); it++ )
	{
		std::vector<Station*>::iterator it2;
		for( it2 = (*it)->possible_next_stations.begin(); it2 != (*it)->possible_next_stations.end(); it2++ )
		{
			if( !(*it2)->isVisited() )
				this->stationsToCheck.push_back( (*it2) );
		}
	}
};

bool PF::isTargetStationInVector( void )
{
	std::vector<Station*>::iterator it;
	for( it = this->stationsToCheck.begin(); it != this->stationsToCheck.end(); it++ )
	{
		if( this->isTargetStation( (*it) ) )
			return true;
	}

	return false;
};

void PF::updateCurrentStationsToCheck( void )
{
	//alle bekannten Station einen Schritt weiter gehen
	std::vector<Station*>::iterator it;
	for( it = this->stationsToCheck.begin(); it != this->stationsToCheck.end(); NULL )
	{
		//nur bereits bekannt stationen bearbeiten
		if( (*it)->isVisited() )
		{
			this->addAllStationsFrom( (*it) );

			//it löschen
			it = this->stationsToCheck.begin();
			it = this->stationsToCheck.erase( it );
		}
		else
		{
			it++;
		}
	}

	if( DEBUG ) cout << "DEBUG" << endl;
};
