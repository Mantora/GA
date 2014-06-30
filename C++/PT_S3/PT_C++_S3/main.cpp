#include <stdio.h>

#include "XMLReader.h"
#include "Station.h"

#include "PF.h" // <- PathFinding class für StationPathFinding
#include "Timer.h"
#include "CustomTime.h"

int main ()
{
	//setze consolenfenster name
	system( "title PT PR320 - Advanced C++" );
	cout << "Praxistest C++: Pathfinding Stations geladen aus xml Datei" << endl;

	std::vector<Station*> stations;
	//variablen vorbereiten
	PF* pf = new PF();

	Station* prev_station = 0;
	Station* current_station = 0;
	Station* next_station = 0;

	Station* cross_station = 0;

	/* ANFANG LESEN XML DATEI */
	XMLReader xml_reader( "net.xml" );
//	XMLReader xml_reader( "unittest_net.xml" );
//	XMLReader xml_reader( "unittest_net_doubleline.xml" );
//	XMLReader xml_reader( "unittest_doubleline_simpel.xml" );

	XML_element readed_element;

	while( readed_element.typ != XML_ELEMENT_TYP_FINISHED )
	{
		readed_element = xml_reader.getNext();

		//lese bis <line> beginnt
		if( readed_element.typ == XML_ELEMENT_TYP_BEGINN_ELEMENT
			&& readed_element.name.compare( "line" ) == 0 )
		{
			//setze variabeln zurück
			prev_station = 0;
			current_station = 0;
			next_station = 0;

			cross_station = 0;

			//lese den line name
			readed_element = xml_reader.getNext();

			std::string lineName = readed_element.value;

			if( DEBUG_XML ) cout << "lineName: " << readed_element.value << endl;
			readed_element = xml_reader.getNext();
			
/**************************** START lesen von operation_time ****************************/
			while( readed_element.typ != XML_ELEMENT_TYP_ATTRIBUT
				|| readed_element.name.compare( "start" ) != 0 )
			{
				readed_element = xml_reader.getNext();
			}
			string str_operationTime_start( readed_element.value );

			while( readed_element.typ != XML_ELEMENT_TYP_ATTRIBUT
				|| readed_element.name.compare( "end" ) != 0 )
			{
				readed_element = xml_reader.getNext();
			}
			string str_operationTime_end( readed_element.value );
/**************************** ENDE lesen von operation_time ****************************/

			//lese jede station
			while( readed_element.typ != XML_ELEMENT_TYP_END_ELEMENT 
				|| readed_element.name.compare( "stations" ) != 0 )
			{

				if( readed_element.name.compare( "station" ) == 0
					&& readed_element.typ == XML_ELEMENT_TYP_BEGINN_ELEMENT )
				{
					int journey_time = 0;
					//lese solange, bis der string gefunden wurde
					while( readed_element.typ != XML_ELEMENT_TYP_STRING_ELEMENT )
					{
						if( readed_element.name.compare( "journey_time" ) == 0 )
						{
							journey_time = atoi( readed_element.value.c_str() );
						}

						readed_element = xml_reader.getNext();
					}

					//DEBUG: ausgabe von station name
					if( DEBUG_XML ) cout << readed_element.name << endl;

					/* BAU DIE MULTI_LINKED_LIST FÜR JEDE STATION */

					//prüfe, ob die current_station die momentane station ist, die wir instanziieren wollen
					if( current_station == 0
						|| current_station->station_name.compare( readed_element.name ) != 0 )
					{
						//store the station as new Station instance
						current_station = new Station( journey_time, readed_element.name, lineName );
						current_station->setOperationTime( str_operationTime_start, str_operationTime_end );
					}


					//wenn es eine frühere Station haben, setzen als möglich nächste Station
					if( prev_station != 0 ) //FORWARD & BACKWARD
					{
						//setzen von prev_station "Real_Next_Station" von current_station
						prev_station->addPosibleNextStation( current_station );
						current_station->addPosibleNextStation( prev_station );

						prev_station = 0;
					
					}

					//Steichere Station in stations
					stations.push_back( current_station );

					prev_station = current_station;
				}

				readed_element = xml_reader.getNext();
			}
		}
	}

	/* ENDE LESEN VON XML DATEI */
	if( DEBUG_STATIONS ) cout << stations.size() << " stations loaded." << endl;

	//verbinde die Stationen, die eine Verbindung zu einer anderen Linie haben
	std::vector<Station*>::iterator it = stations.begin();
	for( it = stations.begin(); it != stations.end(); it++ )
	{
		std::vector<Station*>::iterator it_sub = it+1;
		for( it_sub; it_sub != stations.end(); it_sub++ )
		{
			if( (*it)->station_name.compare( (*it_sub)->station_name ) == 0 )
			{
				// selben Stationsnamen gefunden
				(*it)->addConnectionToOtherLine( (*it_sub) );
				(*it)->typ = STATION_CROSS;

				(*it_sub)->addConnectionToOtherLine( (*it) );
				(*it_sub)->typ = STATION_CROSS;
			}
		}
	}

	/* ANFANG EINFABE: START_STATION, END_STATION, TIME_ARRIVE */
	std::string startStation_name;
	Station* startStation_ptr = 0;

	std::string endStation_name;
	Station* endStation_ptr = 0;

	CustomTime ct_travelStart;

	while( startStation_ptr == 0 && endStation_ptr == 0 )
	{
		//ORGINAL STATIONS
		#ifdef _DEBUG
			// benutze def. werte wenn im Debug Modus
			startStation_name = "S Hennigsdorf";
			endStation_name = "S+U Tegel";

			// 4 use on unittest.xml:
//			startStation_name = "START";
//			endStation_name = "END";

			ct_travelStart = CustomTime( "03:30" ); //<- must hh:mm for debug or unknown behaviour occur

			for( std::vector<Station*>::iterator it = stations.begin(); it != stations.end(); it++ )
			{
				if( (*it)->station_name.compare( startStation_name ) == 0 )
				{
					if( DEBUG_STATIONS ) cout << "found " << (*it)->getFormatedStation() << endl;
					startStation_ptr = (*it);
					break;
				}
			}

			for( std::vector<Station*>::iterator it = stations.begin(); it != stations.end(); it++ )
			{
				if( (*it)->station_name.compare( endStation_name ) == 0 )
				{
					if( DEBUG_STATIONS ) cout << "found " << (*it)->getFormatedStation() << endl;				
					endStation_ptr = (*it);
				}
			}
		#endif

			cout << endl;

		#ifndef _DEBUG
		//search 4 a specific station:
		//START Station
		while( startStation_ptr == 0 )
		{
			if( startStation_ptr == 0 )
			{
				cout << "Input your starting Station: ";
				char carr_startStationName[128] = {0};
				cin.getline( carr_startStationName, 128);
				startStation_name = std::string(carr_startStationName);
			}

			for( std::vector<Station*>::iterator it = stations.begin(); it != stations.end(); it++ )
			{
				if( (*it)->station_name.compare( startStation_name ) == 0 )
				{
					if( DEBUG_STATIONS ) cout << "found " << (*it)->getFormatedStation() << endl;
					startStation_ptr = (*it);
					break;
				}
			}

			if( startStation_ptr == 0 )
			{
				cout << "StartStation not found !" << endl;
				cout << "Please reinput the Name." << endl;
			}
		}

		//END Station
		while( endStation_ptr == 0 )
		{
			if( endStation_ptr == 0 )
			{
				cout << "Input your end Station: ";
				char carr_endStationName[128] = {0};
				cin.getline( carr_endStationName, 128);		
				endStation_name = std::string(carr_endStationName);
			}

			for( std::vector<Station*>::iterator it = stations.begin(); it != stations.end(); it++ )
			{
				if( (*it)->station_name.compare( endStation_name ) == 0 )
				{
					if( DEBUG_STATIONS ) cout << "found " << (*it)->getFormatedStation() << endl;
					endStation_ptr = (*it);
					break;
				}
			}	

			if( endStation_ptr == 0 )
			{
				cout << "EndStation not found !" << endl;
				cout << "Please reinput the Name." << endl;
			}
		}

		//STARTING TIME
		while( ct_travelStart.currentTime == 0 )
		{
			if( ct_travelStart.currentTime == 0 )
			{
				cout << "Input your Starting Time (hh:mm): ";
				
				std::string str_startingTime;
				cin >> str_startingTime;

				ct_travelStart = CustomTime( str_startingTime );
			}

			if( ct_travelStart.currentTime == 0 )
			{
				cout << "Time has wrong format, plz input something like \"08:05\" or \"15:25\"" << endl;
			}
		}
#endif
	}
	

//	cout << "endStation_ID:" << endStation_ID << endl;
//	cout << "startStation_ID:" << startStation_ID << endl;

	// set the datas to PF
	pf->stations = stations;

	// SUCHE NACH BESTER VERBINDUNG
	Timer t;
	std::vector<Station*> route = pf->startSearch( startStation_ptr, endStation_ptr, ct_travelStart );
	int pf_ms = t.getMSecSinceStart();

	cout << endl;
	if( SHOW_MSEC_NEEDED )cout << "PERFORMANCE: PF needed " << pf_ms << " ms to find target." << endl << endl;

	cout << "Route from: " << startStation_ptr->getFormatedStation4Route() << endl;
	cout << "to:         " << endStation_ptr->getFormatedStation4Route() <<  endl;
	cout << "at:         " << ct_travelStart.toString() << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "Linie  Station                                 Dauer" << endl;
	for( std::vector<Station*>::iterator it = route.begin(); it != route.end(); it++ )
	{
		cout << (*it)->getFormatedStation4Route() << endl;
	}


	if( DEBUG_CLEANUP) cout << "stations.size():" << stations.size() << endl;
	if( DEBUG_CLEANUP) cout << "pf->stations.size():" << pf->stations.size() << endl;

	//cleanup:
	stations.clear();
	delete pf;

	if( DEBUG_CLEANUP)cout << "stations.size():" << stations.size() << endl;
	if( DEBUG_CLEANUP)cout << "pf->stations.size():" << pf->stations.size() << endl;

	cout << endl;
	system("pause");
	return 0;
}
