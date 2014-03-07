#include "PF.h"

#include <iostream>

#include "Station.h"
#include "Timer.h"

using namespace std;

PF::PF()
{
	this->index_stationsToCheck = 0;
	this->b_endStationFound = false;

	//DEBUG variables
	this->i_CalculationSteps = 0;
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
	this->str_bestConnection = "From " + station_start->getFormatedStation() + " to " + station_end->getFormatedStation() + " :\n";

	//station_start is first point to check
	this->analyseStation( station_start );

	//BEGINN SEARCH
	if( DEBUG ) cout << endl << "Beginn at " << station_start->getFormatedStation() << endl;

	while( !this->b_endStationFound )
	{
		//no target_Station found,
		this->i_CalculationSteps++;
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
	if(DEBUG) cout << "PF::isTargetStation( " << stationToCheck->getFormatedStation() << " )" << endl;

	stationToCheck->setVisited( true );
	if( stationToCheck->getStationName().compare( this->station_end->getStationName() ) == 0 )
	{
		if(DEBUG) cout << "PF::isTargetStation : FOUND !" << endl;
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
		if( !(*it)->isVisited() 
		&& !this->isStationInVector( (*it) ) )
		{
			this->stationsToCheck.push_back( (*it) );
			(*it)->str_routeToThisStation = baseStation->str_routeToThisStation + "over " + (*it)->getFormatedStation() + "\n";
		}
	}

	//CROSS_STATION
	for( it = baseStation->connections_to_other_line.begin(); it != baseStation->connections_to_other_line.end(); it++ )
	{
		std::vector<Station*>::iterator it2;
		for( it2 = (*it)->possible_next_stations.begin(); it2 != (*it)->possible_next_stations.end(); it2++ )
		{
			if( !(*it2)->isVisited() 
			&& !this->isStationInVector( (*it2) ) )
			{
				this->stationsToCheck.push_back( (*it2) );
				(*it2)->str_routeToThisStation = baseStation->str_routeToThisStation + "take " + (*it2)->getFormatedStation() + "\n";
			}
		}
	}
};

bool PF::isTargetStationInVector( void )
{
	std::vector<Station*>::iterator it;
	for( it = this->stationsToCheck.begin(); it != this->stationsToCheck.end(); it++ )
	{
		if( this->isTargetStation( (*it) ) )
		{
			this->str_bestConnection = (*it)->str_routeToThisStation;
			return true;
		}
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

bool PF::isStationInVector( Station* s )
{
	std::vector<Station*>::iterator it;
	for( it = this->stationsToCheck.begin(); it != this->stationsToCheck.end(); it++ )
	{
		//only add unvisted Stations
		if( (*it)->GUID == s->GUID )
			return true;
	}
	return false;
};
