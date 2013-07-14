#pragma once

#include <iostream>
#include <stdlib.h>

using namespace std;

class CDynArray
{
	private:
		int* data; //pointer zu den Daten
		int elements;

	public:
		//construktors
		CDynArray(); //+
		CDynArray( const CDynArray& arr); //+
		CDynArray( const int iInitialSize ); //+

		//destruktor
		~CDynArray(); //+

		int operator[]( const int index); //+

		int GetSize(); //+

		void Print(); //+

		void AddElement( const int iValue ); //+

		void InsertBeforElement( const int iValue, const int iIndex ); //+
		void InsertAfterElement( const int iValue, const int iIndex ); //*

		void DeleteElement( const int iIndex ); //+
		void DeleteRange( const int iFirst, const int iLast ); //+

		bool operator ==( const CDynArray &other ); //+
		bool operator !=( const CDynArray &other ); //+

		void Sort_ASC(); //1,2,3,4,5,... //+
		void Sort_DSC(); //10,9,8,7,... //+

		//ToDel 4 DEV:
		void DEV_INFO();
};

//+ means : tested by CJ