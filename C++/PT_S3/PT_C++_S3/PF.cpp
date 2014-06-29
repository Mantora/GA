#include "PF.h"
#include "Utility.h"
#include <iostream>

#include "Station.h"
#include "Timer.h"

using namespace std;

PF::PF()
{
	this->stop = false;

	this->stationsToAnalyse = std::vector<Station*>();
	this->stationsToAnalyseNext = std::vector<Station*>();

	this->calculationSteps = 0;
}

PF::~PF( void )
{

}

void PF::startSearch( Station* station_start, Station* station_end, CustomTime& ct_startTravel )
{
	Utility::resetGUIDs();

	this->s_start = station_start;
	this->s_end = station_end;
	this->ct_start = ct_startTravel;

	// da du hier startest, hast du die startStation schon besucht

	station_start->journey_time = 0;
	// die journey Time alle CROSS STATIONs auf 0 setzten: Wir sind ja schon da
	for( std::vector<Station*>::iterator it = station_start->connections_to_other_line.begin(); it != station_start->connections_to_other_line.end(); it )
	{
		(*it)->journey_time = 0;
		this->stationsToAnalyse.push_back( (*it) );
		it++;
	}

	// untersuche die start Station
	this->stationsToAnalyse.push_back(station_start);

	//solange die Stationen durchsuchen, bis wir fertig sind
	while( !this->stop )
	{
		this->calculationSteps++;
		if( DEBUG_STATIONS ) cout << this->calculationSteps << "#" << endl;

		// alle stationen analysieren, die da sind:
		for( std::vector<Station*>::iterator it = this->stationsToAnalyse.begin(); it != this->stationsToAnalyse.end(); it++ )
		{
 			this->analyseStation( (*it) );
		}

		// swap vectors
		this->stationsToAnalyse = this->stationsToAnalyseNext;
		this->stationsToAnalyseNext.clear();

//		system("pause");
	}
}

void PF::analyseStation( Station* s )
{
	if( this->stop )
		return;

	if( DEBUG_STATIONS ) cout << "analyseStation: " << s->getFormatedStation() << endl;

	if( s->visited )
	{
		if( DEBUG_STATIONS ) cout << s->getFormatedStation() << " is visited, return" << endl;
		return;
	}

	if( s->journey_time > 0 )
	{
		if( DEBUG_STATIONS ) cout << " traveling to " << s->getFormatedStation() << " r=" << s->journey_time << endl;
		s->journey_time--;
		this->stationsToAnalyseNext.push_back( s );
		return;
	}
	else
	{
		s->visited = true;
		s->pathfindingOrder = this->calculationSteps;
	}

	if( s->GUID == this->s_end->GUID )
	{
		this->finalStationFound( s );
		return;
	}
	// teste ob verbindung zur anderen Liene in dieser Station unser Ziel ist
	for( std::vector<Station*>::iterator it = s->connections_to_other_line.begin(); it != s->connections_to_other_line.end(); it++ )
	{
		if( (*it)->GUID == this->s_end->GUID )
		{
			if( DEBUG_STATIONS ) cout << "finalStationFound as connection to other line from " << s->getFormatedStation() << endl;
			this->finalStationFound( (*it) );
			return;
		}
	}

	// alle verbindungen zu einer anderen Linie ansehen
	for( std::vector<Station*>::iterator it = s->connections_to_other_line.begin(); it != s->connections_to_other_line.end(); it++ )
	{
		for( std::vector<Station*>::iterator it2 = (*it)->possible_next_stations.begin(); it2 != (*it)->possible_next_stations.end(); it2++ )
		{
			this->stationsToAnalyseNext.push_back( (*it2) );
		}
	}
}

