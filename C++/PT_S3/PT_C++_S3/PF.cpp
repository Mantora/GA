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
	station_start->visited = true;
	station_start->journey_time = 0;
	// die journey Time alle CROSS STATIONs auf 0 setzten: Wir sind ja schon da
	for( std::vector<Station*>::iterator it = station_start->connections_to_other_line.begin(); it != station_start->connections_to_other_line.end(); it )
	{
		(*it)->journey_time = 0;
		(*it)->visited = true;
		it++;
	}

	// untersuche die start Station
	this->stationsToAnalyse.push_back(station_start);

	//solange die Stationen durchsuchen, bis wir fertig sind
	while( !this->stop )
	{
		cout << this->calculationSteps << "#" << endl;
		// alle stationen analysieren, die da sind:
		for( std::vector<Station*>::iterator it = this->stationsToAnalyse.begin(); it != this->stationsToAnalyse.end(); it )
		{
			// aber nur unbesuchte
			this->analyseStation( (*it) );

			it++;
		}

		// swap vectors
		this->stationsToAnalyse = this->stationsToAnalyseNext;
		this->stationsToAnalyseNext.clear();

		this->calculationSteps++;
//		system("pause");
	}
}

void PF::analyseStation( Station* s )
{
// DEBUG:
//	if( s->line_name.compare("L") == 0 )
//		cout << endl;

	// haben wir die zielstation gefunden ?
	if( this->stop )
		return;

	if( DEBUG_STATIONS ) cout << " analyseStation: " << s->getFormatedStation() << endl;

	// sind wir an dieser Station ?
	if( s->journey_time > 0 )
	{
		// nein, fahren
		s->journey_time -= 1;
		if( s->journey_time == 0 )
		{
			cout << "  now on " << s->getFormatedStation() << ", analyse again" << endl;
			this->analyseStation(s);
		}
		else
		{
			this->stationsToAnalyseNext.push_back( s );
			cout << "  traveling on " << s->getFormatedStation() << " r=" << s->journey_time << endl;
		}
		return;
	}

	// ist das unsere Ziel Station?
	if( s->GUID == this->s_end->GUID )
	{
		// ja
		if( DEBUG_STATIONS ) cout << "  targetStationFound: " << s->getFormatedStation() << endl;
		this->finalStationFound( s );
		return;
	}
	// prüfen ob ein teil dieser Station unser Ziel ist
	else if( s->typ == STATION_CROSS )
	{
		std::vector<Station*>::iterator it;
		for( std::vector<Station*>::iterator it = s->connections_to_other_line.begin(); it != s->connections_to_other_line.end(); it )
		{
			if( (*it)->GUID == this->s_end->GUID )
			{
				if( DEBUG_STATIONS ) cout << "  targetStationFound as STATION_CROSS from : " << s->getFormatedStation() << endl;
				this->finalStationFound( s );
				return;
			}
			it++;
		}
	}

	// wir sind jetzt an dieser Station
	s->visited = true;

	//iterator vorbereiten
	std::vector<Station*>::iterator iter;

	// zwischen StationsTypen unterscheiden
	switch( s->typ )
	{
		case STATION_CROSS:
		{
			// diese Station hat eine verbindung zu einer anderen Linie
			for( iter = s->connections_to_other_line.begin(); iter != s->connections_to_other_line.end(); iter )
			{
				// nicht die anderen CROSS_STATIONs betrachten,
				// sondern deren verbindungen
				std::vector<Station*>::iterator it2;
				for( it2 = (*iter)->possible_next_stations.begin(); it2 != (*iter)->possible_next_stations.end(); it2 )
				{
					// nur unbesuchte beachten
					if( !(*it2)->visited 
						&& (*it2)->pathfindingOrder == 0 )
					{
//(*it2)->pathfindingOrder = this->calculationSteps;
(*it2)->pathfindingOrder = Utility::getNewGUID();
						if( DEBUG_STATIONS ) cout << "  STATION_CROSS analyseStation: " << (*it2)->getFormatedStation() << " #" << (*it2)->pathfindingOrder << endl;
						this->stationsToAnalyseNext.push_back( (*it2) );
					}
					it2++;
				}

				// diese CROSS STATION wurde besucht
				(*iter)->visited = true;

				iter++;
			}
		}
		//break; // kein break, CROSS STATION muss CROSS verb. und NORMALE verb. nehmen
		case STATION_NORMAL:
		{
			// normale station auf einer Linie:
			// mögliche stationen betrachten
			for( iter = s->possible_next_stations.begin(); iter != s->possible_next_stations.end(); iter )
			{
				// nur unbesuchte beachten
				if( !(*iter)->visited
					&& (*iter)->pathfindingOrder == 0 )
				{
//(*iter)->pathfindingOrder = this->calculationSteps;
(*iter)->pathfindingOrder = Utility::getNewGUID();
					if( DEBUG_STATIONS ) cout << "  STATION_NORMAL analyseStation: " << (*iter)->getFormatedStation() << " #" << (*iter)->pathfindingOrder << endl;
					this->stationsToAnalyseNext.push_back( (*iter) );
				}

				iter++;
			}
		}
		break;
	}
}

