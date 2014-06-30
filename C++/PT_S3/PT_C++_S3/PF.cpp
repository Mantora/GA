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

	this->routeData = std::vector<Station*>();
}

PF::~PF( void )
{
	this->cleanup();
}

void PF::cleanup()
{
	this->routeData.clear();
}

void PF::setDatas( std::vector<Station*> stationDatas )
{
	this->stations = stationDatas;
}

std::vector<Station*> PF::startSearch( Station* station_start, Station* station_end, CustomTime& ct_startTravel )
{
	Utility::resetGUIDs();

	this->s_start = station_start;
	this->s_end = station_end;
	this->ct_start = ct_startTravel;

	// da du hier startest, hast du die startStation schon besucht
	station_start->analysed = true;

	station_start->journey_time_pf = 0;
	// die journey Time alle CROSS STATIONs auf 0 setzten: Wir sind ja schon da
	for( std::vector<Station*>::iterator it = station_start->connections_to_other_line.begin(); it != station_start->connections_to_other_line.end(); it )
	{
		(*it)->journey_time_pf = 0;
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

	return this->routeData;
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

	if( s->journey_time_pf > 0 )
	{
		if( DEBUG_STATIONS ) cout << " traveling to " << s->getFormatedStation() << " r=" << s->journey_time_pf << endl;
		s->journey_time_pf--;
		this->stationsToAnalyseNext.push_back( s );
		return;
	}
	else
	{
		s->visited = true;
		s->pathfindingOrder = this->calculationSteps;
		if( DEBUG_STATIONS ) cout << " pf=" << s->pathfindingOrder << endl;

		// zeit bis hier hin:
		// beim startbahnhof keine Umsteigzeig berechnen
		if( s->pathfindingOrder == 1 )
			s->AddRouteTimeToAllStations( s->journey_time );
		else
			s->AddRouteTimeToAllStations( s->journey_time + ADDITIONL_MINUTES_TO_BOARDING );

		s->SetTotalRouteTimeToAllStations( s->routeTimeToThisStation.currentTime + s->totalRouteTime.currentTime );
	}

	if( this->isFinalStation(s) )
	{
		this->finalStationFound( s );
		return;
	}

	switch( s->typ )
	{
		case STATION_CROSS:
		{
			// alle verbindungen zu einer anderen Linie ansehen
			for( std::vector<Station*>::iterator it = s->connections_to_other_line.begin(); it != s->connections_to_other_line.end(); it++ )
			{
				//wir sind jetzt hier, markieren:
				(*it)->pathfindingOrder = this->calculationSteps;
				(*it)->analysed = true;
				(*it)->visited = true;
				(*it)->journey_time_pf = 0;

				//davon die Linien Verbindungen
				for( std::vector<Station*>::iterator it2 = (*it)->possible_next_stations.begin(); it2 != (*it)->possible_next_stations.end(); it2++ )
				{
					if( !(*it2)->analysed )
					{
						if( DEBUG_STATIONS ) cout << " add from STATION_CROSS: " << (*it2)->getFormatedStation() << endl;
						(*it2)->analysed = true;
						
						// prüfen, ob zu dieser Station gefahren werden kann, oder man laufen muss
						(*it2)->SetTotalRouteTimeToAllStations( s->totalRouteTime.currentTime );
						if( DEBUG_TIME ) cout << "   s->totalRouteTime from " << s->getFormatedStation() << " = " << s->totalRouteTime.toString() << endl;
						this->calculateJourneyTime( (*it2), (*it2)->totalRouteTime.currentTime + this->ct_start.currentTime ); 

						this->stationsToAnalyseNext.push_back( (*it2) );
					}
				}
			}
		}
//		break;

		case STATION_NORMAL:
		{
			// alle verbindungen von dieser Linie ansehen
			for( std::vector<Station*>::iterator it = s->possible_next_stations.begin(); it != s->possible_next_stations.end(); it++ )
			{
				if( !(*it)->analysed )
				{
					if( DEBUG_STATIONS ) cout << " add from STATION_NORMAL: " << (*it)->getFormatedStation() << endl;
					(*it)->analysed = true;

					// prüfen, ob zu dieser Station gefahren werden kann, oder man laufen muss
					(*it)->SetTotalRouteTimeToAllStations( s->totalRouteTime.currentTime );
					if( DEBUG_TIME ) cout << "   s->totalRouteTime from " << s->getFormatedStation() << " = " << s->totalRouteTime.toString() << endl;
					this->calculateJourneyTime( (*it), (*it)->totalRouteTime.currentTime + this->ct_start.currentTime); 

					this->stationsToAnalyseNext.push_back( (*it) );
				}
			}
		}
		break;
	}
}

void PF::finalStationFound( Station* s )
{
	//DEBUG
/*	for( std::vector<Station*>::iterator it = this->stations.begin(); it != this->stations.end(); it++ )
	{
		if( DEBUG_STATIONS ) cout << (*it)->getFormatedStation() << " PForder=" << (*it)->pathfindingOrder << endl;
	}
*/
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

	for( std::vector<Station*>::iterator it = reverseSearch.begin(); it != reverseSearch.end(); it )
	{
		for( std::vector<Station*>::iterator it2 = (*it)->possible_next_stations.begin(); it2 != (*it)->possible_next_stations.end(); it2++ )
		{
			if( (*it2)->visited && (*it2)->pathfindingOrder < finalRoute.back()->pathfindingOrder )
			{
				(*it2)->visited = false;
				nextFinalStation = (*it2);

				reverseSearch_2.push_back( (*it2) );
			}
		}

		it++;

		if( it == reverseSearch.end() 
			&& nextFinalStation->GUID == finalRoute.back()->GUID )
		{
			// alle verbindungen zu anderen Stationen
			for( std::vector<Station*>::iterator it2 = finalRoute.back()->connections_to_other_line.begin(); it2 != finalRoute.back()->connections_to_other_line.end(); it2++ )
			{
				for( std::vector<Station*>::iterator it3 = (*it2)->possible_next_stations.begin(); it3 != (*it2)->possible_next_stations.end(); it3++ )
				{
					if( (*it3)->visited && (*it3)->pathfindingOrder < finalRoute.back()->pathfindingOrder )
					{
						(*it3)->visited = false;
						nextFinalStation = (*it3);

						reverseSearch_2.push_back( (*it3) );
					}
				}
			}
		}

		if( it == reverseSearch.end() 
			&& !this->isStartStation(nextFinalStation) )
		{
			reverseSearch = reverseSearch_2;
			reverseSearch_2 = std::vector<Station*>();

			it = reverseSearch.begin();

			if( DEBUG_STATIONS ) cout << "BEST ROUTE REV.: " << nextFinalStation->getFormatedStation() << endl;
			finalRoute.push_back( nextFinalStation );
		}
	}

	finalRoute.push_back( this->s_start );
	
	CustomTime ct_totalRouteTime;

	for( std::vector<Station*>::iterator it = finalRoute.end(); it != finalRoute.begin(); it )
	{
		it--;
		if( DEBUG_STATIONS ) cout << (*it)->getFormatedStation() << endl;
		this->routeData.push_back( (*it) );
		ct_totalRouteTime.add( (*it)->routeTimeToThisStation.currentTime );

		// Zeit bis zu dieser Station:
		(*it)->routeTimeToThisStation.currentTime = ct_totalRouteTime.currentTime;

cout << "totalRouteTime=" << (*it)->totalRouteTime.toString() << endl;
	}

	if( DEBUG_TIME ) cout << "ct_totalRouteTime.currentTime=" << ct_totalRouteTime.toString() << endl;
	if( DEBUG_STATIONS ) system("pause");
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
				{
					s->pathfindingOrder = this->calculationSteps;
					for( std::vector<Station*>::iterator it2 = s->connections_to_other_line.begin(); it2 != s->connections_to_other_line.end(); it2++ )
					{
						(*it2)->pathfindingOrder = this->calculationSteps;
					}
					return true;
				}
			}
		}
