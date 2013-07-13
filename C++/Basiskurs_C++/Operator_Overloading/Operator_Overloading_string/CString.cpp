#include "CString.h"

CString::CString()
{
	for( int i = 0; i < MAX_CHARAKTERS; i++)
		this->data[i] = 0;
}

// für "CString TestString2 = "Bier";"
CString::CString( const char* cstr )
{
	this->CString_cpy( this->data, cstr );
}

/*//ToDel 4 dev:
char* CString::getArray()
{
	return this->data;
}
*/////////////////



void CString::operator =( const char* cstr )
{
	this->CString_cpy( this->data, cstr );
}

CString CString::operator +(const CString& anotherCString)
{
	char tmp[MAX_CHARAKTERS] = {};
	this->CString_cpy( tmp, this->data );
	this->CString_cat( tmp, anotherCString.data );

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
	int size = CString_len(this->data);
	return size;
}

CString::operator char*()
{
	return this->data;
}

bool CString::operator ==( const CString &other )
{
	int result = this->CString_cmp( this->data, other.data );
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

bool CString::operator <=( const CString &other )
{
	int result = this->CString_cmp( this->data, other.data );

	if( result <= 0 )
		return true;
	else
		return false;
}

bool CString::operator >=( const CString &other )
{
	int result = this->CString_cmp( this->data, other.data );

	if( result >= 0 )
		return true;
	else
		return false;
}

bool CString::operator !=( const CString &other )
{
	int result = this->CString_cmp( this->data, other.data );

	if( result != 0 )
		return true;
	else
		return false;
}

//für "TestString3 == CString("Bier")"
//beachte für 2 parameter: 
//in header: "private: friend bool operator ==(const CString &left, const CString &right );"
//in cpp: siehe unten
bool operator ==( const CString &left, const CString &right )
{
	CString tmp;
	int result = tmp.CString_cmp( left.data, right.data);

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

int CString::operator <( const CString &other )
{
	int result = this->CString_cmp( this->data, other.data);
	return result;
}

int CString::operator >( const CString &other )
{
	int result = this->CString_cmp( this->data, other.data);
	return result;
}

CString CString::operator +=( const CString &other )
{
	char tmp[MAX_CHARAKTERS] = {};
	this->CString_cpy( tmp, this->data );
	this->CString_cat( tmp, other.data );

	CString c(tmp);
	return c;
}

CString CString::operator +( const char* cstr )
{
	char tmp[MAX_CHARAKTERS] = {0};
	this->CString_cpy( tmp, this->data );
	this->CString_cat( tmp, cstr );

	CString c( tmp );
	return c;
}

CString CString::operator +=( const char* cstr )
{
	char tmp[MAX_CHARAKTERS] = {0};
	this->CString_cpy( tmp, this->data );
	this->CString_cat( tmp, cstr );

	CString c( tmp );
	return c;
}

int CString::Find( const char* cstr )
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
			int newSearchLength = CString_len( cstr );
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

bool CString::Contains( const char* cstr )
{
	bool contains = this->CString_contain( this->data, cstr );
	return contains;
}

void CString::Reverse()
{
	char tmp[MAX_CHARAKTERS] = {};

	int size = CString_len( this->data );

	for( int i = 0; i < CString_len( this->data ); i++)
	{
		tmp[ i ] = this->data[ size-1-i];
	}

//	cout << "org:\"" << this->data << "\"" << endl;
//	cout << "tmp:\"" << tmp  << "\"" << endl;

	this->CString_cpy( this->data, tmp );
}

void CString::Clear()
{
	this->CString_cpy( this->data, "" );
}

//ToDel 4 test the custom <cstring> funktions
void CString::test()
{
	char str1[MAX_CHARAKTERS] = "Bier2";
	cout << str1 << endl;
	cout << this->CString_cmp( str1, "Bier" ) << endl;
	cout << str1 << endl;
}

////////////////////custom <cstring> funktion////////////////////
int CString::CString_len( const char* str )
{
	//anzahl zeichen von str
	int pos = 0;
	while( str[pos] != 0 )
	{
		pos++;
	}

	return pos;
}

void CString::CString_cpy( char* dest, const char* src )
{
	//src in dest copieren
	int anzZeichen = this->CString_len( src );
	for( int i = 0; i <= anzZeichen; i++)
		dest[i] = src[i];

	//verbesserung möglich: dest ist char array[256] -> speicherverschwendung
}

void CString::CString_cat( char* dest, const char* src )
{
	//src an dest anhängen
	int anzZeichen = this->CString_len( src );
	int anfang = this->CString_len( dest );
	for( int i = 0; i <= anzZeichen; i++)
		dest[anfang+i] = src[i];
	
	//verbesserung möglich: dest ist char array[256] -> speicherverschwendung
}

int CString::CString_cmp( const char* dest, const char* src )
{
	//src mit dest vergleich
	//return: gleich 0
	// > 0 erster wert von dest > src
	// < 0 erster wert von dest < src

	int charakters = this->CString_len(dest);
	if( this->CString_len(src) > charakters )
		charakters = this->CString_len(src);

	for( int i = 0; i < charakters; i++ )
	{
		if( dest[i] == src[i] )
		{
			//gleich, nichts tun
		}
		
		if( dest[i] > src[i] )
			return 1;

		if( dest[i] < src[i] )
			return -1;
	}

	return 0;
}

bool CString::CString_contain( const char* dest, const char* src )
{
	//true wenn src in dest enthalten
	//false nicht enthalten
	//jedes einzelne zeichen in this->data mit cstr vergleichen
	for( int i = 0; i < this->CString_len(dest); i++)
	{
		//der erste Buchstabe wurde gefunden
		if( dest[i] == src[0] )
		{
			//von dieser stelle an weitersuchen
			int newSearchLength = CString_len( src );
			for( int x = 0; x < newSearchLength; x++ )
			{
				//beim ersten unterschied die suche abbrechen
				if( this->data[i+x] != src[x] )
				{
					break;
				}
				
//				cout << dest[i+x] << "==" << src[x] << endl;

				//wenn beim letzten element keine unterschiede, suche erfolgreich
				if( x+1 == newSearchLength )
					return true;
			}
		}
	}
	return false;
}
/////////////////////////////////////////////////////////////