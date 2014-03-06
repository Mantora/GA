#include "History.h"

#include <algorithm>// sort

//-----------------------------------------------------------------------------------------------------------------------
History::History( int maxHistoryDataCount )
{
	this->maxHistoryDataCount = maxHistoryDataCount;
	this->currentHistoryDataCount = 0;
}
//-----------------------------------------------------------------------------------------------------------------------
History::~History(void)
{

}
//-----------------------------------------------------------------------------------------------------------------------
void 
History::addPosition( int timestamp, CVector3 position)
{
	// alle vorhandenen Daten nach diesem timestamp durchsuchen
	for( std::vector<HistoryData>::iterator it = this->data.begin(); it != this->data.end(); it++ )
	{
		if( (*it).timestamp == timestamp )
		{
			// einem vorhandenen timestamp die position hinzufügen
			(*it).pos = position;

			// funktion verlassen
			return;
		}
	}

	//es wurde kein Eintrag gefunden: einen neuen zu diesem Zeitpunkt anlegen
	this->checkForDataSize();

	HistoryData tmp;
	tmp.timestamp = timestamp;
	tmp.pos = position;

	this->data.push_back( tmp );

	//zähler für die elemente in der History erhöhen
	this->currentHistoryDataCount++;

	// inhalt sortieren
	std::sort( this->data.begin(), this->data.end(), History::sortFunction );
};
//-----------------------------------------------------------------------------------------------------------------------
void 
History::addDirection(int timestamp, CVector3 direction)
{
	// alle vorhandenen Daten nach diesem timestamp durchsuchen
	for( std::vector<HistoryData>::iterator it = this->data.begin(); it != this->data.end(); it++ )
	{
		if( (*it).timestamp == timestamp )
		{
			// einem vorhandenen timestamp die position hinzufügen
			(*it).dir = direction;

			// funktion verlassen
			return;
		}
	}

	//es wurde kein Eintrag gefunden: einen neuen zu diesem Zeitpunkt anlegen
	this->checkForDataSize();

	HistoryData tmp;
	tmp.timestamp = timestamp;
	tmp.dir = direction;

	this->data.push_back( tmp );

	//zähler für die elemente in der History erhöhen
	this->currentHistoryDataCount++;

	// inhalt sortieren
	std::sort( this->data.begin(), this->data.end(), History::sortFunction );
};
//-----------------------------------------------------------------------------------------------------------------------
void 
History::addButtonEvent(int timestamp, bool buttonDown)
{
	// alle vorhandenen Daten nach diesem timestamp durchsuchen
	for( std::vector<HistoryData>::iterator it = this->data.begin(); it != this->data.end(); it++ )
	{
		if( (*it).timestamp == timestamp )
		{
			// fallunterscheidung für Buttonstate
			if( buttonDown )
			{
				// TRUE
				(*it).buttonState = TRUE;
			}
			else
			{
				// FALSE
				(*it).buttonState = FALSE;
			}

			// funktion verlassen
			return;
		}
	}

	//es wurde kein Eintrag gefunden: einen neuen zu diesem Zeitpunkt anlegen
	this->checkForDataSize();

	HistoryData tmp;
	tmp.timestamp = timestamp;
	// fallunterscheidung für Buttonstate
	if( buttonDown ) tmp.buttonState = TRUE;
	else tmp.buttonState = FALSE;

	this->data.push_back( tmp );

	//zähler für die elemente in der History erhöhen
	this->currentHistoryDataCount++;

	// inhalt sortieren
	std::sort( this->data.begin(), this->data.end(), History::sortFunction );
};
//-----------------------------------------------------------------------------------------------------------------------
CVector3 
History::getPosition(int timestamp)
{
	//zu alte timestamps mit ältesten Daten füttern
	std::vector<HistoryData>::iterator it = this->data.begin();
	if( timestamp < (*it).timestamp )
	{
		cout << "getPosition(" << timestamp << ") is to old, using last data in history : " << (*it).pos << endl;
		return (*it).pos;
	}

	// gibt es einen timestamp zu dieser Zeit ?
	HistoryData hd = this->getLastKnownData( timestamp );
	if( hd.timestamp == timestamp )
	{
		// ja, pos zu diesem zeitpunkt zurückgeben und beenden
		cout << "getPosition(" << timestamp << ") = " << hd.pos << endl;
		return hd.pos;
	}

	// nein, interpolieren oder extrapolieren ?
	int lastKnownTimestamp = this->getMaxTimestamp();

	CVector3 posOnTimestamp;

	if( timestamp < lastKnownTimestamp )
	{	
		HistoryData start = this->getLastKnownData( timestamp );
		HistoryData end = this->getFirstDataAfter( timestamp );

		posOnTimestamp = this->interpolate_pos( start, end, timestamp );
		cout << "Interpolated getPosition(" << timestamp << ") = " << posOnTimestamp << endl;
	}
	else
	{
		HistoryData lastKnownData = this->getLastKnownData( timestamp );

		posOnTimestamp = this->extrapolate_pos( lastKnownData, timestamp );
		cout << "Extrapolated getPosition(" << timestamp << ") = " << posOnTimestamp << endl;
	}
	
	return posOnTimestamp;
};
//-----------------------------------------------------------------------------------------------------------------------
CVector3 
History::getDirection(int timestamp)
{
	//zu alte timestamps mit ältesten Daten füttern
	std::vector<HistoryData>::iterator it = this->data.begin();
	if( timestamp < (*it).timestamp )
	{
		cout << "getDirection(" << timestamp << ") is to old, using last data in history : " << (*it).dir << endl;
		return (*it).dir;
	}

	// gibt es einen timestamp zu dieser Zeit ?
	HistoryData hd = this->getLastKnownData( timestamp );
	if( hd.timestamp == timestamp )
	{
		// ja, dir zu diesem zeitpunkt zurückgeben und beenden
		cout << "getDirection(" << timestamp << ") = " << hd.dir << endl;
		return hd.dir;
	}

	// nein, interpolieren oder extrapolieren ?
	int lastKnownTimestamp = this->getMaxTimestamp();

	CVector3 dirOnTimestamp;

	if( timestamp < lastKnownTimestamp )
	{
		HistoryData start = this->getLastKnownData( timestamp );
		HistoryData end = this->getFirstDataAfter( timestamp );

		dirOnTimestamp = this->interpolate_dir( start, end, timestamp );

		cout << "Interpolated getDirection(" << timestamp << ") = " << dirOnTimestamp << endl;
	}
	else
	{
		HistoryData lastKnownData = this->getLastKnownData( timestamp );

		dirOnTimestamp = this->extrapolate_dir( lastKnownData, timestamp );
		cout << "Extrapolated getDirection(" << timestamp << ") = " << dirOnTimestamp << endl;
	}

	return dirOnTimestamp;
};
//-----------------------------------------------------------------------------------------------------------------------
bool 
History::getButtonDown(int timestamp)
{
	//zu alte timestamps mit ältesten Daten füttern
	std::vector<HistoryData>::iterator it = this->data.begin();
	if( timestamp < (*it).timestamp )
	{
		cout << "getButtonDown(" << timestamp << ") is to old, using last data in history : " << (*it).buttonState << endl;
		cout << "\t##########################################################################" << endl;
		cout << "\t# TO DO: ASK GAMEDESIGNER HOW TO HANDLE BUTTONDOWN EVENT ON TO OLD DATAS #" << endl;
		cout << "\t##########################################################################" << endl;
		return false;
	}

	// gibt es einen timestamp zu dieser Zeit ?
	HistoryData hd = this->getLastKnownData( timestamp );
	if( hd.timestamp == timestamp )
	{
		// ja, dir zu diesem zeitpunkt zurückgeben und beenden
		cout << "getButtonDown(" << timestamp << ") = " << hd.buttonState << endl;
		if( hd.buttonState == TRUE ) return true;
		else return false;
	}

	// nein, interpolieren oder extrapolieren ?
	int lastKnownTimestamp = this->getMaxTimestamp();

	bool isButtonDownOnTimestamp = false;

	if( timestamp < lastKnownTimestamp )
	{
		isButtonDownOnTimestamp = interpolate_buttonDown( timestamp );
		cout << "Interpolated getButtonDown(" << timestamp << ") = " << isButtonDownOnTimestamp << endl;
	}
	else
	{
		isButtonDownOnTimestamp = extrapolate_buttonDown( timestamp );
		cout << "Extrapolated getButtonDown(" << timestamp << ") = " << isButtonDownOnTimestamp << endl;
	}

	return isButtonDownOnTimestamp;
};
//-----------------------------------------------------------------------------------------------------------------------
void 
History::printDebugInfo()
{
	cout << "History::printDebugInfo()" << endl;
	cout << "current elements in History: " << this->currentHistoryDataCount << endl;
	for( std::vector<HistoryData>::iterator it = this->data.begin(); it != this->data.end(); it++ )
	{
		(*it).print();
	}
	cout << endl;
};
//-----------------------------------------------------------------------------------------------------------------------
bool 
History::sortFunction( HistoryData h1, HistoryData h2 )
{
	return( h1.timestamp < h2.timestamp );
};
//-----------------------------------------------------------------------------------------------------------------------
HistoryData 
History::getLastKnownData( int timestamp )
{
	HistoryData tmp = this->data[0];

	for( std::vector<HistoryData>::iterator it = this->data.begin(); it != this->data.end(); it++ )
	{
		if( (*it).timestamp <= timestamp )
			tmp = (*it);
	}

	return tmp;
};
//-----------------------------------------------------------------------------------------------------------------------
HistoryData 
History::getFirstDataAfter( int timestamp )
{
	HistoryData tmp = this->data[0];

	for( std::vector<HistoryData>::iterator it = this->data.begin(); it != this->data.end(); it++ )
	{
		if( (*it).timestamp >= timestamp )
		{
			tmp = (*it);
			break;
		}
	}

	return tmp;
};
//-----------------------------------------------------------------------------------------------------------------------
int 
History::getMaxTimestamp( void )
{
	std::vector<HistoryData>::iterator it = this->data.end();

	//it zeigt auf das letzte element +1, d.h. -1
	it--;

	HistoryData tmp = (*it);

	return tmp.timestamp;
};
//-----------------------------------------------------------------------------------------------------------------------
CVector3 
History::interpolate_pos( HistoryData h1, HistoryData h2, int timestampToInterpolate )
{
	CVector3 tmp;

	/*herausfinden, zu welchem prozentsatz der timestamp abgefragt wird*/

	//anfangszeit und endzeit bis zu diesem timestamp ermitteln
	float timestampDiff_1 = (float)abs( h1.timestamp - timestampToInterpolate );
	float timestampDiff_2 = (float)abs( h2.timestamp - timestampToInterpolate );
	
	//gesamtzeit dieses bereiches
	float totalTimestampDiff = timestampDiff_1 + timestampDiff_2;

	//prozentualen Anteil errechnen
	float percent = timestampDiff_1 / totalTimestampDiff;

	//pos zu prozentsatz ausrechnen
	tmp = ( h1.pos + h2.pos ) * percent;

	return tmp;
};
//-----------------------------------------------------------------------------------------------------------------------
CVector3 
History::interpolate_dir( HistoryData h1, HistoryData h2, int timestampToInterpolate )
{
/*	cout << "+" << endl;
	h1.print();
	h2.print();
	cout << "Interpolieren von position zu timestamp " << timestampToInterpolate << endl;
	cout << "+" << endl;
*/
	CVector3 tmp;
	/*herausfinden, zu welchem prozentsatz der timestamp abgefragt wird*/

	//anfangszeit und endzeit bis zu diesem timestamp ermitteln
	float timestampDiff_1 = (float)abs( h1.timestamp - timestampToInterpolate );
	float timestampDiff_2 = (float)abs( h2.timestamp - timestampToInterpolate );
	
	//gesamtzeit dieses bereiches
	float totalTimestampDiff = timestampDiff_1 + timestampDiff_2;

	//prozentualen Anteil errechnen
	float percent = timestampDiff_1 / totalTimestampDiff;

	//pos zu prozentsatz ausrechnen
	tmp = ( h1.dir + h2.dir ) * percent;

	return tmp;
};
//-----------------------------------------------------------------------------------------------------------------------
bool 
History::interpolate_buttonDown( int timestampToInterpolate )
{
	//letzten bekannten Tastendruck herausfinden
	HistoryData hd_lastButtonEvent;
	for( std::vector<HistoryData>::iterator it = this->data.begin(); it != this->data.end(); it++ )
	{
		if( (*it).timestamp < timestampToInterpolate
			&& (*it).buttonState != NO_INPUT )
		{
			hd_lastButtonEvent = (*it);
		}
	}
	if( DEBUG )	cout << " found last Input on timestamp " << hd_lastButtonEvent.timestamp << endl;

	if( hd_lastButtonEvent.buttonState == TRUE ) return true;
	else return false; //<- keine prüfung auf ! -1 notwendig, da dies schon hd_lastButtonEvent geschehen ist
};
//-----------------------------------------------------------------------------------------------------------------------
CVector3 
History::extrapolate_pos( HistoryData h1, int timestampToExtrapolate )
{
	//letzten positionswert finden, der vor h1 kommt und nicht (0,0,0) ist
	HistoryData hd_bevorh1;
	for( std::vector<HistoryData>::iterator it = this->data.end()-1; it != this->data.begin(); it-- )
	{
		if( (*it).timestamp != h1.timestamp
			&& (*it).pos.x != 0.0f && (*it).pos.z != 0.0f  )
		{
			hd_bevorh1 = (*it);
			break;
		}
	}

	if( DEBUG) h1.print();
	if( DEBUG) hd_bevorh1.print();
	if( DEBUG) cout << "extrapolate to " << timestampToExtrapolate << endl;

	float timestampDiff = (float)abs(h1.timestamp - hd_bevorh1.timestamp);
	float timestampDiff_future = (float)abs( h1.timestamp - timestampToExtrapolate );
	if( DEBUG) cout << "timestampDiff:" << timestampDiff << endl;
	if( DEBUG) cout << "timestampDiff_future:" << timestampDiff_future << endl;

	CVector3 posDiff = h1.pos - hd_bevorh1.pos;
	if( DEBUG) cout << "posDiff:" << posDiff << endl;

	float percent = timestampDiff_future / timestampDiff;
	if( DEBUG) cout << "percent:" << percent << endl;

	CVector3 additionalPos = posDiff * percent;
	if( DEBUG) cout << "additionalPos:" << additionalPos << endl;

	CVector3 extrapolatetPos = h1.pos + additionalPos;

	return extrapolatetPos;
};
//-----------------------------------------------------------------------------------------------------------------------
CVector3 
History::extrapolate_dir( HistoryData h1, int timestampToExtrapolate )
{
	//letzten richtungswert finden, der vor h1 kommt und nicht (0,0,0) ist
	HistoryData hd_bevorh1;
	for( std::vector<HistoryData>::iterator it = this->data.end()-1; it != this->data.begin(); it-- )
	{
		if( (*it).timestamp != h1.timestamp
			&& (*it).dir.x != 0.0f && (*it).dir.z != 0.0f  )
		{
			hd_bevorh1 = (*it);
			break;
		}
	}

	if( DEBUG) h1.print();
	if( DEBUG) hd_bevorh1.print();
	if( DEBUG) cout << "extrapolate to " << timestampToExtrapolate << endl;

	float timestampDiff = (float)abs(h1.timestamp - hd_bevorh1.timestamp);
	float timestampDiff_future = (float)abs( h1.timestamp - timestampToExtrapolate );
	if( DEBUG) cout << "timestampDiff:" << timestampDiff << endl;
	if( DEBUG) cout << "timestampDiff_future:" << timestampDiff_future << endl;

	CVector3 dirDiff = h1.dir - hd_bevorh1.dir;
	if( DEBUG) cout << "dirDiff:" << dirDiff << endl;

	float percent = timestampDiff_future / timestampDiff;
	if( DEBUG) cout << "percent:" << percent << endl;

	CVector3 additionalDir = dirDiff * percent;
	if( DEBUG) cout << "additionalDir:" << additionalDir << endl;

	CVector3 extrapolatetDir = h1.dir + additionalDir;
	
	return extrapolatetDir;	
};
//-----------------------------------------------------------------------------------------------------------------------
bool 
History::extrapolate_buttonDown( int timestampToExtrapolate )
{
	//get last know data where HistoryData.buttonState != NO_INPUT
	HistoryData lastButtonStateEvent;
	for( std::vector<HistoryData>::iterator it = this->data.end()-1; it != this->data.begin(); it-- )
	{
		if( (*it).buttonState != NO_INPUT )
		{
			lastButtonStateEvent = (*it);
			break;
		}
	}

	if( DEBUG ) lastButtonStateEvent.print();

	if( lastButtonStateEvent.buttonState == TRUE ) return true;
	else return false;
};
//-----------------------------------------------------------------------------------------------------------------------
void History::checkForDataSize( void )
{
	if( this->currentHistoryDataCount == this->maxHistoryDataCount )
	{
		if( DEBUG )cout << "maxHistoryDataCount reached, delete oldest timestamp !" << endl;
		//delete oldest timestamp
		
		//da es eine nach timestamp sortierte liste ist und die neusten IMMER unten dran gehangen werden
		//erstes element entfernen
		std::vector<HistoryData>::iterator it = this->data.begin();
		this->data.erase( it );

		this->currentHistoryDataCount--;
	}
};
