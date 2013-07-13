#include "CString.h"

CString::CString()
{
	for( int i = 0; i < MAX_CHARAKTERS; i++)
		this->data[i] = 0;
}

// für "CString TestString2 = "Bier";"
CString::CString( const char* cstr )
{
	strcpy( this->data, cstr );
}

/*
char* CString::getArray()
{
	return this->data;
}
*/

void CString::operator =( const char* cstr )
{
	strcpy( this->data, cstr );
}

CString CString::operator +(const CString& anotherCString)
{
	char tmp[MAX_CHARAKTERS] = {};
	strcpy( tmp, this->data );
	strcat( tmp, anotherCString.data );

	CString c( tmp);
	return c;
}

//für "CString[0] = 'D';"
char& CString::operator [](const int index)
{
	return this->data[ index ];
}

bool CString::IsEmpthy()
{
	if( this->GetLength() == 0 )
		return true;
	else
		return false;
}

int CString::GetLength()
{
	int size = strlen(this->data);
	return size;
}

CString::operator char*()
{
	return this->data;
}

bool CString::operator ==( CString &other )
{
	int result = strcmp( this->data, other.data );
	switch( result )
	{
		case 0:
			//gleich
			return true;
		break;

		default:
			//irgendwie unterschiedlich
			return false;
	}
}

bool CString::operator <=( CString &other )
{
	int result = strcmp( this->data, other.data );

	if( result <= 0 )
		return true;
	else
		return false;
}

bool CString::operator >=( CString &other )
{
	int result = strcmp( this->data, other.data );

	if( result >= 0 )
		return true;
	else
		return false;
}

bool CString::operator !=( CString &other )
{
	int result = strcmp( this->data, other.data );

	if( result != 0 )
		return true;
	else
		return false;
}

//für "TestString3 == CString("Bier")"
//beachte für 2 parameter: 
//in header: "private: friend bool operator ==(const CString &left, const CString &right );"
//in cpp: siehe unten
bool operator ==(const CString &left, const CString &right )
{
	int result = strcmp( left.data, right.data);

	if( result == 0 )
	{
		//gleich
		return true;
	}
	else
	{
		//irgendwie verschieden
		return false;
	}
}

int CString::operator <( CString &other )
{
	int result = strcmp( this->data, other.data);
	return result;
}

int CString::operator >( CString &other )
{
	int result = strcmp( this->data, other.data);
	return result;
}

CString CString::operator +=( CString &other )
{
	char tmp[MAX_CHARAKTERS] = {};
	strcpy( tmp, this->data );
	strcat( tmp, other.data );

	CString c(tmp);
	return c;
}

CString CString::operator +( char* cstr )
{
	char tmp[MAX_CHARAKTERS] = {0};
	strcat( tmp, this->data );
	strcat( tmp, cstr );

	CString c( tmp );
	return c;
}

CString CString::operator +=( char* cstr )
{
	char tmp[MAX_CHARAKTERS] = {0};
	strcat( tmp, this->data );
	strcat( tmp, cstr );

	CString c( tmp );
	return c;
}

int CString::Find( char* cstr )
{
	int foundOnIndex = -1;
//	cout << strlen( cstr ) << endl;

	//jedes einzelne zeichen in this->data mit cstr vergleichen
	for( int i = 0; i < this->GetLength(); i++)
	{
		//der erste Buchstabe wurde gefunden
		if( this->data[i] == cstr[0] )
		{
			//möglichen index gefunden an
			foundOnIndex = i;
			//von dieser stelle an weitersuchen
			int newSearchLength = strlen( cstr );
			for( int x = 0; x < newSearchLength; x++ )
			{
				//beim ersten unterschied die suche abbrechen
				if( this->data[i+x] != cstr[x] )
				{
					foundOnIndex = -1;
					break;
				}
				
//				cout << this->data[i+x] << "==" << cstr[x] << endl;

//				if( x+1 == newSearchLength )
//					cout << "GEFUNDEN ab index " << foundOnIndex << endl;
				//am ende 
			}
		}
	}

	return foundOnIndex;
}

bool CString::Contains( char* cstr )
{
	char* tmp;

	tmp = strstr( this->data, cstr );

	if( tmp == NULL )
		return false;
	else
	{
//		cout << strlen(tmp) << endl;
//		cout << "1" << endl;

		if( strlen(tmp) == 0 )
			return false;
		else
			return true;
	}
}

void CString::Reverse()
{
	char tmp[MAX_CHARAKTERS] = {};

	int size = strlen( this->data );

	for( int i = 0; i < strlen( this->data ); i++)
	{
		tmp[ i ] = this->data[ size-1-i];
	}

//	cout << "org:\"" << this->data << "\"" << endl;
//	cout << "tmp:\"" << tmp  << "\"" << endl;

	strcpy( this->data, tmp );
}

void CString::Clear()
{
	strcpy( this->data, "" );
}