void PF::finalStationFound( Station* s )
{
	//DEBUG
	for( std::vector<Station*>::iterator it = this->stations.begin(); it != this->stations.end(); it++ )
	{
		cout << (*it)->getFormatedStation() << " PForder=" << (*it)->pathfindingOrder << endl;
	}

	this->stop = true;
	s->visited = false;
	cout << "End Station Found: " << s->getFormatedStation() << " after " << this->calculationSteps << " steps." << endl;
//	system("pause");

	cout << "Reihenfolge:" << endl;

	std::vector<Station*> reverseSearch = std::vector<Station*>();
	std::vector<Station*> reverseSearch_2 = std::vector<Station*>();

	// vector zum speichern der entgültigen Route
	std::vector<Station*> finalRoute = std::vector<Station*>();
	// letzte Station merken
	finalRoute.push_back( s );
	Station* nextFinalStation = 0; // s nur damit wir einen pathfindingOrder zum vergleichen haben

	reverseSearch.push_back( s );

	for( std::vector<Station*>::iterator it = reverseSearch.begin(); it != reverseSearch.end(); it )
	{
		nextFinalStation = 0;
untersuche reihenfolge der pathfindingOrder beim vector bauen der endgültigen verbindung
		switch( (*it)->typ )
		{
			case STATION_CROSS:
			{
				for( std::vector<Station*>::iterator it2 = (*it)->connections_to_other_line.begin(); it2 != (*it)->connections_to_other_line.end(); it2 )
				{
					// wenn wir wieder am anfang sind, beenden
					if( (*it2)->GUID == this->s_start->GUID )
						break;

					if( (*it2)->journey_time == 0 && (*it2)->visited == true
						&& (*it2)->pathfindingOrder > finalRoute.back()->pathfindingOrder )
					{
						nextFinalStation = (*it2);
						reverseSearch_2.push_back( (*it2) );

						// besucht auf falsch setzten damit diese station nicht mehrfach vorkommt
						(*it2)->visited = false;
					}

					it2++;
				}
			}
			//break;
			case STATION_NORMAL:
			{
				for( std::vector<Station*>::iterator it2 = (*it)->possible_next_stations.begin(); it2 != (*it)->possible_next_stations.end(); it2 )
				{
					// wenn wir wieder am anfang sind, beenden
					if( (*it2)->GUID == this->s_start->GUID )
						break;

					if( (*it2)->journey_time == 0 && (*it2)->visited == true
						&& (*it2)->pathfindingOrder < finalRoute.back()->pathfindingOrder )
					{
						nextFinalStation = (*it2);
						reverseSearch_2.push_back( (*it2) );

						// besucht auf falsch setzten damit diese station nicht mehrfach vorkommt
						(*it2)->visited = false;
					}

					it2++;
				}
			}
			break;
		}

		reverseSearch = reverseSearch_2;
		reverseSearch_2 = std::vector<Station*>();

		it = reverseSearch.begin();

		if( nextFinalStation != 0 )
			finalRoute.push_back( nextFinalStation );
	}

	//erste Station merken
	finalRoute.push_back( this->s_start );

	//ausgabe
	for( std::vector<Station*>::iterator it = finalRoute.end(); it != finalRoute.begin(); it )
	{
		it--;
		cout << (*it)->getFormatedStation() << endl;
	}
	
	system("pause");

}