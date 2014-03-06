#include "PF.h"

#include <iostream>

#include "Station.h"

using namespace std;

PF::PF()
{
	this->index_stationsToCheck = 0;
}

PF::~PF( void )
{

}

void PF::setStations( std::vector<Station*> stations )
{
	//this->stationsToCheck = stations;
/*
	for( std::vector<Station*>::iterator it1 = stations.begin(); it1 != stations.end(); it1++ )
	{

		if( (*it1)->getStationName().compare( "S+U Jannowitzbruecke" ) == 0 )
			cout << "DEBUG" << endl;


		for( std::vector<Station*>::iterator it2 = stations.begin(); it2 != stations.end(); it2++ )
		{ 
			if( (*it1)->getGUID() == (*it2)->getGUID()
				&& (*it1) != (*it2) )
			{
				cout << "double Station found: " << (*it1)->getFormatedStation() << endl;
			}
		}	
	}
*/
};

void PF::startSearch( Station* station_start, Station* station_end )
{
	this->station_start = station_start;
	this->station_start->str_routeToThisStation = "Start at "+station_start->getFormatedStation()+"\n";
	this->station_end = station_end;

	this->startStation_GUID = station_start->getGUID();
	this->endStation_GUID = station_end->getGUID();

	//init the return string
	this->str_bestConnection = "From " + station_start->getFormatedStation() + " to " + station_end->getFormatedStation() + "\n";

	//station_start is first point to check
	this->initWithStation( station_start );

	//BEGINN SEARCH
	if( DEBUG ) cout << endl << "Beginn at " << station_start->getFormatedStation() << endl;
	bool b_endStationFound = false;

	int i_steps = 0;
	while( !b_endStationFound )
	{
		//go 4 every Station* one step further
		for( this->it_stationToCheck = this->stationsToCheck.begin(); this->it_stationToCheck != stationsToCheck.end(); ++this->it_stationToCheck )
		{

			if( this->isTargetStation( (*this->it_stationToCheck) ) )
			{
				if( DEBUG ) cout << "PF::startSearch: targetStation found " << (*this->it_stationToCheck)->getFormatedStation() << endl;
				
				//add last station tostr_route
				(*this->it_stationToCheck)->str_routeToThisStation += "|arrived at " + (*this->it_stationToCheck)->getFormatedStation();

				this->str_bestConnection = (*this->it_stationToCheck)->str_routeToThisStation;
				b_endStationFound = true;
				break;
			}

			//check 4 already visited Stations
			if( (*this->it_stationToCheck)->isVisited() )
			{
				if( DEBUG ) cout << "PF::startSearch: found visited Station " << (*this->it_stationToCheck)->getFormatedStation() << " , break !" << endl;

				//remove this station from stationsToCheck
				this->it_stationToCheck = this->stationsToCheck.erase( this->it_stationToCheck )-1;
				this->index_stationsToCheck--;
			}
			else
			{
				(*this->it_stationToCheck)->setVisited( true );
				if( DEBUG ) cout << "\tPF::startSearch: visit Station " << (*this->it_stationToCheck)->getFormatedStation() << endl;
			}

			switch( (*this->it_stationToCheck)->typ )
			{
				case STATION_NORMAL:
				{
					//HANDLE NORMAL STATION WITH 1 OR 2 CONNECTIONS TO THE SAME LINE
					int possibleNextStationsCount = (*this->it_stationToCheck)->possible_next_stations.size();
					switch( possibleNextStationsCount )
					{
						case 0:
						{
							if( DEBUG ) cout << "PF::startSearch: Station with 0 possible_next_stations, eraseing." << endl;
							//remove this station from stationsToCheck
							this->it_stationToCheck = this->stationsToCheck.erase( this->it_stationToCheck );
						}
						break;

						case 1:
						{
							if( !(*this->it_stationToCheck)->possible_next_stations[0]->isVisited() )
							{
								(*this->it_stationToCheck) = (*this->it_stationToCheck)->possible_next_stations[0];
							}
						}
						break;

						case 2:
						{
							if( !(*this->it_stationToCheck)->possible_next_stations[0]->isVisited() )
							{
								(*this->it_stationToCheck) = (*this->it_stationToCheck)->possible_next_stations[0];
								break;
							}
							if( !(*this->it_stationToCheck)->possible_next_stations[1]->isVisited() )
								(*this->it_stationToCheck) = (*this->it_stationToCheck)->possible_next_stations[1];
						}
						break;
					}
				}
				break;

				case STATION_CROSS:
				{
					//HANDLE CROSS STATION WITH CONNECTINOS TO ANOTHER LINE
					this->analyseStation( (*this->it_stationToCheck) );
				}
				break;
			}

			this->index_stationsToCheck++;
		}

		this->index_stationsToCheck = 0;
		if( DEBUG ) cout << i_steps << ") ------------------------------------------------------------------------------------" << endl;
		i_steps++;

		if( this->stationsToCheck.size() == 0 )
		{
			std::cout << "PF::startSearch Internal Error: no more stationsToCheck, exit." << endl;
			break;
		}
	}

	std::cout << "EndStation found after " << i_steps << " steps." << std::endl;
};

