#include <stdio.h>

#include "XMLReader.h"
#include "Station.h"

#include "PF.h" // <- PathFinding class 4 Stations
#include "Timer.h"


int main ()
{
	std::vector<Station*> stations;
	//prepare variables
	PF* pf = new PF();

	Station* prev_station = 0;
	Station* current_station = 0;
	Station* next_station = 0;

	Station* cross_station = 0;

	/* BEGINN READING XML FILE */
	XMLReader xml_reader( "net.xml" );

	XML_element readed_element;

	while( readed_element.typ != XML_ELEMENT_TYP_FINISHED )
	{
		readed_element = xml_reader.getNext();

		//read till a <line> starts
		if( readed_element.typ == XML_ELEMENT_TYP_BEGINN_ELEMENT
			&& readed_element.name.compare( "line" ) == 0 )
		{
			//reset working variables
			prev_station = 0;
			current_station = 0;
			next_station = 0;

			cross_station = 0;

			//read the line name
			readed_element = xml_reader.getNext();

			std::string lineName = readed_element.value;

//			cout << "lineName: " << readed_element.value << endl;
			readed_element = xml_reader.getNext();

			while( readed_element.typ != XML_ELEMENT_TYP_END_ELEMENT 
				|| readed_element.name.compare( "stations" ) != 0 )
			{

				if( readed_element.name.compare( "station" ) == 0
					&& readed_element.typ == XML_ELEMENT_TYP_BEGINN_ELEMENT )
				{
					int journey_time = 0;
					//read untill the string is found
					while( readed_element.typ != XML_ELEMENT_TYP_STRING_ELEMENT )
					{
						if( readed_element.name.compare( "journey_time" ) == 0 )
						{
							journey_time = atoi( readed_element.value.c_str() );
						}

						readed_element = xml_reader.getNext();
					}

					//output the string (station name)
//					cout << readed_element.name << endl;

					/* BUILD THE MULTI_LINKED_LIST 4 EACH STATION */

					//check each station if the station whe want to instance already exists
/*					for( std::vector<Station*>::iterator it_existingStation = stations.begin(); it_existingStation != stations.end(); it_existingStation++ )
					{
						if( (*it_existingStation)->getStationName().compare( readed_element.name ) == 0 )
						{
							//station already exists
							(*it_existingStation)->typ = STATION_CROSS;
							current_station = (*it_existingStation);
							break;
						}
					}
*/
					bool b_addNewStation = false;


					//check, if current_station is our station whe want to instanciate
					if( current_station == 0
						|| current_station->getStationName().compare( readed_element.name ) != 0 )
					{
						//store the station as new Station instance
						current_station = new Station( journey_time, readed_element.name, lineName );
						b_addNewStation = true;
					}


					//if we have a prev_station, set it as a possible nextStation
					if( prev_station != 0 ) //FORWARD & BACKWARD
					{
						//set from prev_station "Real_Next_Station" from current_station
						prev_station->addPosibleNextStation( current_station );
						current_station->addPosibleNextStation( prev_station );
						prev_station = 0;
					
					}

					//store current station if it is an new instance
					if( b_addNewStation )
					{
						stations.push_back( current_station );
					}

					prev_station = current_station;
				}

				readed_element = xml_reader.getNext();
			}
		}
	}
	/* END READING XML FILE */
	if( DEBUG ) cout << stations.size() << " stations loaded." << endl;
	pf->setStations( stations );

	/* BEGINN 4 INPUT: START_STATION END_STATION TIME_ARRIVE*/
	std::string startStation_name;
	int startStation_ID = 0;
	Station* startStation_ptr = 0;

	std::string endStation_name;
	int endStation_ID = 0;
	Station* endStation_ptr = 0;

	while( startStation_ID == 0 && endStation_ID == 0 )
	{
		cout << "TO IMPLEMENT: change startStation_name and endStation_name to be user input" << endl;
		//DEBUG STATIONS:
//		startStation_name = "S1_0";
//		endStation_name = "S2_0";

		//ORGINAL STATIONS
		startStation_name = "S+U Jannowitzbruecke";
		endStation_name = "S+U Friedrichstr.";

		//search 4 a specific station:
		//START & END Stations
		for( std::vector<Station*>::iterator it = stations.begin(); it != stations.end(); it++ )
		{
			if( (*it)->getStationName().compare( startStation_name ) == 0 )
			{
				if( DEBUG ) cout << "found " << (*it)->getStationName() << endl;
				startStation_ID = (*it)->getGUID();
				startStation_ptr = (*it);
			}
			else if( (*it)->getStationName().compare( endStation_name ) == 0 )
			{
				if( DEBUG ) cout << "found " << (*it)->getStationName() << endl;
				endStation_ID = (*it)->getGUID();
				endStation_ptr = (*it);
			}
		}

		if( startStation_ID == 0 )
		{
			cout << "StartStation not found !" << endl;
			cout << "Please reinput the Name." << endl;
		}

		if( endStation_ID == 0 )
		{
			cout << "EndStation not found !" << endl;
			cout << "Please reinput the Name." << endl;
		}
	}

//	cout << "endStation_ID:" << endStation_ID << endl;
//	cout << "startStation_ID:" << startStation_ID << endl;

	// START SEARCH 4 BEST CONNECTION
	Timer t;
	pf->startSearch( startStation_ptr, endStation_ptr );

	cout << pf->printBestConnection() << endl;
	cout << t.getMSecSinceStart() << " ms needed 4 PF" << endl;


/*	// Testing travel sytem setup:
	//prepare variables
	Station* prev_station = 0;
	Station* current_station = 0;
	Station* next_station = 0;

	//ADD STATIONS
	//start station
	current_station = new Station( 1, "Station 1" );
	stations.push_back( current_station );

	//station with pref_ and next_ possible Station
	prev_station = current_station;
	current_station = new Station( 2, "Station 2" );
	current_station->addPosibleNextStation( prev_station );
	next_station = new Station( 3, "Station 3" );
	current_station->addPosibleNextStation( next_station );
	stations.push_back( current_station );

	//end station
	prev_station = current_station;
	current_station = next_station;
	current_station->addPosibleNextStation( prev_station );
	stations.push_back( current_station );

	cout << "stations.size():" << stations.size() << endl;
*/
	system( "pause" );
	return 0;
}