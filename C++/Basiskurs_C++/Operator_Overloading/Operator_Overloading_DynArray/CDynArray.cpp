#include "CDynArray.h"

//construktors
CDynArray::CDynArray()
{
	//anz elemente merken
	this->elements = 0;

	//Speicherplatz reservieren
	this->data = (int*)malloc( this->elements * sizeof(int) );
	if( this->data == NULL) exit(1);

	//array initialisieren
	for( int i = 0; i < this->elements; i++)
		this->data[i] = 0;
}

//copyconstruktor
CDynArray::CDynArray( const CDynArray& arr )
{
	//neuen speicherplatz erzeugen für die zu kopierenden Elemente
	this->data = (int*)malloc( arr.elements * sizeof(int) );
	if( this->data == NULL ) exit(1);

	//anz elemente übernehmen
	this->elements = arr.elements;

	//elemente kopieren
	for( int i = 0; i < arr.elements; i++)
		this->data[i] = arr.data[i];
}

CDynArray::CDynArray( const int iInitialSize )
{
	//vorgegebenen Speicherplatz reservieren
	this->data = (int*)malloc( iInitialSize * sizeof(int) );

	//anz elemente merken
	this->elements = iInitialSize;

	//array initialisieren
	for( int i = 0; i < iInitialSize; i++ )
		this->data[i] = 0;
}

//destruktor
CDynArray::~CDynArray()
{
	//benutzen speicherplatz freigeben
	free( this->data );
}

int CDynArray::operator []( const int index )
{
	return this->data[index];
}

int CDynArray::GetSize()
{
	//gibt die anzahl der element zurück
	return this->elements;
}

void CDynArray::Print()
{
	cout << "Print: " ;
	for( int i = 0; i < this->elements; i++)
		cout << this->data[i] << "|";
		//cout << i << ") " <<  this->data[i] << endl;
	cout << endl;
}

void CDynArray::AddElement( const int iValue )
{
	this->elements++;

	//datenbereich erweitern
	int* tmp = NULL;
	tmp	= (int*)realloc( this->data, this->elements * sizeof(int) );
	if( tmp != NULL )
	{
		this->data = tmp;
		
		//neues element anhängen
		this->data[ this->elements-1 ] = iValue;
	}
	else
		exit(1);
}

//ToFIX: Heap Corruption
void CDynArray::InsertBeforElement( const int iValue, const int iIndex )
{
	this->elements++;

	//datenbereich erweitern
	int* tmp = NULL;
	tmp	= (int*)realloc( this->data, this->elements * sizeof(int) );
	if( tmp != NULL )
	{
		this->data = tmp;
		
		//neues element initialisieren
		this->data[ this->GetSize()-1 ] = 0;
		
		//verschieben
		for( int i = this->GetSize()-1; i > iIndex; i--)
		{
			this->data[i] = this->data[i-1];
		}

		this->data[iIndex] = iValue;
	}
	else
		exit(1);
}

void CDynArray::InsertAfterElement(const int iValue, const int iIndex)
{
	this->elements++;

	//datenbereich erweitern
	int* tmp = NULL;
	tmp	= (int*)realloc( this->data, this->elements * sizeof(int) );
	if( tmp != NULL )
	{
		this->data = tmp;
		
		//neues element initialisieren
		this->data[ this->GetSize()-1 ] = 0;
		
		//verschieben
		for( int i = this->GetSize()-1; i > iIndex; i--)
		{
			this->data[i] = this->data[i-1];
		}

		this->data[iIndex+1] = iValue;
	}
	else
		exit(1);
}

void CDynArray::DeleteElement( const int iIndex )
{
	//alle elemente nach "iIndex" um 1 nach links verschieben
	for( int i = iIndex; i < this->GetSize(); i++)
		this->data[i] = this->data[i+1];

	this->elements--;

	//speicherbereich verkleinern
	int* tmp = NULL;
	tmp	= (int*)realloc( this->data, this->elements * sizeof(int) );
	if( tmp != NULL )
	{
		this->data = tmp;
	}
	else
		exit(1);
}

void CDynArray::DeleteRange( const int iFirst, const int iLast )
{
	//wieviel elemente werden gelöscht
	int dif = 0;
	if( iLast < iFirst ) dif = iFirst - iLast;
	else dif = iLast - iFirst;

	//elemente verschieben
	int start = 0;
	if( iFirst < iLast ) start = iFirst;
	else start = iLast;

	int end = 0;
	if( iFirst > iLast ) end = iFirst;
	else end = iLast;

//	cout << start << endl;
//	cout << end << endl;

	for( int i = start; i < GetSize()-start; i++ )
	{
		this->data[i] = this->data[i+end];
	}

	//anzahl elemente aktualisieren
	this->elements -= end;

	//speicherplatz verkleinern
	int* tmp = NULL;
	tmp	= (int*)realloc( this->data, this->elements * sizeof(int) );
	//auskommentiert, da man mit "DeleteRange" auch die kompletten daten löschen kann
/*	if( tmp != NULL )
	{
		this->data = tmp;
	}
	else
		exit(1);
*/
	this->data = tmp;
}

bool CDynArray::operator ==( const CDynArray &other )
{
	for( int i = 0; i < this->GetSize(); i++ )
	{
		if( this->data[i] != other.data[i] )
			return false;
	}
	return true;
}

bool CDynArray::operator !=( const CDynArray &other )
{
	for( int i = 0; i < this->GetSize(); i++ )
	{
		if( this->data[i] == other.data[i] )
			return false;
	}
	return true;
}

void CDynArray::Sort_ASC()
{
	cout << "Sort_ASC() befor:";
	this->Print();

	//aufsteigend sortieren: 1,2,3,4,5,...
	for( int i = 0; i < this->GetSize(); i++ )
	{
		for( int a = i; a < this->GetSize(); a++ )
		{
			if( this->data[a] < this->data[i] )
			{
				int tmp = this->data[i];
				this->data[i] = this->data[a];
				this->data[a] = tmp;
			}
		}
	}

	cout << "Sort_ASC() after:";
	this->Print();
}

void CDynArray::Sort_DSC()
{
	cout << "Sort_DSC() befor:";
	this->Print();

	//absteigend sortieren: 10,9,8,7,...
	for( int i = 0; i < this->GetSize(); i++ )
	{
		for( int a = i; a < this->GetSize(); a++ )
		{
			if( this->data[a] > this->data[i] )
			{
				int tmp = this->data[i];
				this->data[i] = this->data[a];
				this->data[a] = tmp;
			}
		}
	}

	cout << "Sort_DSC() after:";
	this->Print();
}

//ToDel 4 DEV
void CDynArray::DEV_INFO()
{
	cout << "DEV_INFO():" << endl;
	cout << "elements:" << this->elements << endl;
	cout << "inhalt:" << endl;
	for( int i = 0; i < this->elements; i++)
		cout << this->data[i] << endl;
}
/////////////////////////////////////////////////////////