std::string PF::printBestConnection( void )
{
	return this->str_bestConnection;
};

void PF::initWithStation( Station* stationToUse4Init )
{
	int possibleNextStationCount = 0;
	switch( stationToUse4Init->typ )
	{

		case STATION_CROSS: //add all Stations from other line
		{
			possibleNextStationCount = stationToUse4Init->connections_to_other_line.size();
			if(DEBUG) cout << "PF::initWithStation " << stationToUse4Init->getFormatedStation() << " is STATION_CROSS has " << possibleNextStationCount << " possibleNextStations" << endl;
			std::vector<Station*>::iterator it_station;
			for( it_station = stationToUse4Init->connections_to_other_line.begin(); it_station != stationToUse4Init->connections_to_other_line.end(); it_station++ )
			{
				std::vector<Station*>::iterator it_station_sub;
				for( it_station_sub = (*it_station)->possible_next_stations.begin(); it_station_sub != (*it_station)->possible_next_stations.end(); it_station_sub++ )
				{
					(*it_station_sub)->str_routeToThisStation = stationToUse4Init->str_routeToThisStation;
					if(DEBUG) cout << "PF::initWithStation stationsToCheck.push_back( " << (*it_station_sub)->getFormatedStation() << " )" << endl;
					this->stationsToCheck.push_back( (*it_station_sub) );
					(*it_station_sub)->str_routeToThisStation = stationToUse4Init->str_routeToThisStation;
				}

				//this is a substation of our start_Station, d.h. is visited
				(*it_station)->setVisited( true );
			}
		}

		case STATION_NORMAL: //add all Stations from this line
		{
			possibleNextStationCount = stationToUse4Init->possible_next_stations.size();
			if(DEBUG) cout << "PF::initWithStation " << stationToUse4Init->getFormatedStation() << " is STATION_NORMAL has " << possibleNextStationCount << " possibleNextStations" << endl;
			std::vector<Station*>::iterator it_station;
			for( it_station = stationToUse4Init->possible_next_stations.begin(); it_station != stationToUse4Init->possible_next_stations.end(); it_station++ )
			{
				(*it_station)->str_routeToThisStation = stationToUse4Init->str_routeToThisStation;
				if(DEBUG) cout << "PF::initWithStation stationsToCheck.push_back( " << (*it_station)->getFormatedStation() << " )" << endl;
				this->stationsToCheck.push_back( (*it_station) );
				(*it_station)->str_routeToThisStation = stationToUse4Init->str_routeToThisStation;
			}
		}
		break;

	}
	//our main start_Station is visited to
	stationToUse4Init->setVisited(true);
};

//funktion zum hinzufügen von neuen Knotenpunkten
void PF::analyseStation( Station* stationToAnalyse )
{
	//search each possible_next_stations and add it to stationsToCheck
	int possibleNextStationCount = stationToAnalyse->connections_to_other_line.size();


	//ADD OTHER CROSS_STATIONS
	if( DEBUG ) cout << "PF::analyseStation: " << stationToAnalyse->getFormatedStation() << " is X-Station with " << possibleNextStationCount << " possibleNextStations: Add unvisited" << endl;
	std::vector<Station*>::iterator it_station;
	for( it_station = stationToAnalyse->connections_to_other_line.begin(); it_station != stationToAnalyse->connections_to_other_line.end(); it_station++ )
	{
		if( (*it_station)->isVisited() )
		{
			
		}
		else
		{
			if( DEBUG ) cout << "PF::analyseStation: STATION_CROSS stationsToCheck.push_back( " << (*it_station)->getFormatedStation() << " )" << endl;
			this->stationsToCheck.push_back( (*it_station) );

			//update the route
			(*it_station)->str_routeToThisStation = stationToAnalyse->str_routeToThisStation;
			(*it_station)->str_routeToThisStation += "|travel " + stationToAnalyse->getFormatedStation()+"\n";
		}
	}

	//ADD OTHER NORMAL_STATIONS
	for( it_station = stationToAnalyse->possible_next_stations.begin(); it_station != stationToAnalyse->possible_next_stations.end(); it_station++ )
	{
		if( (*it_station)->isVisited() )
		{
			
		}
		else
		{
			if( DEBUG ) cout << "PF::analyseStation: STATION_NORMAL stationsToCheck.push_back( " << (*it_station)->getFormatedStation() << " )" << endl;
			this->stationsToCheck.push_back( (*it_station) );

					//update the route
			(*it_station)->str_routeToThisStation = stationToAnalyse->str_routeToThisStation;
			(*it_station)->str_routeToThisStation += "|travel " + stationToAnalyse->getFormatedStation()+"\n";
		}
	}
 
	if( DEBUG ) cout << possibleNextStationCount << "*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	this->it_stationToCheck = this->stationsToCheck.begin() + this->index_stationsToCheck;

};

//function to check, if stationToCheck is our targetStation
bool PF::isTargetStation( Station* stationToCheck )
{
	if( stationToCheck->getStationName().compare( this->station_end->getStationName() ) == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
};