//		break;
		case STATION_NORMAL:
		{
			if( s->GUID == this->s_end->GUID )
			{
				s->pathfindingOrder = this->calculationSteps;
				return true;
			}
		}
		break;
	}

	return false;
}

// durchsucht auch alle connections_to_other_line s
bool PF::isStartStation( Station* s )
{

					//DEBUG
	if( s->station_name.compare("START") == 0 && s->line_name.compare("M") == 0 ) 
		cout << endl;


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
//		break;
		case STATION_NORMAL:
		{
			if( s->GUID == this->s_start->GUID )
				return true;
		}
		break;
	}

	return false;
}

void PF::calculateJourneyTime( Station* s, int ct_current )
{
	// s->routeTimeToThisStation ? wird in analyseStation gesetzt, wenn man da ist
	// s->journey_time
	// s->journey_time_pf

	// müssen wir laufen?

//	if( DEBUG_TIME ) 
//		cout << "ct_current=" << ct_current << " > s->operation_time_end.currentTime=" << s->operation_time_end.currentTime << " : ";

	bool none24 = (ct_current > s->operation_time_end.currentTime) 
		&& (ct_current < s->operation_time_start.currentTime);

	if( none24 )
	{
		//laufen
		if( DEBUG_TIME ) cout << "LAUFEN: old journey_time=" << s->journey_time;

		s->journey_time *= MULTIPLAYER_IF_LINE_IS_OUT_OPERATION_TIME;
		s->journey_time_pf = s->journey_time;

		if( DEBUG_TIME ) cout << " new journey_time=" << s->journey_time << endl;
	}
	else
	{
		// nicht laufen
		if( DEBUG_TIME ) cout << "FAHREN" << endl;
	}

if( DEBUG_TIME ) cout << ct_current << ">" << s->operation_time_end.currentTime << " || " << ct_current << "<" << s->operation_time_start.currentTime << " : ";

}
