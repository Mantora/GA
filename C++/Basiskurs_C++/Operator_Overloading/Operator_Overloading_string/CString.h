#pragma once

#include <iostream>

#define MAX_CHARAKTERS 256

using namespace std;

class CString
{
	private:
		char data[MAX_CHARAKTERS];
		friend bool operator ==(const CString &left, const CString &right );

	public:
		CString();
		CString(const char* cstr);

		void operator =( const char* cstr);

//		char* getArray();

		CString operator +( const CString& anotherCString);

		char& operator []( const int index );

		bool IsEmpthy();
		int GetLength();

		operator char*();

		bool operator ==( CString &other );
		bool operator <=( CString &other );
		bool operator >=( CString &other );

		bool operator !=( CString &other );

		int operator <( CString &other );
		int operator >( CString &other );

		CString operator +=( CString &other );
		CString operator +( char* cstr );
		CString operator +=( char* cstr );

		int Find( char* cstr );

		bool Contains( char* cstr );

		void Reverse();

		void Clear();
};