void PF::finalStationFound( Station* s )
{
	//DEBUG
	for( std::vector<Station*>::iterator it = this->stations.begin(); it != this->stations.end(); it++ )
	{
		if( DEBUG_STATIONS ) cout << (*it)->getFormatedStation() << " PForder=" << (*it)->pathfindingOrder << endl;
	}

	this->stop = true;
	s->visited = false;
	if( DEBUG_STATIONS ) cout << "End Station Found: " << s->getFormatedStation() << " after " << this->calculationSteps << " steps." << endl;
//	system("pause");

	if( DEBUG_STATIONS ) cout << "Reihenfolge:" << endl;

	std::vector<Station*> reverseSearch = std::vector<Station*>();
	std::vector<Station*> reverseSearch_2 = std::vector<Station*>();

	// vector zum speichern der entgültigen Route
	std::vector<Station*> finalRoute = std::vector<Station*>();
	// letzte Station merken
	finalRoute.push_back( s );
	Station* nextFinalStation = s; // s nur damit wir einen pathfindingOrder zum vergleichen haben

	reverseSearch.push_back( s );

	bool stop = false;
	for( std::vector<Station*>::iterator it = reverseSearch.begin(); it != reverseSearch.end(); it )
	{
		if( stop )
			break;

		switch( (*it)->typ )
		{
			case STATION_CROSS:
			{
				for( std::vector<Station*>::iterator it2 = (*it)->connections_to_other_line.begin(); it2 != (*it)->connections_to_other_line.end(); it2++ )
				{
					if( stop )
						break;

					//DEBUG
					if( (*it2)->pathfindingOrder == 3 ) 
						cout << endl;

					// keine station beachten, die einen höheren pfOrder haben als die momentane Station
					if( (*it2)->pathfindingOrder > (*it)->pathfindingOrder )
						break;

					if( (*it2)->journey_time > 0 )
						break;

					for( std::vector<Station*>::iterator it3 = (*it2)->possible_next_stations.begin(); it3 != (*it2)->possible_next_stations.end(); it3++ )
					{
						if( stop )
							break;

						// wenn wir wieder am anfang sind, beenden
						if( this->isStartStation( (*it3) ) )
						{
							nextFinalStation = (*it3);
							stop = true;
							break;
						}

						if(  (*it3)->journey_time == 0 && (*it3)->visited == true
							&& (*it3)->pathfindingOrder < nextFinalStation->pathfindingOrder )
						{
							nextFinalStation = (*it3);

							reverseSearch_2.push_back( (*it3) );
							// besucht auf falsch setzten damit diese station nicht mehrfach vorkommt
							(*it3)->visited = false;
						}
					}
				}
			}
			//break;
			case STATION_NORMAL:
			{
				if( stop )
					break;

				for( std::vector<Station*>::iterator it2 = (*it)->possible_next_stations.begin(); it2 != (*it)->possible_next_stations.end(); it2++ )
				{
					if( stop )
						break;
					
					// wenn wir wieder am anfang sind, beenden
					if( isStartStation( (*it2) ) )
					{
						nextFinalStation = (*it2);
						stop = true;
						break;
					}

					if( (*it2)->journey_time == 0 && (*it2)->visited == true
						&& (*it2)->pathfindingOrder < nextFinalStation->pathfindingOrder )
					{
						nextFinalStation = (*it2);
						reverseSearch_2.push_back( (*it2) );

						// besucht auf falsch setzten damit diese station nicht mehrfach vorkommt
						(*it2)->visited = false;
					}
				}
			}
			break;
		}

		reverseSearch = reverseSearch_2;
		reverseSearch_2 = std::vector<Station*>();

		it = reverseSearch.begin();

		finalRoute.push_back( nextFinalStation );
	}

	//erste Station merken
//	finalRoute.push_back( this->s_start );

	//ausgabe
	for( std::vector<Station*>::iterator it = finalRoute.end(); it != finalRoute.begin(); it )
	{
		it--;
		if( DEBUG_STATIONS ) cout << (*it)->getFormatedStation() << endl;
	}
	
//	system("pause");

}

// durchsucht auch alle connections_to_other_line s
bool PF::isFinalStation( Station* s )
{
	switch( s->typ )
	{
		case STATION_CROSS:
		{
			for( std::vector<Station*>::iterator it = s->connections_to_other_line.begin(); it != s->connections_to_other_line.end(); it++ )
			{
				if( (*it)->GUID == this->s_end->GUID )
					return true;
			}
		}
//		break;
		case STATION_NORMAL:
		{
			if( s->GUID == this->s_end->GUID )
				return true;
		}
		break;
	}

	return false;
}

// durchsucht auch alle connections_to_other_line s
bool PF::isStartStation( Station* s )
{
	switch( s->typ )
	{
		case STATION_CROSS:
		{
			for( std::vector<Station*>::iterator it = s->connections_to_other_line.begin(); it != s->connections_to_other_line.end(); it++ )
			{
				if( (*it)->GUID == this->s_start->GUID )
					return true;
			}
		}
		break;

		case STATION_NORMAL:
		{
			if( s->GUID == this->s_start->GUID )
				return true;
		}
		break;
	}

	return false;
}